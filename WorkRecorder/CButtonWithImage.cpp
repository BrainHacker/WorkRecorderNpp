// 
// CButtonWithImage.cpp
// Button with image control class.
// Fixes disadvantages of CBitmapButton.
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2014.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/BrainHacker/WorkRecorderNpp
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

CButtonWithImage::CButtonWithImage(DWORD dwExtendedStyle /*= BMPBTN_AUTOSIZE*/,
    HIMAGELIST hImageList /*= NULL*/)
    : CBitmapButtonImpl<CButtonWithImage>(dwExtendedStyle, hImageList)
{

}

void CButtonWithImage::DoPaint(CDCHandle dc)
{
    ATLASSERT(m_ImageList.m_hImageList != NULL);   // image list must be set
    ATLASSERT(m_nImage[0] != -1);                  // main bitmap must be set

    // set bitmap according to the current button state
    bool bHover = IsHoverMode();
    bool bPressed = (m_fPressed == 1) || (IsCheckMode() && (m_fChecked == 1));
    int nImage = -1;
    if (!IsWindowEnabled())
        nImage = m_nImage[_nImageDisabled];
    else if (bPressed)
        nImage = m_nImage[_nImagePushed];
    else if ((m_fFocus == 1) || (bHover && (m_fMouseOver == 1)))
        nImage = m_nImage[_nImageFocusOrHover];

    // if none is set, use default one
    if (nImage == -1)
        nImage = m_nImage[_nImageNormal];

    // fill background
    RECT rect = {};
    GetClientRect(&rect);
    dc.FillRect(&rect, (HBRUSH)(COLOR_BTNFACE + 1));

    // draw the button image
    bool bAuto3D = (m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0;
    int xyPos = (bPressed && bAuto3D && (m_nImage[_nImagePushed] == -1)) ? 1 : 0;
    m_ImageList.Draw(dc, nImage, xyPos, xyPos, ILD_NORMAL);

    // draw 3D border if required
    if (bAuto3D)
    {
        if (bPressed)
            dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_SUNKENOUTER : EDGE_SUNKEN, BF_RECT);
        else if (!bHover || (m_fMouseOver == 1))
            dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_RAISEDINNER : EDGE_RAISED, BF_RECT);

        if (!bHover && (m_fFocus == 1))
        {
            ::InflateRect(&rect, -2 * ::GetSystemMetrics(SM_CXEDGE), -2 * ::GetSystemMetrics(SM_CYEDGE));
            dc.DrawFocusRect(&rect);
        }
    }
}

LRESULT CButtonWithImage::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == VK_SPACE && m_fPressed == 0)
    {
        m_fPressed = 1;
        Invalidate();
        UpdateWindow();
    }

    return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CButtonWithImage::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == VK_SPACE && m_fPressed == 1)
    {
        m_fPressed = 0;
        if ((m_dwExtendedStyle & BMPBTN_AUTOCHECK) != 0)
            SetCheck(!GetCheck(), false);
        Invalidate();
        UpdateWindow();
    }

    return DefWindowProc(uMsg, wParam, lParam);
}

