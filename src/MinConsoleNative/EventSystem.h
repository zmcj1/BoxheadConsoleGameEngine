#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <vector>

//EventSystem support mouse input in Windows Terminal!
//The origin of this this comes from:https://github.com/microsoft/terminal/issues/376
//I find this in comment below the issue:https://gist.github.com/Hamayama/6add968870269f2426716fad79724b31
//After a night of research, I successfully implemented mouse support!
//Special thanks to Hamayama(https://github.com/Hamayama) for inspiration.
//April 15, 2021 in Minsk.

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

        //This method is triggered when the console output buffer change
        virtual void OnConsoleWindowSizeChanged(COORD newSize);
    
        //NOTICE:newSize is in pixel.
        virtual void OnClientSizeChanged(COORD newSize);
    };

    class EventSystem
    {
    private:
        EventSystem()
        {
        }

    private:
        static COORD preMousePos;
        static COORD preConsoleWindowSize;
        static COORD preClientSize;

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

        static void Deinit();

        static void Update();
    };
}