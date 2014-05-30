// Record tab

#pragma once

class RecordingWindow
    : public Singleton<RecordingWindow>
    , public CDialogImpl<RecordingWindow>
    , public CDialogResize<RecordingWindow>
{
public:
    enum { IDD = IDD_RECORDINGDLG };

    BEGIN_DLGRESIZE_MAP(RecordingWindow)
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(RecordingWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<RecordingWindow>)
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    RecordingWindow() = default;
    virtual ~RecordingWindow() = default;

    friend class Singleton<RecordingWindow>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
};
