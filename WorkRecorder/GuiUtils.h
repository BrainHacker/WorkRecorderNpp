// GUI utils

#pragma once

class GuiUtils
{
public:
    static void setSystemDefaultFont(HWND hwnd);

    /// Makes filter string for File-Open dialog
    /// @param maskSymbol - symbol to be replaced in string by '\0'
    static CString makeFilter(const CString& filter, TCHAR maskSymbol = TEXT('#'));

private:
    static BOOL CALLBACK setSystemDefaultFontCallback(HWND hwnd, LPARAM lParam);

};