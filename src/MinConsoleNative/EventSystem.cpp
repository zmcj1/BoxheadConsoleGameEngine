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

    std::vector<EventHandler*> EventSystem::handlers;
    EventSystemTarget EventSystem::target;

    void EventSystem::Init(EventSystemTarget target)
    {
        POINT consoleWindowSize = Console::Global.GetInstance().GetConsoleWindowSize();
        POINT clientSize = Window::Global.GetInstance().GetClientSize();

        EventSystem::preConsoleWindowSize = { (short)consoleWindowSize.x, (short)consoleWindowSize.y };
        EventSystem::preClientSize = { (short)clientSize.x, (short)clientSize.y };
        EventSystem::target = target;
        ConsoleMode consoleMode;

        switch (EventSystem::target)
        {
        case EventSystemTarget::Win32Callback:
            consoleMode = Console::Global.GetInstance().GetConsoleMode();
            consoleMode.inputMode._ENABLE_WINDOW_INPUT = true;
            consoleMode.inputMode._ENABLE_QUICK_EDIT_MODE = false;
            Console::Global.GetInstance().SetConsoleMode(consoleMode);
            break;
        case EventSystemTarget::VTSequences:
            VTConverter::VTEnableMouseInput();
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
                        handlers[index]->OnConsoleOutputBufferChanged(curInput.Event.WindowBufferSizeEvent.dwSize);
                    }
                    break;
                case KEY_EVENT:
                    wstring wstr;
                    //Read and Concatenated string here:
                    for (size_t index = 0; index < eventNumber; index++)
                    {
                        //make sure they are all ASCII code!
                        if (VTConverter::IsVTInput(&inputBuffer[index]) &&
                            inputBuffer[index].Event.KeyEvent.uChar.UnicodeChar <= 127)
                        {
                            wstr += inputBuffer[index].Event.KeyEvent.uChar.UnicodeChar;
                        }
                    }
                    //Parse the VT sequence
                    if (wstr.size() > 1)
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

                        //The VT sequence should only be executed once
                        return;
                    }
                    //Just normal input
                    else
                    {
                        if (!curInput.Event.KeyEvent.bKeyDown)
                        {
                            continue;
                        }
                        for (size_t index = 0; index < handlers.size(); index++)
                        {
                            ConsoleKeyboardInputRecord keyboardInput;
                            keyboardInput.KeyChar = curInput.Event.KeyEvent.uChar.UnicodeChar;
                            keyboardInput.VirualKey = curInput.Event.KeyEvent.wVirtualKeyCode;
                            handlers[index]->OnReadKey(keyboardInput);
                        }
                    }
                    break;
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

    void MinConsoleNative::EventHandler::OnConsoleWindowSizeChanged(COORD newSize)
    {
    }

    void MinConsoleNative::EventHandler::OnClientSizeChanged(COORD newSize)
    {
    }
}