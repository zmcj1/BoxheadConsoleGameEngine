#include "Clipboard.h"
using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinReadFromClipboard(wchar** data)
    {
        if (!::OpenClipboard(nullptr))
        {
            return false;
        }

        if (!::IsClipboardFormatAvailable(CF_UNICODETEXT))
        {
            ::CloseClipboard();
            return false;
        }

        HANDLE handle = ::GetClipboardData(CF_UNICODETEXT);
        if (handle == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        // Lock the handle to get the actual text pointer
        wchar* text = static_cast<wchar*>(::GlobalLock(handle));
        if (text == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        //注意:这里只能进行指针复制而不是字符串复制, 否则会报错
        //::wcscpy_s(*data, wcslen(text), text);
        *data = text;

        // Release the lock
        ::GlobalUnlock(handle);

        //close
        ::CloseClipboard();

        return true;
    }

    EXPORT_FUNC_EX(bool) MinWriteToClipboard(const wchar* data)
    {
        if (!::OpenClipboard(nullptr))
        {
            return false;
        }

        if (!::EmptyClipboard())
        {
            ::CloseClipboard();
            return false;
        }

        //计算缓冲区长度: wcslen(data) + 1是因为要算上结尾的L'\0'
        int length = (::wcslen(data) + 1) * sizeof(wchar);
        //GMEM_FIXED
        HGLOBAL handle = ::GlobalAlloc(GMEM_MOVEABLE, length);
        if (handle == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        wchar* text = static_cast<wchar*>(::GlobalLock(handle));
        if (text == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        //赋值操作
        ::ZeroMemory(text, length);
        ::wcscpy_s(text, length, data);

        // Release the lock
        ::GlobalUnlock(handle);

        if (::SetClipboardData(CF_UNICODETEXT, handle) == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        ::GlobalFree(handle);

        //close
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
        return MinWriteToClipboard(data.c_str());
    }
}