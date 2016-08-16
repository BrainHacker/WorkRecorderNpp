// 
// CButtonWithImage.h
// Button with image control class.
// Fixes disadvantages of CBitmapButton.
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

#pragma once

class CButtonWithImage : public CBitmapButtonImpl<CButtonWithImage>
{
public:
    BEGIN_MSG_MAP(CButtonWithImage)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
        CHAIN_MSG_MAP(CBitmapButtonImpl<CButtonWithImage>)
    END_MSG_MAP()

    DECLARE_WND_SUPERCLASS(TEXT("CButtonWithImage"), GetWndClassName())

    CButtonWithImage(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = nullptr);
    void DoPaint(CDCHandle dc);

private:
    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
