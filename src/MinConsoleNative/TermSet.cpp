#include "TermSet.hpp"
#include "File.hpp"
#include <cstdlib> //_wgetenv

using namespace std;

namespace MinConsoleNative
{
    std::wstring TermSet::GetWTSettingFilePath()
    {
        //dont delete/release path!
        wchar* localAppDataPath = ::_wgetenv(L"LOCALAPPDATA");

        if (localAppDataPath == nullptr) return wstring();

        //Terminal (stable / general release):
        wstring filePath = L"Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json";
        
        //Terminal (preview release):
        //wstring filePath = L"Packages\\Microsoft.WindowsTerminalPreview_8wekyb3d8bbwe\\LocalState\\settings.json";

        return File::Combine(wstring(localAppDataPath), filePath);
    }
}