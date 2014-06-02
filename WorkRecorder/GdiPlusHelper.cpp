// GDI+ helper class

#include "common.h"

void GdiPlusHelper::init()
{
    Gdiplus::GdiplusStartup(&token, &input, NULL);
}

void GdiPlusHelper::uninit()
{
    Gdiplus::GdiplusShutdown(token);
}
