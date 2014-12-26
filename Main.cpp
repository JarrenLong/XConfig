#include "XConfig.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char szClassName[ ] = "XCFGTEST";
DWORD WinXCoord,WinYCoord,WinXWidth,WinYWidth;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wincl))
    {
        return 0;
    }

    XConfig cfg(".\\XConfig.ini");
    cfg.GetInt(WinXCoord, "Application","WinXCoord",0);
    cfg.GetInt(WinYCoord, "Application","WinYCoord",0);
    cfg.GetInt(WinXWidth, "Application","WinXWidth",320);
    cfg.GetInt(WinYWidth, "Application","WinYWidth",240);

    hwnd = CreateWindowEx (0,szClassName,"XConfig Class Test",WS_OVERLAPPEDWINDOW,
                           WinXCoord,WinYCoord,WinXWidth,WinYWidth,HWND_DESKTOP,NULL,hThisInstance,NULL);
    ShowWindow (hwnd, nFunsterStil);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        PostQuitMessage (0);
        break;
        default:
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
