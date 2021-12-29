#include "FileDialog.hpp"
#include <commdlg.h>

namespace MinConsoleNative
{
    std::wstring FileDialog::Open(const std::vector<FileFilter>* filters)
    {
        wchar buffer[MAX_PATH] = { 0 };

        OPENFILENAME ofn = { 0 };
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = nullptr;
        ofn.hInstance = nullptr;

        if (filters == nullptr || filters->size() == 0)
        {
            ofn.lpstrFilter = L"All(*.*)\0*.*\0\0";
        }
        else
        {
            ofn.lpstrFilter = L"All(*.*)\0*.*\0\0";
        }

        ofn.lpstrCustomFilter = nullptr;
        ofn.nMaxCustFilter = 0;
        ofn.nFilterIndex = 1;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrFileTitle = nullptr;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = nullptr;
        ofn.lpstrTitle = nullptr;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        ofn.nFileOffset;
        ofn.nFileExtension;
        ofn.lpstrDefExt;
        ofn.lCustData;
        ofn.lpfnHook;
        ofn.lpTemplateName;

        if (GetOpenFileName(&ofn))
        {
            return std::wstring(buffer);
        }

        return std::wstring();
    }
}