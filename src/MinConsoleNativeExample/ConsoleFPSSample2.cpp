#include "MinConsoleNative.hpp"

class ConsoleFPS2 : public ConsoleEngine
{

};

int main()
{
    auto path = TermSet::GetWTSettingFilePath();
    auto content = File::ReadAllText(path);
    return 0;
}