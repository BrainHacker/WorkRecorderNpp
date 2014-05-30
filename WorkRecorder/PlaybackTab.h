// Playback tab

#pragma once

class PlaybackTab
    : public CDialogImpl<PlaybackTab>
    , public CDialogResize<PlaybackTab>
{
public:
    enum { IDD = IDD_PLAYBACKTAB };

    BEGIN_DLGRESIZE_MAP(PlaybackTab)
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(PlaybackTab)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<PlaybackTab>)
    END_MSG_MAP()

    PlaybackTab() = default;
    virtual ~PlaybackTab() = default;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
};
