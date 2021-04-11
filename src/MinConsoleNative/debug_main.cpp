#ifdef _DEBUG

#include "MinConsoleNative.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    POINT pos = Window::Global.GetInstance().GetCenterPosOfWindowInDesktop();
    Window::Global.GetInstance().SetWindowPos(pos);
    Console::Global.GetInstance().SetTreatControlCAsInput(true);


    //while (true)
    //{
    //    Input::CheckKeyboardEx();
    //    if (Input::GetKeyDownEx('A'))
    //    {
    //        Console::Global.GetInstance().WriteLine(L"down");
    //    }
    //    if (Input::GetKeyUpEx('A'))
    //    {
    //        Console::Global.GetInstance().WriteLine(L"up");
    //    }
    //    Sleep(1);
    //}


    //CHAR_INFO cells[6];
    //for (int i = 0; i < 6; i++)
    //{
    //    if (i % 2 == 0)
    //    {
    //        cells[i].Char.UnicodeChar = L'大';
    //        cells[i].Attributes = ConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::GREEN) |
    //            COMMON_LVB_LEADING_BYTE;
    //    }
    //    else
    //    {
    //        cells[i].Char.UnicodeChar = L'\0';
    //        cells[i].Attributes = ConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::GREEN) |
    //            COMMON_LVB_TRAILING_BYTE;
    //    }
    //    cells[i].Attributes |= COMMON_LVB_UNDERSCORE;
    //}
    //auto xxx = Console::Global.GetInstance().GetConsoleFont();
    //COORD SIZE = GetConsoleFontSize(Console::Global.GetInstance().cons.consoleOutput, xxx.FontIndex);
    //Console::Global.GetInstance().WriteConsoleOutputW(cells, 0, 0, 6, 1);
    //Console::Global.GetInstance().SetConsoleCursorPos({ 10,0 });
    //Console::Global.GetInstance().ReadLine();
    //return 0;


    //ConsoleFont cf;
    //cf.SetFontBold(false);
    //cf.SetFontWidth(8);
    //cf.SetFontHeight(16);
    //cf.SetFontName(L"Consolas");
    //Console::Global.GetInstance().SetConsoleFont(cf);
    //Console::Global.GetInstance().GetConsoleFont();
    //TextLayout textLayout(Console::Global.GetInstance());
    //auto lines = textLayout.WstringToLines(L"english中文русский", 5);
    //for (size_t i = 0; i < lines.size(); i++)
    //{
    //    wstring line = lines[i];
    //    Console::Global.GetInstance().WriteConsoleOutputCharacterW(line, { 0 , (short)i });
    //    ushort att[5];
    //    for (size_t i = 0; i < LEN(att); i++)
    //    {
    //        att[i] = ConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::BLUE);
    //    }
    //    Console::Global.GetInstance().WriteConsoleOutputAttribute(att, 5, { 0 , (short)i });
    //}
    //Console::Global.GetInstance().ReadLine();
    //return 0;


    //MinTimer timer;
    //MinInitTimer(&timer);
    //while (true)
    //{
    //    MinStartTimer(&timer);
    //    Sleep(10);
    //    double deltaTime = 0;
    //    MinStopTimer(&timer);
    //    MinTimeTimer(&timer, &deltaTime);
    //    cout << deltaTime << "\n";
    //}


    //Input::ResetMouseAxis();
    //Timer timer;
    //while (true)
    //{
    //    timer.Start();
    //    Sleep(100);
    //    timer.Stop();
    //    double deltaTime = timer.Time();
    //    Input::CheckMouseAxis();
    //    int diff = Input::GetMouseAxis(MouseAxis::MOUSE_X);
    //    cout << diff << "\n";
    //    if (Input::GetKeyDown('A'))
    //    {
    //        cout << deltaTime << "\n";
    //    }
    //}
}

#endif