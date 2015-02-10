#include "Akkle.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_NCCREATE:
        {
            Akkle* pAkkle = reinterpret_cast<Akkle*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pAkkle));
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        {
            Akkle* pAkkle = reinterpret_cast<Akkle*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            pAkkle->CleanProcessMonitor();
            pAkkle->CleanApp();
            pAkkle->CleanDirect3D();
        }
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}