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
    bool EventSystem::useLegacy = false;

    std::vector<EventHandler*> EventSystem::handlers;
    EventSystemTarget EventSystem::target;

    bool EventSystem::mouseState[5];
    bool EventSystem::_RIGHT_ALT_PRESSED;
    bool EventSystem::_LEFT_ALT_PRESSED;
    bool EventSystem::_RIGHT_CTRL_PRESSED;
    bool EventSystem::_LEFT_CTRL_PRESSED;
    bool EventSystem::_SHIFT_PRESSED;
    bool EventSystem::_NUMLOCK_ON;
    bool EventSystem::_SCROLLLOCK_ON;
    bool EventSystem::_CAPSLOCK_ON;
    bool EventSystem::_ENHANCED_KEY;

    void EventSystem::Init(EventSystemTarget target, bool useLegacy)
    {
        POINT consoleWindowSize = Console::Global.GetInstance().GetConsoleWindowSize();
        POINT clientSize = Window::Global.GetInstance().GetClientSize();

        EventSystem::preConsoleWindowSize = { (short)consoleWindowSize.x, (short)consoleWindowSize.y };
        EventSystem::preClientSize = { (short)clientSize.x, (short)clientSize.y };
        EventSystem::target = target;
        EventSystem::useLegacy = useLegacy;

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
        if (!EventSystem::inited) throw EventSystemException::SystemUninitialized;

        switch (EventSystem::target)
        {
            //for Windows Console and Windows Legacy Console
        case EventSystemTarget::Win32Callback:
        {
            if (useLegacy)
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
                console.ReadConsoleInputW(callback1, callback2, callback3);
            }
            else
            {
                //IMPORTANT:Invoke GetNumberOfConsoleInputEvents first instead of directly invoke ReadConsoleInput, otherwise it will block the entire thread.
                DWORD eventNumber = 0;
                bool getNumberSuccess = ::GetNumberOfConsoleInputEvents(console.cons.consoleInput, &eventNumber);

                if (!getNumberSuccess) break;   //error
                if (eventNumber == 0) break;    //no event

                // The number read by GetNumberOfConsoleInputEvents is not necessarily equal to the real number, so we have to creat const array here.
                INPUT_RECORD inputBuf[64];
                bool readInputSuccess = ::ReadConsoleInput(console.cons.consoleInput, inputBuf, LEN(inputBuf), &eventNumber);

                if (!readInputSuccess) break;   //error
                if (eventNumber == 0) break;    //no event

                for (int i = 0; i < eventNumber; i++)
                {
                    ushort eventType = inputBuf[i].EventType;
                    KEY_EVENT_RECORD& keyEvent = inputBuf[i].Event.KeyEvent;
                    MOUSE_EVENT_RECORD& mouseEvent = inputBuf[i].Event.MouseEvent;
                    WINDOW_BUFFER_SIZE_RECORD& bufferEvent = inputBuf[i].Event.WindowBufferSizeEvent;

                    if (eventType == KEY_EVENT)
                    {
                        for (auto item : handlers)
                        {
                            //onkey
                            item->OnKey(keyEvent.bKeyDown, keyEvent.uChar.UnicodeChar, keyEvent.wVirtualKeyCode, keyEvent.wVirtualScanCode);
                            //repeat count
                            UNUSED(keyEvent.wRepeatCount);
                            //control keystate
                            _RIGHT_ALT_PRESSED = keyEvent.dwControlKeyState & RIGHT_ALT_PRESSED;
                            _LEFT_ALT_PRESSED = keyEvent.dwControlKeyState & LEFT_ALT_PRESSED;
                            _RIGHT_CTRL_PRESSED = keyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED;
                            _LEFT_CTRL_PRESSED = keyEvent.dwControlKeyState & LEFT_CTRL_PRESSED;
                            _SHIFT_PRESSED = keyEvent.dwControlKeyState & SHIFT_PRESSED;
                            _NUMLOCK_ON = keyEvent.dwControlKeyState & NUMLOCK_ON;
                            _SCROLLLOCK_ON = keyEvent.dwControlKeyState & SCROLLLOCK_ON;
                            _CAPSLOCK_ON = keyEvent.dwControlKeyState & CAPSLOCK_ON;
                            _ENHANCED_KEY = keyEvent.dwControlKeyState & ENHANCED_KEY;
                        }
                    }
                    else if (eventType == MOUSE_EVENT)
                    {
                        for (auto item : handlers)
                        {
                            //mouse position
                            if (preMousePos.X != mouseEvent.dwMousePosition.X ||
                                preMousePos.Y != mouseEvent.dwMousePosition.Y)
                            {
                                item->OnMousePositionChanged(mouseEvent.dwMousePosition);
                                preMousePos = mouseEvent.dwMousePosition;
                            }
                            //event flags
                            switch (mouseEvent.dwEventFlags)
                            {
                            case 0:
                                //mouse button being pressed or released
                                break;
                            case DOUBLE_CLICK:
                                item->OnMouseDoubleClicked();
                                break;
                            case MOUSE_HWHEELED:
                                //ignore
                                break;
                            case MOUSE_MOVED:
                                item->OnMouseMovedOrClicked();
                                break;
                            case MOUSE_WHEELED:
                                int value = mouseEvent.dwButtonState >> sizeof(DWORD) * 8;
                                if (value > 0)
                                    item->OnMouseWheeled(MouseWheelDirection::Up);
                                else if (value < 0)
                                    item->OnMouseWheeled(MouseWheelDirection::Down);
                                else
                                    item->OnMouseWheeled(MouseWheelDirection::None);
                                break;
                            }
                            //button state
                            for (int m = 0; m < 5; m++)
                            {
                                mouseState[m] = (mouseEvent.dwButtonState & (1 << m)) == 1;
                            }
                            //control keystate
                            _RIGHT_ALT_PRESSED = mouseEvent.dwControlKeyState & RIGHT_ALT_PRESSED;
                            _LEFT_ALT_PRESSED = mouseEvent.dwControlKeyState & LEFT_ALT_PRESSED;
                            _RIGHT_CTRL_PRESSED = mouseEvent.dwControlKeyState & RIGHT_CTRL_PRESSED;
                            _LEFT_CTRL_PRESSED = mouseEvent.dwControlKeyState & LEFT_CTRL_PRESSED;
                            _SHIFT_PRESSED = mouseEvent.dwControlKeyState & SHIFT_PRESSED;
                            _NUMLOCK_ON = mouseEvent.dwControlKeyState & NUMLOCK_ON;
                            _SCROLLLOCK_ON = mouseEvent.dwControlKeyState & SCROLLLOCK_ON;
                            _CAPSLOCK_ON = mouseEvent.dwControlKeyState & CAPSLOCK_ON;
                            _ENHANCED_KEY = mouseEvent.dwControlKeyState & ENHANCED_KEY;
                        }
                    }
                    else if (eventType == WINDOW_BUFFER_SIZE_EVENT)
                    {
                        for (auto item : handlers)
                        {
                            item->OnConsoleOutputBufferChanged(bufferEvent.dwSize);
                        }
                    }
                }
            }
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

    void EventHandler::OnKey(bool keyDown, wchar character, ushort virtualKeyCode, ushort virtualScanCode)
    {
    }
}