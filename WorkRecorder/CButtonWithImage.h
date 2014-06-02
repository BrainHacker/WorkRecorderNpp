// Button with image control class
// Fixes disadvantages of CBitmapButton

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

    CButtonWithImage(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = NULL);
    void DoPaint(CDCHandle dc);

private:
    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
