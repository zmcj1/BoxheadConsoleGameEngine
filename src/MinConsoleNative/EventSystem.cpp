#include "EventSystem.h"
#include "VTConverter.h"
#include "String.h"
#include <string>
#include "Window.h"

using namespace std;

namespace MinConsoleNative
{
    COORD EventSystem::preMousePos = { -1, -1 };
    COORD EventSystem::preConsoleWindowSize;
    COORD EventSystem::preClientSize;
    bool EventSystem::inited = false;

    std::vector<EventHandler*> EventSystem::handlers;
    EventSystemTarget EventSystem::target;

    void EventSystem::Init(EventSystemTarget target)
    {
        POINT consoleWindowSize = Console::Global.GetInstance().GetConsoleWindowSize();
        POINT clientSize = Window::Global.GetInstance().GetClientSize();

        EventSystem::preConsoleWindowSize = { (short)consoleWindowSize.x, (short)consoleWindowSize.y };
        EventSystem::preClientSize = { (short)clientSize.x, (short)clientSize.y };
        EventSystem::target = target;

        ConsoleInputMode inputMode;

        switch (EventSystem::target)
        {
        case EventSystemTarget::Win32Callback:
            inputMode = console.GetConsoleInputMode();
            inputMode._ENABLE_WINDOW_INPUT = true;
            inputMode._ENABLE_QUICK_EDIT_MODE = false;
            console.SetConsoleInputMode(inputMode);
            EventSystem::inited = true;
            break;
        case EventSystemTarget::VTSequences:
            VTConverter::VTEnableMouseInput();
            EventSystem::inited = true;
            break;
        }
    }

    void EventSystem::Deinit()
    {
        if (target == EventSystemTarget::VTSequences)
        {
            VTConverter::VTDisableMouseInput();
        }
    }

