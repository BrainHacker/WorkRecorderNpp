// Main Work Recorder dialog

#include "common.h"

LRESULT MainDlg::OnClose(UINT msgId, WPARAM wP, LPARAM lP, BOOL& handled)
{
    EndDialog(S_OK);
    return S_OK;
}
