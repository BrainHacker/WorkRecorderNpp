// Main Work Recorder dialog

#include "common.h"

void MainDlg::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

LRESULT MainDlg::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    tabControl.SubclassWindow(GetDlgItem(IDC_MAINDLGTABCTRL));

    CWindow firstTab = playbackTab.Create(tabControl);
    insertTab(firstTab, 0, Constants::strPlaybackTabName);

    CWindow secondTab = recordTab.Create(tabControl);
    insertTab(secondTab, 1, Constants::strRecordTabName);

    tabControl.SetCurSel(0);

    DlgResize_Init(false, false, 0);
    return S_OK;
}

void MainDlg::insertTab(CWindow tab, uint index, const TCHAR* name)
{
    TCITEM item = {};
    item.mask = TCIF_TEXT;
    item.pszText = (TCHAR*)name;

    tabControl.InsertItem(index, &item, tab);
}
