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
#define EXPORT_FUNC_EX(return_type) extern "C" __declspec(dllexport) return_type __stdcall
#else
#define EXPORT_FUNC extern __declspec(dllexport) bool __stdcall
#define EXPORT_FUNC_EX(return_type) extern __declspec(dllexport) return_type __stdcall
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
//no min/max
#define NOMINMAX

// Including SDKDDKVer.h defines the highest available Windows platform.
#include <SDKDDKVer.h>

//reduces the size of the Win32 header files by excluding some of the less frequently used APIs
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef LEN
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#ifndef _T
#define _T(x) TEXT(x)
#endif

#define SYS_ANAL 0

//Windows Console Versions:
#define WINDOWS_LEGACY_CONSOLE  0X0001
#define WINDOWS_CONSOLE 	    0X0002
#define WINDOWS_TERMINAL  	    0X0004

#define MIN_LOG(file, str, ...) fprintf(file, str "\n", ##__VA_ARGS__)

#define NEW_LINE "\r\n"
#define WNEW_LINE L"\r\n"

//Macros for EXPORT_FUNC and EXPORT_FUNC_EX
#define _IN_
#define _OUT_
#define _REF_
#define _ARRAY_

//Macros for NativeFunctionTranslator
#define EXPORT_ENUM_CLASS enum class
#define EXPORT_STRUCT struct
#define EXPORT_STRUCT_MEMBER
#define EXPORT_DELEGATE

//add namespace, ensure wont causes a naming conflict with the standard library(std)
namespace MinConsoleNative
{
    typedef wchar_t wchar;

    typedef unsigned char byte;

    typedef unsigned short ushort;

    typedef unsigned int uint;

    typedef unsigned long long ulong;
}