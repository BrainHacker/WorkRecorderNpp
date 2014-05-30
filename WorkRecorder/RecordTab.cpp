// Record tab

#include "common.h"

LRESULT RecordTab::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    DlgResize_Init(false, false, 0);
    return S_OK;
}
