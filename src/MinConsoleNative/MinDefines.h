#pragma once

//See:https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160

//Macro:CUI/GUI

#ifdef _MSC_VER

#if !defined(WIN32) && !defined(_WIN32)
#error Windows Only.
#endif

#if defined(_MT) && !defined(_DLL) && !defined(_DEBUG)
#define MT
#elif defined(_MT) && !defined(_DLL) && defined(_DEBUG)
#define MT_DEBUG
#elif defined(_MT) && defined(_DLL) && !defined(_DEBUG)
#define MD
#elif defined(_MT) && defined(_DLL) && defined(_DEBUG)
#define MD_DEBUG
#endif

//X86/X64
#ifdef _M_X64
#define X64
#else
#define X86
#endif

//In order to prevent naming conflicts, all export methods in this project are prefixed with Min
#ifdef __cplusplus
#define EXPORT_FUNC extern "C" __declspec(dllexport) bool __stdcall
#else
#define EXPORT_FUNC extern __declspec(dllexport) bool __stdcall
#endif

#if defined(CUI)    //(Command User Interface)
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#elif defined(GUI)  //(Graphical User Interface)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#endif

#endif

#if !defined(UNICODE) && !defined(_UNICODE)
#ifdef _MSC_VER
#error Please enable UNICODE for your MS compiler! For VisualStudio: Project Properties -> General -> Character Set -> Use Unicode.
#else
// For now, I'll try enabling it for you
#define UNICODE
#define _UNICODE
#endif
#endif

//Disable warning
#define _CRT_SECURE_NO_WARNINGS
//Disable network library warning
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//reduces the size of the Win32 header files by excluding some of the less frequently used APIs
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef LEN
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#ifndef _T
#define _T(x) TEXT(x)
#endif

typedef wchar_t wchar;

typedef unsigned char byte;

typedef unsigned short ushort;

typedef unsigned int uint;

typedef unsigned long long ulong;