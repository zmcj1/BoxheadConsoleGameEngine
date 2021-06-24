#include "..\MinConsoleNative\MinConsoleNative.h"
#include <string>

using namespace std;

class Wujiang
{
public:
    wstring name;
    int level;
    int weight;

    Wujiang(wstring name, int level, int weight)
    {
        this->name = name;
        this->level = level;
        this->weight = weight;
    }
};

int main()
{
    wstring resPath = L"../../res/";
    wstring wujiangWeightPath = File::Combine(resPath, L"sgs.txt");
    wstring bgmPath = File::Combine(resPath, L"sgs_bgm.mp3");

    bool sgs_exists = File::Exists(wujiangWeightPath);
    bool bgm_exists = File::Exists(bgmPath);

    if (!sgs_exists)
    {
        throw "Can't find sgs.txt!";
    }
    if (!bgm_exists)
    {
        throw "Can't find sgs_bgm.mp3!";
    }

    ConsoleEngine ce;
    ce.ConstructConsole(L"三国杀", PaletteType::Legacy, 60, 30, FontSize::_10x20);

    Audio bgmPlayer(bgmPath);
    bgmPlayer.Play(true, false);

    vector<wstring> wujiangLines = File::ReadAllLines(wujiangWeightPath);
    vector<Wujiang> wujiangs;

    for (int i = 0; i < wujiangLines.size(); i++)
    {
        //trim
        wstring item = String::TrimAll(wujiangLines[i]);
        //ignore //
        if (item.find(L"//") != wstring::npos)
        {
            continue;
        }
        //ignore empty line
        if (item == L"")
        {
            continue;
        }
        //split
        vector<wstring> wujiangLine = String::Split(item, L",");
        //add
        wujiangs.push_back(Wujiang(wujiangLine[0],
            _wtoi(wujiangLine[1].c_str()), _wtoi(wujiangLine[2].c_str())));
    }

    //legacy
    //GDIRenderer::PutPixel(100, 100, Color24(255, 255, 255));
    //lua_test();

    console.ReadKey();
    return 0;
}