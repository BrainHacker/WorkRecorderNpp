// Playback tab

#pragma once

class PlaybackWindow
    : public Singleton<PlaybackWindow>
    , public CDialogImpl<PlaybackWindow>
    , public CDialogResize<PlaybackWindow>
{
public:
    enum { IDD = IDD_PLAYBACKDLG };

    BEGIN_DLGRESIZE_MAP(PlaybackWindow)
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(PlaybackWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<PlaybackWindow>)
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    PlaybackWindow() = default;
    virtual ~PlaybackWindow() = default;

    friend class Singleton<PlaybackWindow>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
};
