#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    int width = 10;

    //在terminal中渲染时, 俄文的宽度都为1, 不管什么字体
    if (console.GetConsoleType() == ConsoleType::WindowsTerminal)
    {
        textLayout.charWidthUserDefineDict[L'р'] = CharWidth::Half;
        textLayout.charWidthUserDefineDict[L'у'] = CharWidth::Half;
        textLayout.charWidthUserDefineDict[L'с'] = CharWidth::Half;
        textLayout.charWidthUserDefineDict[L'к'] = CharWidth::Half;
        textLayout.charWidthUserDefineDict[L'и'] = CharWidth::Half;
        textLayout.charWidthUserDefineDict[L'й'] = CharWidth::Half;
    }

    std::vector<std::wstring> lines = textLayout.WstringToLines(L"english中文русский", width);

    for (size_t i = 0; i < lines.size(); i++)
    {
        std::wstring line = lines[i];
        console.WriteConsoleOutputCharacterW(line, { 0 , (short)i });

        ushort* att = new ushort[width];
        for (size_t i = 0; i < width; i++)
        {
            att[i] = MinConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::BLUE);
        }
        console.WriteConsoleOutputAttribute(att, width, { (short)0 , (short)i });
        delete[] att;
    }
    console.ReadLine();
    return 0;
}