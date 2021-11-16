#include "MinConsoleNative.hpp"

int main()
{
    //VT TEST
    Console::Global.GetInstance().Write(VTConverter::VTWindowTitle(L"Hello World"));
    Console::Global.GetInstance().Write(VTConverter::VTCursorPos({ 10,5 }));
    Console::Global.GetInstance().Write(VTConverter::VTCursorVisible(true));
    Console::Global.GetInstance().Write(L"你好世界", { 55,55,189 }, { 33,33,33 }, true);
    Console::Global.GetInstance().ReadLine();
    return 0;
}