    void EventSystem::Update()
    {
        if (!EventSystem::inited)
        {
            throw EventSystemException::SystemUninitialized;
        }

        switch (EventSystem::target)
        {
            //for Windows Console
        case EventSystemTarget::Win32Callback:
        {
            auto callback1 = [](ConsoleMouseInputRecord mouseInput)
            {
                for (size_t i = 0; i < handlers.size(); i++)
                {
                    if (mouseInput.moved)
                    {
                        handlers[i]->OnMouseMovedOrClicked();
                    }
                    if (mouseInput.doubleClick)
                    {
                        handlers[i]->OnMouseDoubleClicked();
                    }
                    if (mouseInput.mouseWheelDir != MouseWheelDirection::None)
                    {
                        handlers[i]->OnMouseWheeled(mouseInput.mouseWheelDir);
                    }
                    if (preMousePos.X != mouseInput.position.X ||
                        preMousePos.Y != mouseInput.position.Y)
                    {
                        handlers[i]->OnMousePositionChanged(mouseInput.position);
                        preMousePos = mouseInput.position;
                    }
                }
            };
            auto callback2 = [](ConsoleKeyboardInputRecord keyboardInput)
            {
                for (size_t i = 0; i < handlers.size(); i++)
                {
                    handlers[i]->OnReadKey(keyboardInput);
                }
            };
            auto callback3 = [](COORD newSize)
            {
                for (size_t i = 0; i < handlers.size(); i++)
                {
                    handlers[i]->OnConsoleOutputBufferChanged(newSize);
                }
            };
            Console::Global.GetInstance().ReadConsoleInputW(callback1, callback2, callback3);
        }
        break;

        //for Windows Terminal
        case EventSystemTarget::VTSequences:
        {
            HANDLE consoleInput = Console::Global.GetInstance().cons.consoleInput;

            DWORD eventNumber;
            bool suc1 = ::GetNumberOfConsoleInputEvents(consoleInput, &eventNumber);
            if (!suc1) return;
            if (eventNumber == 0) return;

            INPUT_RECORD inputBuffer[32];
            bool suc2 = ::ReadConsoleInput(consoleInput, inputBuffer, LEN(inputBuffer), &eventNumber);
            if (!suc2) return;
            if (eventNumber == 0) return;

            wstring wstr;
            //Read and Concatenated string here:
            for (size_t index = 0; index < eventNumber; index++)
            {
                //make sure they are all ASCII code!
                if (IsVTInput(&inputBuffer[index]) &&
                    inputBuffer[index].Event.KeyEvent.uChar.UnicodeChar <= 127)
                {
                    wstr += inputBuffer[index].Event.KeyEvent.uChar.UnicodeChar;
                }
            }

            //Parse the VT sequence
            if (wstr.size() > 1 && wstr.find_first_of(L"\27[<") != wstring::npos)
            {
                //27[<_;_;_m/M
                wstring _wstr = wstr.substr(3, wstr.size() - 4);
                auto params = String::Split(_wstr, L";");

                int vt_mouse_input_type = stoi(params[0]);
                short mouse_pos_x = stoi(params[1]) - 1;
                short mouse_pos_y = stoi(params[2]) - 1;

                switch (vt_mouse_input_type)
                {
                    //position
                case 35:
                    for (size_t index = 0; index < handlers.size(); index++)
                    {
                        handlers[index]->OnMousePositionChanged({ mouse_pos_x, mouse_pos_y });
                    }
                    break;
                    //mouse wheel up
                case 64:
                    for (size_t index = 0; index < handlers.size(); index++)
                    {
                        handlers[index]->OnMouseWheeled(MouseWheelDirection::Up);
                    }
                    break;
                    //mouse wheel down
                case 65:
                    for (size_t index = 0; index < handlers.size(); index++)
                    {
                        handlers[index]->OnMouseWheeled(MouseWheelDirection::Down);
                    }
                    break;
                }
            }
            else
            {
                for (size_t i = 0; i < eventNumber; i++)
                {
                    INPUT_RECORD curInput = inputBuffer[i];
                    switch (curInput.EventType)
                    {
                        //This event is not supported in Windows Terminal yet!
                    case MOUSE_EVENT:
                        break;
                    case WINDOW_BUFFER_SIZE_EVENT:
                        for (size_t index = 0; index < handlers.size(); index++)
                        {
                            handlers[index]->OnConsoleOutputBufferChanged
                            (curInput.Event.WindowBufferSizeEvent.dwSize);
                        }
                        break;
                    case KEY_EVENT:
                        //Just normal input
                        if (curInput.Event.KeyEvent.bKeyDown)
                        {
                            ConsoleKeyboardInputRecord keyboardInput;
                            keyboardInput.KeyChar = curInput.Event.KeyEvent.uChar.UnicodeChar;
                            keyboardInput.VirualKey = curInput.Event.KeyEvent.wVirtualKeyCode;
                            uint keyState = curInput.Event.KeyEvent.dwControlKeyState;
                            keyboardInput._RIGHT_ALT_PRESSED = keyState & RIGHT_ALT_PRESSED;
                            keyboardInput._LEFT_ALT_PRESSED = keyState & LEFT_ALT_PRESSED;
                            keyboardInput._RIGHT_CTRL_PRESSED = keyState & RIGHT_CTRL_PRESSED;
                            keyboardInput._LEFT_CTRL_PRESSED = keyState & LEFT_CTRL_PRESSED;
                            keyboardInput._SHIFT_PRESSED = keyState & SHIFT_PRESSED;
                            keyboardInput._NUMLOCK_ON = keyState & NUMLOCK_ON;
                            keyboardInput._SCROLLLOCK_ON = keyState & SCROLLLOCK_ON;
                            keyboardInput._CAPSLOCK_ON = keyState & CAPSLOCK_ON;
                            keyboardInput._ENHANCED_KEY = keyState & ENHANCED_KEY;
                            for (size_t index = 0; index < handlers.size(); index++)
                            {
                                handlers[index]->OnReadKey(keyboardInput);
                            }
                        }
                        break;
                    }
                }
            }
        }
        break;
        }

        //handle other callbacks
        POINT consoleWindowSize = Console::Global.GetInstance().GetConsoleWindowSize();
        POINT clientSize = Window::Global.GetInstance().GetClientSize();

        if (consoleWindowSize.x != preConsoleWindowSize.X ||
            consoleWindowSize.y != preConsoleWindowSize.Y)
        {
            COORD newSize = { (short)consoleWindowSize.x, (short)consoleWindowSize.y };
            for (size_t i = 0; i < handlers.size(); i++)
            {
                handlers[i]->OnConsoleWindowSizeChanged(newSize);
            }
            preConsoleWindowSize = newSize;
        }

        if (clientSize.x != preClientSize.X ||
            clientSize.y != preClientSize.Y)
        {
            COORD newSize = { (short)clientSize.x, (short)clientSize.y };
            for (size_t i = 0; i < handlers.size(); i++)
            {
                handlers[i]->OnClientSizeChanged(newSize);
            }
            preClientSize = newSize;
        }
    }

    void EventHandler::OnMouseMovedOrClicked()
    {
    }

    void EventHandler::OnMouseDoubleClicked()
    {
    }

    void EventHandler::OnMousePositionChanged(COORD position)
    {
    }

    void EventHandler::OnMouseWheeled(MouseWheelDirection wheelDir)
    {
    }

    void EventHandler::OnReadKey(ConsoleKeyboardInputRecord keyboardInput)
    {
    }

    void EventHandler::OnConsoleOutputBufferChanged(COORD newSize)
    {
    }

    void EventHandler::OnConsoleWindowSizeChanged(COORD newSize)
    {
    }

    void EventHandler::OnClientSizeChanged(COORD newSize)
    {
    }
}