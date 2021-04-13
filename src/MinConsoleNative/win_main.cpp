#ifdef _DEBUG

//#define GUI
#include "MinDefines.h"

//0x2591 ░
//0x2592 ▒
//0x2593 ▓
//0x2588 █

//FOR WIN32 SEE:https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <string>
using namespace std;

//D2D & DW factories

ID2D1Factory* pD2DFactory_;
ID2D1HwndRenderTarget* pRT_;
ID2D1SolidColorBrush* pBlackBrush_;

IDWriteFactory* pDWriteFactory_;
IDWriteTextFormat* pTextFormat_;

wstring wstr = L"asdkjasld啊是大多数空间, 😄لغة عربية/ʔæl̚luɣɑtʰu ʔælʕɑrɐbiːjatʰu/";
RECT rc = { 0 };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#include "Win32Window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    //Win32Window window(hInstance);
    //return 0;


    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    //UpdateWindow(hwnd); //test

    //Init my DirectWrite and Direct2d factories.

    HRESULT hr;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory_);

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&pDWriteFactory_)
        );
    }

    if (SUCCEEDED(hr))
    {
        //hr = pDWriteFactory_->CreateTextFormat(
        //	L"Oswald",
        //	NULL,
        //	DWRITE_FONT_WEIGHT_NORMAL,
        //	DWRITE_FONT_STYLE_NORMAL,
        //	DWRITE_FONT_STRETCH_NORMAL,
        //	20.0f,
        //	L"en-us", &pTextFormat_);
        hr = pDWriteFactory_->CreateTextFormat(
            L"Consolas",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            40.0f,
            L"en-us", &pTextFormat_);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }



    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    if (!pRT_)
    {
        D2D1_HWND_RENDER_TARGET_PROPERTIES hRTP = D2D1::HwndRenderTargetProperties(hwnd, size);

        hr = pD2DFactory_->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(), hRTP, &pRT_);
    }

    if (SUCCEEDED(hr))
    {
        hr = pRT_->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::White),
            &pBlackBrush_);
    }


    //layoutRect = D2D1::RectF(
    //    static_cast<FLOAT>(rc.left) / dpiScaleX_,
    //    static_cast<FLOAT>(rc.top) / dpiScaleY_,
    //    static_cast<FLOAT>(rc.right) / dpiScaleX_,
    //    static_cast<FLOAT>(rc.bottom) / dpiScaleY_);


    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        pRT_->BeginDraw();
        GetClientRect(hwnd, &rc);
        HDC screen = GetDC(hwnd);
        float dpiScaleX_ = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
        float dpiScaleY_ = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
        D2D1_RECT_F layoutRect = D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom);
        pRT_->Clear(D2D1::ColorF(D2D1::ColorF::Black));
        pRT_->DrawText(wstr.c_str(), wstr.size(), pTextFormat_, layoutRect, pBlackBrush_);
        HRESULT hr = pRT_->EndDraw();

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif