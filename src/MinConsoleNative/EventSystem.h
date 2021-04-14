#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <vector>

namespace MinConsoleNative
{
    enum class EventSystemTarget
    {
        Win32Callback = 1,
        VTSequences = 2,
    };

    class EventHandler
    {
    public:
        //Move and click will trigger this method
        virtual void OnMouseMovedOrClicked();

        //Only double click will trigger the method
        virtual void OnMouseDoubleClicked();

        //This method is triggered when the mouse coordinates change
        virtual void OnMousePositionChanged(COORD position);

        //Turning the mouse wheel will trigger the method
        virtual void OnMouseWheeled(MouseWheelDirection wheelDir);

        //The method is triggered when you enter a character
        virtual void OnReadKey(ConsoleKeyboardInputRecord keyboardInput);

        //This method is triggered when the console output buffer change
        virtual void OnConsoleOutputBufferChanged(COORD newSize);
    };

    //Before use this system, you need to turn on EnableWindowInput and turn off EnableQuickEditMode
    class EventSystem
    {
    private:
        EventSystem()
        {
        }

    private:
        static COORD preMousePos;

    public:
        static std::vector<EventHandler*> handlers;
        static EventSystemTarget target;

        //About input mode:
        //Win32Callback:
        //    enable_window_input = true
        //    enable_quick_edit_mode = false
        //VTSequences:
        //    enable_window_input = true
        //    enable_quick_edit_mode = true
        //    enable_virtual_terminal_input = true
        static void Init(EventSystemTarget target);

        static void Update();
    };
}