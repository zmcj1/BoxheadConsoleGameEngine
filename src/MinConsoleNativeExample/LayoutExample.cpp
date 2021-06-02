#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    int width = 10;
    std::vector<std::wstring> lines = textLayout.WstringToLines(L"english中文русский", width);

    for (size_t i = 0; i < lines.size(); i++)
    {
        std::wstring line = lines[i];
        console.WriteConsoleOutputCharacterW(line, { 0 , (short)i });

        ushort* att = new ushort[width];
        for (size_t i = 0; i < width; i++)
        {
            att[i] = ConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::BLUE);
        }
        console.WriteConsoleOutputAttribute(att, width, { (short)0 , (short)i });
        delete[] att;
    }
    console.ReadLine();
    return 0;
}