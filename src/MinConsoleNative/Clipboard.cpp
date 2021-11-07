#include "Clipboard.h"
using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinReadFromClipboard(wchar** data)
    {
        bool open_suc = ::OpenClipboard(0);
        if (!open_suc) return false;

        bool data_available = ::IsClipboardFormatAvailable(CF_UNICODETEXT);
        if (!data_available)
        {
            ::CloseClipboard();
            return false;
        }

        //The clipboard controls the handle that the GetClipboardData function returns, not the application. The application should copy the data immediately. The application must not free the handle nor leave it locked.
        //So we should not free this rawData, we can copy it.
        wchar* rawData = (wchar*)::GetClipboardData(CF_UNICODETEXT);
        if (rawData == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        *data = rawData;

        ::CloseClipboard();
        return true;
    }

    EXPORT_FUNC_EX(bool) MinWriteToClipboard(const wchar* data, int charCount)
    {
        bool open_suc = ::OpenClipboard(0);
        if (!open_suc) return false;

        ::EmptyClipboard();

        int length = (charCount + 1) * sizeof(wchar);
        wchar* rawData = (wchar*)::GlobalAlloc(GMEM_FIXED, length);

        if (rawData == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        ::ZeroMemory(rawData, length);
        ::wcscpy_s(rawData, length, data);

        HANDLE set_data_suc = ::SetClipboardData(CF_UNICODETEXT, rawData);
        ::GlobalUnlock(rawData);
        //GlobalFree(rawData); //Use this will cause a breakpoint!

        if (!set_data_suc)
        {
            ::CloseClipboard();
            return false;
        }

        ::CloseClipboard();
        return true;
    }

    std::wstring Clipboard::Read()
    {
        wstring wstr;
        wchar* data = nullptr;

        bool suc = MinReadFromClipboard(&data);
        if (!suc) return wstr;

        wstr = data;
        return wstr;
    }

    bool Clipboard::Write(const std::wstring& data)
    {
        return MinWriteToClipboard(data.c_str(), (int)data.size());
    }
}