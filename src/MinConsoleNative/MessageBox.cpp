#include "MessageBox.h"

using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(MessageBoxResult) MinShowMessageBox(const wchar* text, const wchar* title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType)
    {
        MessageBoxResult result = MessageBoxResult::OK;

        uint type = 0;

        switch (buttons)
        {
        case MessageBoxButtons::OK:
            type |= MB_OK;
            break;
        case MessageBoxButtons::OKCANCEL:
            type |= MB_OKCANCEL;
            break;
        case MessageBoxButtons::YESNO:
            type |= MB_YESNO;
            break;
        case MessageBoxButtons::YESNOCANCEL:
            type |= MB_YESNOCANCEL;
            break;
        }

        switch (defButton)
        {
        case MessageBoxDefaultButton::First:
            type |= MB_DEFBUTTON1;
            break;
        case MessageBoxDefaultButton::Second:
            type |= MB_DEFBUTTON2;
            break;
        case MessageBoxDefaultButton::Third:
            type |= MB_DEFBUTTON3;
            break;
        }

        switch (iconType)
        {
        case MessageBoxIcon::Warning:
            type |= MB_ICONWARNING;
            break;
        case MessageBoxIcon::Information:
            type |= MB_ICONINFORMATION;
            break;
        case MessageBoxIcon::Error:
            type |= MB_ICONERROR;
            break;
        }

        int r = MessageBox(nullptr, text, title, type);

        switch (r)
        {
        case IDOK:
            result = MessageBoxResult::OK;
            break;
        case IDYES:
            result = MessageBoxResult::YES;
            break;
        case IDNO:
            result = MessageBoxResult::NO;
            break;
        case IDCANCEL:
            result = MessageBoxResult::CANCEL;
            break;
        }

        return result;
    }

    MessageBoxResult WMessageBox::Show(const std::wstring& text, const std::wstring& title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType)
    {
        return MinShowMessageBox(text.c_str(), title.c_str(), buttons, defButton, iconType);
    }
}