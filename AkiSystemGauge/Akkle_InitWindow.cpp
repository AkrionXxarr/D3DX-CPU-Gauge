#include "Akkle.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Akkle::InitWindow(
                const wchar_t* lpWindowName,
                DWORD dwStyle,
                DWORD dwExStyle,
                int x,
                int y,
                int nWidth,
                int nHeight,
                HWND hWndParent,
                HMENU hMenu)
{
    WNDCLASSEX wcex = { 0 };

    wcex = BuildClass();

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = m_hInst;
    wcex.lpszClassName = ClassName();

    RegisterClassEx(&wcex);

    m_hwnd = CreateWindowEx(
                        dwExStyle,
                        ClassName(),
                        lpWindowName,
                        dwStyle,
                        x, y, nWidth, nHeight,
                        hWndParent,
                        hMenu,
                        m_hInst,
                        static_cast<LPVOID>(this)
                        );

    RECT windowRect, clientRect;
    POINT sizeDelta;

    if (!GetClientRect(m_hwnd, &clientRect))
        return false;
    if (!GetWindowRect(m_hwnd, &windowRect))
        return false;

    sizeDelta.x = (windowRect.right - windowRect.left) - clientRect.right;
    sizeDelta.y = (windowRect.bottom - windowRect.top) - clientRect.bottom;

    if (!MoveWindow(m_hwnd, windowRect.left, windowRect.top, nWidth + sizeDelta.x, nHeight + sizeDelta.y, TRUE))
        return false;

    m_screenWidth = nWidth;
    m_screenHeight = nHeight;

    return (m_hwnd ? true : false);
}

WNDCLASSEX Akkle::BuildClass()
{
    WNDCLASSEX wcex = { 0 };

    return wcex;
}