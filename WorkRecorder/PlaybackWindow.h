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
        DLGRESIZE_CONTROL(IDC_PLAY_CHOOSERECORDSTATIC, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_RECORDFILEEDIT, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_BROWSEBUTTON, DLSZ_MOVE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_CONTROLSSTATIC, DLSZ_SIZE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(PlaybackWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnClick)
        COMMAND_ID_HANDLER(IDC_PLAY_BROWSEBUTTON, OnBrowseRecordFile)
        COMMAND_HANDLER(IDC_PLAY_RECORDFILEEDIT, EN_CHANGE, OnRecordFileNameChanged)
        CHAIN_MSG_MAP(CDialogResize<PlaybackWindow>)
        //REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    PlaybackWindow() = default;
    virtual ~PlaybackWindow() = default;

    friend class Singleton<PlaybackWindow>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
    LRESULT OnClick(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);

    /// Command handlers
    LRESULT OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled);
    LRESULT OnRecordFileNameChanged(WORD code, WORD id, HWND hwnd, BOOL& handled);

    /// Init controls
    void initButtons();
    void setButtonText(uint id, const WCHAR* text, bool changeFont = true, uint fontSize = 9);

    void initSpeedControl();

    /// Enable all media buttons
    void enableMediaButtons(bool enable = true);
    void enableControl(uint id, bool enable = true);

    /// Playback state controlling
    void onReadyToPlay();

    /// Error handling
    /// @param errorDesc - error description, if 0 error message will be hided
    void setError(const TCHAR* errorDesc = 0, bool showErrorIcon = true);

    typedef struct 
    {
        const TCHAR* displayText;
        float value;
    } SpeedInfo;

    static const uint numSpeedCount = 19;
    static SpeedInfo speedArray[numSpeedCount];
};
