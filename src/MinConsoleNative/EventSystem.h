#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <vector>

namespace MinConsoleNative
{
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

        static void Init();

        static void Update();
    };
}