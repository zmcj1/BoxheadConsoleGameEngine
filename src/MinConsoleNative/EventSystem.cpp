#include "EventSystem.h"

namespace MinConsoleNative
{
    COORD EventSystem::preMousePos = { -1, -1 };

    std::vector<EventHandler*> EventSystem::handlers;

    void EventSystem::Update()
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

    void EventSystem::Init()
    {
        ConsoleMode consoleMode = Console::Global.GetInstance().GetConsoleMode();
        consoleMode.inputMode._ENABLE_WINDOW_INPUT = true;
        consoleMode.inputMode._ENABLE_QUICK_EDIT_MODE = false;
        Console::Global.GetInstance().SetConsoleMode(consoleMode);
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
}