#include "MinConsoleNative.hpp"

class MyEventHandler : public EventHandler
{
public:
    //Move and click will trigger this method
    void OnMouseMovedOrClicked()
    {

    }

    //Only double click will trigger the method
    void OnMouseDoubleClicked()
    {

    }

    //This method is triggered when the mouse coordinates change
    void OnMousePositionChanged(COORD position)
    {

    }

    //Turning the mouse wheel will trigger the method
    void OnMouseWheeled(MouseWheelDirection wheelDir)
    {

    }

    //The method is triggered when you enter a character
    void OnReadKey(ConsoleKeyboardInputRecord keyboardInput)
    {

    }

    //This method is triggered when the console output buffer change
    void OnConsoleOutputBufferChanged(COORD newSize)
    {

    }

    //This method is triggered when the console window size change
    void OnConsoleWindowSizeChanged(COORD newSize)
    {

    }

    //NOTICE:newSize is in pixel.
    void OnClientSizeChanged(COORD newSize)
    {

    }

    //The method is triggered when you press or release a key.
    void OnKey(bool keyDown, wchar character, ushort virtualKeyCode, ushort virtualScanCode)
    {
        console.WriteLine(String::WcharToWstring(character));
    }
};

void initInputModule(MyEventHandler* myHandlerPtr)
{
    EventSystemTarget eventSysTarget = EventSystemTarget::Win32Callback;

    ConsoleType consoleType = console.GetConsoleType();
    if (consoleType == ConsoleType::WindowsConsole)
    {
        eventSysTarget = EventSystemTarget::Win32Callback;
    }
    else if (consoleType == ConsoleType::WindowsTerminal)
    {
        eventSysTarget = EventSystemTarget::VTSequences;
    }
    else if (consoleType == ConsoleType::WindowsLegacyConsole)
    {
        eventSysTarget = EventSystemTarget::Win32Callback;
    }
    else
    {
        //not support now
    }

    EventSystem::Init(eventSysTarget, false);
    EventSystem::handlers.push_back(myHandlerPtr);
}

void deinitInputModule()
{
    EventSystem::Deinit();
}

void updateInputModule()
{
    EventSystem::Update();
}

int main()
{
    MyEventHandler myHandler;

    initInputModule(&myHandler);
    while (true)
    {
        updateInputModule();
        ::Sleep(10);
    }
    deinitInputModule();
    return 0;
}