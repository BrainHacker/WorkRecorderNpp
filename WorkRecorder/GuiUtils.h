// GUI utils

#pragma once

class GuiUtils
{
public:
    static void setSystemDefaultFont(HWND hwnd);

private:
    static BOOL CALLBACK setSystemDefaultFontCallback(HWND hwnd, LPARAM lParam);

};