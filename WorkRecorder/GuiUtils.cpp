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

//static
void GuiUtils::changeControlFontSize(HWND parentHwnd, uint controlId, uint fontSize)
{
    CWindow control = GetDlgItem(parentHwnd, controlId);
    CFontHandle font = control.GetFont();

    CLogFont logFont;
    font.GetLogFont(&logFont);

    logFont.SetHeight(fontSize);
    font = logFont.CreateFontIndirect();
    control.SetFont(font);
}

//static
void GuiUtils::onBrowseRecordFile(HWND parentHwnd, uint editControlId)
{
    const TCHAR* strFileName = TEXT("");

    CString defaultExtension = translate(IDS_RECORDFILEEXTENSION);
    CString filter = GuiUtils::makeFilter(translate(IDS_FILEDIALOGFILTER));

    DWORD flags = OFN_FILEMUSTEXIST;
    CFileDialog dlg(FALSE, defaultExtension, strFileName, flags, filter, parentHwnd);
    // TODO: fill initial folder and file name based on the previous choice

    INT_PTR answer = dlg.DoModal();
    if (answer == IDOK)
    {
        CEdit edit = GetDlgItem(parentHwnd, editControlId);
        edit.SetWindowText(dlg.m_szFileName);

        int length = edit.GetWindowTextLength();
        edit.SetSel(length, length);
        edit.SetFocus();
    }
}
