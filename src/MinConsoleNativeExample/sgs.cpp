#include "..\MinConsoleNative\MinConsoleNative.h"
#include <string>
#include <ctime>

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

    
    int randomValue = (::rand() % totalWeight) + 1;

    //int randomValue = Random::Range(1, totalWeight);
    //modify
    //randomValue = totalWeight;

    int originRandomValue = randomValue;

    int randomWujiangIndex = -1;
    for (size_t i = 0; i < wujiangs.size(); i++)
    {
        int weight = wujiangs[i].weight;
        if (randomValue > weight)
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

    //Audio bgmPlayer(bgmPath);
    //bgmPlayer.Play(true, false);

    ::srand(time(nullptr));

    vector<wstring> wujiangLines = File::ReadAllLines(wujiangWeightPath);

    //RandomWujiangInfo rw = RandomWujiang(wujiangLines);
    //int x = 0;
    //while (!String::Compare(rw.wujiang.name, L"赵襄"))
    //{
    //    rw = RandomWujiang(wujiangLines);
    //    x++;
    //}

    console.WriteLine(L"按A连抽50次, 按S连抽10次, 按D单抽");
    while (true)
    {
        ConsoleKeyInfo key = console.ReadKey(false);

        int loopTime = 0;
        if (key.KeyChar == L'a')
        {
            loopTime = 5000;
        }
        else if (key.KeyChar == L's')
        {
            loopTime = 10;
        }
        else if (key.KeyChar == L'd')
        {
            loopTime = 1;
        }

        for (size_t i = 0; i < loopTime; i++)
        {
            RandomWujiangInfo randomWujiangInfo = RandomWujiang(wujiangLines);

            //显示史诗
            if (String::Compare(randomWujiangInfo.wujiang.name, L"赵襄") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"张星彩") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"麹义") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"关索") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"刘晔") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"张让") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"董允") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"王平") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"孙皓") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"士夑") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"陈琳") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"戏志才") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"杨修") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"左慈") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"沮授"))
            {
                console.WriteLine(L"随机号为:" + to_wstring(randomWujiangInfo.randomValue) + L" 恭喜你, 你抽中了史诗武将:" + randomWujiangInfo.wujiang.name + L"!!!", { 235,168,1 });
            }
            //显示高级精品
            else if (String::Compare(randomWujiangInfo.wujiang.name, L"赵统赵广") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"界孙权") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"刘琦") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"孙资刘放") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"李通") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"董白") ||
                String::Compare(randomWujiangInfo.wujiang.name, L"界颜良文丑"))
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