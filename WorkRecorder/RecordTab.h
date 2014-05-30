// Record tab

#pragma once

class RecordTab
    : public CDialogImpl<RecordTab>
    , public CDialogResize<RecordTab>
{
public:
    enum { IDD = IDD_RECORDTAB };

    BEGIN_DLGRESIZE_MAP(RecordTab)
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(RecordTab)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<RecordTab>)
    END_MSG_MAP()

    RecordTab() = default;
    virtual ~RecordTab() = default;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
};
