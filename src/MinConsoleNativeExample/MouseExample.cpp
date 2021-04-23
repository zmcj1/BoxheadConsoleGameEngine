#include "..\MinConsoleNative\MinConsoleNative.h"

class ExampleHandler : public EventHandler
{
    void OnReadKey(ConsoleKeyboardInputRecord keyboardInput) override
    {
        Console::Global.GetInstance().WriteLine(String::WcharToWstring(keyboardInput.KeyChar));
    }

    //Move and click will trigger this method
    void OnMouseMovedOrClicked()
    {
        Console::Global.GetInstance().WriteLine(L"moved");
    }

    //Only double click will trigger the method
    void OnMouseDoubleClicked()
    {
        Console::Global.GetInstance().WriteLine(L"double clicked");
    }

    //This method is triggered when the mouse coordinates change
    void OnMousePositionChanged(COORD position)
    {
        Console::Global.GetInstance().WriteLine(Vector2(position).ToString());
    }

    //Turning the mouse wheel will trigger the method
    void OnMouseWheeled(MouseWheelDirection wheelDir)
    {
        if (wheelDir == MouseWheelDirection::Up)
        {
            Console::Global.GetInstance().WriteLine(L"up");
        }
        else if (wheelDir == MouseWheelDirection::Down)
        {
            Console::Global.GetInstance().WriteLine(L"down");
        }
    }

    //This method is triggered when the console output buffer change
    void OnConsoleOutputBufferChanged(COORD newSize)
    {
        Console::Global.GetInstance().WriteLine(L"buffer" + Vector2(newSize).ToString());
    }

    //This method is triggered when the console output buffer change
    void OnConsoleWindowSizeChanged(COORD newSize)
    {
        Console::Global.GetInstance().WriteLine(L"window" + Vector2(newSize).ToString());
    }

    //NOTICE:newSize is in pixel.
    void OnClientSizeChanged(COORD newSize)
    {
        Console::Global.GetInstance().WriteLine(L"client" + Vector2(newSize).ToString());
    }
};

int main()
{
    ConsoleType type = console.GetConsoleType();

    if (type == ConsoleType::WindowsConsole || type == ConsoleType::WindowsLegacyConsole)
    {
        EventSystem::Init(EventSystemTarget::Win32Callback);
    }
    else if (type == ConsoleType::WindowsTerminal)
    {
        EventSystem::Init(EventSystemTarget::VTSequences);
    }

    ExampleHandler handler;
    EventSystem::handlers.push_back(&handler);
    while (true)
    {
        if (Input::GetKey('C'))
        {
            Console::Global.GetInstance().Clear();
        }
        EventSystem::Update();
    }

    return 0;
}