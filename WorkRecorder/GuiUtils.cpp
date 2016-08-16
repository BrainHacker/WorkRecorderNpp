// 
// GuiUtils.cpp
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2017.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/dmitry-zakablukov/WorkRecorderNpp
//
// Work Recorder plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Work Recorder plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Work Recorder plugin. If not, see <http://www.gnu.org/licenses/>.
//

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

//static
CString GuiUtils::makeFilter(const CString& filter, TCHAR maskSymbol /*= TEXT('#')*/)
{
    CString result = filter;
    result.Replace(maskSymbol, 0);

    return result;
}
