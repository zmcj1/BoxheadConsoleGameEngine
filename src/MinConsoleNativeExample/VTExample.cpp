#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    //VT TEST
    Console::Global.GetInstance().Write(VTConverter::WindowTitle(L"Hello World"));
    Console::Global.GetInstance().Write(VTConverter::CursorPos({ 10,5 }));
    Console::Global.GetInstance().Write(VTConverter::CursorVisible(true));
    Console::Global.GetInstance().Write(L"你好世界", { 55,55,189 }, { 33,33,33 }, true);
    Console::Global.GetInstance().ReadLine();
    return 0;
}