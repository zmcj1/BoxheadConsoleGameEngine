#pragma once

#include "MinDefines.hpp"

//SEE:https://devblogs.microsoft.com/commandline/understanding-windows-console-host-settings/

//
// Registry strings:FROM:winconp.h(https://github.com/microsoft/terminal/blob/main/dep/Console/winconp.h)
//

#define CONSOLE_REGISTRY_STRING                         L"Console"
#define CONSOLE_REGISTRY_FONTSIZE                       L"FontSize"
#define CONSOLE_REGISTRY_FONTFAMILY                     L"FontFamily"
#define CONSOLE_REGISTRY_BUFFERSIZE                     L"ScreenBufferSize"
#define CONSOLE_REGISTRY_CURSORSIZE                     L"CursorSize"
#define CONSOLE_REGISTRY_WINDOWMAXIMIZED                L"WindowMaximized"
#define CONSOLE_REGISTRY_WINDOWSIZE                     L"WindowSize"
#define CONSOLE_REGISTRY_WINDOWPOS                      L"WindowPosition"
#define CONSOLE_REGISTRY_WINDOWALPHA                    L"WindowAlpha"
#define CONSOLE_REGISTRY_FILLATTR                       L"ScreenColors"
#define CONSOLE_REGISTRY_POPUPATTR                      L"PopupColors"
#define CONSOLE_REGISTRY_FULLSCR                        L"FullScreen"
#define CONSOLE_REGISTRY_QUICKEDIT                      L"QuickEdit"
#define CONSOLE_REGISTRY_FACENAME                       L"FaceName"
#define CONSOLE_REGISTRY_FONTWEIGHT                     L"FontWeight"
#define CONSOLE_REGISTRY_INSERTMODE                     L"InsertMode"
#define CONSOLE_REGISTRY_HISTORYSIZE                    L"HistoryBufferSize"
#define CONSOLE_REGISTRY_HISTORYBUFS                    L"NumberOfHistoryBuffers"
#define CONSOLE_REGISTRY_HISTORYNODUP                   L"HistoryNoDup"
#define CONSOLE_REGISTRY_COLORTABLE                     L"ColorTable%02u"
#define CONSOLE_REGISTRY_EXTENDEDEDITKEY                L"ExtendedEditKey"
#define CONSOLE_REGISTRY_EXTENDEDEDITKEY_CUSTOM         L"ExtendedEditkeyCustom"
#define CONSOLE_REGISTRY_WORD_DELIM                     L"WordDelimiters"
#define CONSOLE_REGISTRY_TRIMZEROHEADINGS               L"TrimLeadingZeros"
#define CONSOLE_REGISTRY_LOAD_CONIME                    L"LoadConIme"
#define CONSOLE_REGISTRY_ENABLE_COLOR_SELECTION         L"EnableColorSelection"
#define CONSOLE_REGISTRY_SCROLLSCALE                    L"ScrollScale"
#define CONSOLE_REGISTRY_CODEPAGE                       L"CodePage"

// V2 console settings
#define CONSOLE_REGISTRY_FORCEV2                        L"ForceV2"
#define CONSOLE_REGISTRY_LINESELECTION                  L"LineSelection"
#define CONSOLE_REGISTRY_FILTERONPASTE                  L"FilterOnPaste"
#define CONSOLE_REGISTRY_LINEWRAP                       L"LineWrap"
#define CONSOLE_REGISTRY_CTRLKEYSHORTCUTS_DISABLED      L"CtrlKeyShortcutsDisabled"
#define CONSOLE_REGISTRY_ALLOW_ALTF4_CLOSE              L"AllowAltF4Close"
#define CONSOLE_REGISTRY_VIRTTERM_LEVEL                 L"VirtualTerminalLevel"
#define CONSOLE_REGISTRY_CURSORTYPE                     L"CursorType"
#define CONSOLE_REGISTRY_CURSORCOLOR                    L"CursorColor"
#define CONSOLE_REGISTRY_INTERCEPTCOPYPASTE             L"InterceptCopyPaste"
#define CONSOLE_REGISTRY_COPYCOLOR                      L"CopyColor"
#define CONSOLE_REGISTRY_USEDX                          L"UseDx"
#define CONSOLE_REGISTRY_DEFAULTFOREGROUND              L"DefaultForeground"
#define CONSOLE_REGISTRY_DEFAULTBACKGROUND              L"DefaultBackground"
#define CONSOLE_REGISTRY_TERMINALSCROLLING              L"TerminalScrolling"
// end V2 console settings

namespace MinConsoleNative
{
    //来源:https://docs.microsoft.com/en-us/windows/win32/sysinfo/deleting-a-key-with-subkeys
    bool RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey);

    bool RegDelnode(HKEY hKeyRoot, LPCTSTR lpSubKey);

    EXPORT_FUNC_EX(bool) MinIsLegacyConsole();

    //注意:设置后需要重启控制台生效
    EXPORT_FUNC_EX(bool) MinEnableLegacyConsole(bool enable);

    //delete HKEY_CURRENT_USER/Console
    //删除所有控制台注册表
    //注意!删除后无法还原!
    EXPORT_FUNC_EX(bool) MinDeleteConsoleRegistry();

    //在Windows11中可以设置默认控制台是Windows Terminal, 该函数可以进行检测
    EXPORT_FUNC_EX(bool) MinWTIsDefaultConsole();

    class ConRegistry
    {
    private:
        ConRegistry()
        {
        }

    public:
        static bool IsLegacyConsole();

        //注意:设置后需要重启控制台生效
        static bool EnableLegacyConsole(bool enable);

        //delete HKEY_CURRENT_USER/Console
        static bool DeleteConsoleRegistry();

        static bool WTIsDefaultConsole();
    };
}