// GUI utils

#include "common.h"

//static
void GuiUtils::setSystemDefaultFont(HWND hwnd)
{
    setSystemDefaultFontCallback(hwnd, 0);
}

//static
BOOL CALLBACK GuiUtils::setSystemDefaultFontCallback(HWND hwnd, LPARAM lParam)
{
    ::EnumChildWindows(hwnd, setSystemDefaultFontCallback, 0);

    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(ncm);

    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
    CFontHandle font = CreateFontIndirect(&(ncm.lfMessageFont));

    CWindow window(hwnd);
    window.SetFont(font);

    return TRUE;
}
