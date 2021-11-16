#include "Clipboard.hpp"
using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(wchar*) MinReadFromClipboard()
    {
        if (!::OpenClipboard(nullptr))
        {
            return nullptr;
        }

        if (!::IsClipboardFormatAvailable(CF_UNICODETEXT))
        {
            ::CloseClipboard();
            return nullptr;
        }

        HANDLE handle = ::GetClipboardData(CF_UNICODETEXT);
        if (handle == nullptr)
        {
            ::CloseClipboard();
            return nullptr;
        }

        // Lock the handle to get the actual text pointer
        wchar* text = static_cast<wchar*>(::GlobalLock(handle));
        if (text == nullptr)
        {
            ::CloseClipboard();
            return nullptr;
        }

        int dataLength = ::wcslen(text) + 1; //include '\0'

        //extern alloc
        wchar* data = ExternAlloc<wchar>(dataLength);
        if (data == nullptr)
        {
            ::CloseClipboard();
            return nullptr;
        }

        ::ZeroMemory(data, dataLength * sizeof(wchar));
        ::wcscpy_s(data, dataLength, text);

        // Release the lock
        ::GlobalUnlock(handle);

        //close
        ::CloseClipboard();

        return data;
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

        //alloc
        HGLOBAL handle = ::GlobalAlloc(/*GMEM_FIXED*/ GMEM_MOVEABLE, length);
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
        ::ZeroMemory(text, length * sizeof(wchar));
        ::wcscpy_s(text, length, data);

        // Release the lock
        ::GlobalUnlock(handle);

        if (::SetClipboardData(CF_UNICODETEXT, handle) == nullptr)
        {
            ::CloseClipboard();
            return false;
        }

        //release
        ::GlobalFree(handle);

        //close
        ::CloseClipboard();
        return true;
    }

    std::wstring Clipboard::Read()
    {
        wstring wstr;
        wchar* data = MinReadFromClipboard();

        if (data == nullptr)
        {
            return wstr;
        }

        wstr = data;
        ExternFree(data);

        return wstr;
    }

    bool Clipboard::Write(const std::wstring& data)
    {
        return MinWriteToClipboard(data.c_str());
    }
}