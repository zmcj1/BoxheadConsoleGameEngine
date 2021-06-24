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

class RandomWujiangInfo
{
public:
    int randomValue;
    Wujiang wujiang;

public:
    RandomWujiangInfo(int randomValue, Wujiang& wujiang) :wujiang(wujiang)
    {
        this->randomValue = randomValue;
    }
};

RandomWujiangInfo RandomWujiang(const vector<wstring>& wujiangLines)
{
    vector<Wujiang> wujiangs;
    int totalWeight = 0;

    //Pharse
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
        //+=weight
        totalWeight += _wtoi(wujiangLine[2].c_str());
    }

    int randomValue = Random::Range(0, totalWeight - 1);
    int originRandomValue = randomValue;

    int randomWujiangIndex = -1;
    for (size_t i = 0; i < wujiangs.size(); i++)
    {
        int weight = wujiangs[i].weight;
        if (randomValue > weight - 1)
        {
            randomValue -= weight;
            continue;
        }
        else
        {
            //is this!
            randomWujiangIndex = i;
            break;
        }
    }

    return RandomWujiangInfo(originRandomValue, wujiangs[randomWujiangIndex]);
}

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

    //ConsoleEngine ce;
    //ce.ConstructConsole(L"三国杀", PaletteType::Legacy, 60, 30, FontSize::_10x20);

    Audio bgmPlayer(bgmPath);
    bgmPlayer.Play(true, false);

    vector<wstring> wujiangLines = File::ReadAllLines(wujiangWeightPath);

    console.WriteLine(L"按A连抽50次, 按S连抽10次, 按D单抽");
    while (true)
    {
        ConsoleKeyInfo key = console.ReadKey();
        int loopTime = 0;
        if (key.VirtualKey = L'A')
        {
            loopTime = 50;
        }
        else if (key.VirtualKey == L'S')
        {
            loopTime = 10;
        }
        else if (key.VirtualKey == L'D')
        {
            loopTime = 1;
        }
        else
        {
            loopTime = 0;
        }

        for (size_t i = 0; i < loopTime; i++)
        {
            RandomWujiangInfo randomWujiangInfo = RandomWujiang(wujiangLines);
            //显示史诗
            if (randomWujiangInfo.wujiang.name == L"赵襄" ||
                randomWujiangInfo.wujiang.name == L"张星彩" ||
                randomWujiangInfo.wujiang.name == L"麹义" ||
                randomWujiangInfo.wujiang.name == L"关索" ||
                randomWujiangInfo.wujiang.name == L"刘晔" ||
                randomWujiangInfo.wujiang.name == L"张让" ||
                randomWujiangInfo.wujiang.name == L"董允" ||
                randomWujiangInfo.wujiang.name == L"王平" ||
                randomWujiangInfo.wujiang.name == L"孙皓" ||
                randomWujiangInfo.wujiang.name == L"士夑" ||
                randomWujiangInfo.wujiang.name == L"陈琳" ||
                randomWujiangInfo.wujiang.name == L"戏志才" ||
                randomWujiangInfo.wujiang.name == L"杨修" ||
                randomWujiangInfo.wujiang.name == L"左慈" ||
                randomWujiangInfo.wujiang.name == L"沮授")
            {
                console.WriteLine(L"随机号为:" + to_wstring(randomWujiangInfo.randomValue) + L" 恭喜你, 你抽中了史诗武将:" + randomWujiangInfo.wujiang.name + L"!!!", { 235,168,1 });
            }
            //显示高级精品
            else if (randomWujiangInfo.wujiang.name == L"赵统赵广" ||
                randomWujiangInfo.wujiang.name == L"界孙权" ||
                randomWujiangInfo.wujiang.name == L"刘琦" ||
                randomWujiangInfo.wujiang.name == L"孙资刘放" ||
                randomWujiangInfo.wujiang.name == L"李通" ||
                randomWujiangInfo.wujiang.name == L"董白" ||
                randomWujiangInfo.wujiang.name == L"界颜良文丑")
            {
                console.WriteLine(L"随机号为:" + to_wstring(randomWujiangInfo.randomValue) + L" 恭喜你, 你抽中了精品武将:" + randomWujiangInfo.wujiang.name + L"!", { 208,115,230 });
            }
            else
            {
                console.WriteLine(L"随机号为:" + to_wstring(randomWujiangInfo.randomValue) + L" 恭喜你, 你抽中了:" + randomWujiangInfo.wujiang.name);
            }
        }
    }

    return 0;
}