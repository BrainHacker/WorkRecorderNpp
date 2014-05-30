// Record tab

#include "common.h"

void RecordingWindow::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

LRESULT RecordingWindow::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    DlgResize_Init(false, false, 0);
    return S_OK;
}
