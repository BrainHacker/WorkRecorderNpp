// Main Work Recorder dialog

class MainDlg
    : public Singleton<MainDlg>
    , public CDialogImpl<MainDlg>
    , public CDialogResize<MainDlg>
{
public:
    enum { IDD = IDD_MAINDIALOG };

    BEGIN_DLGRESIZE_MAP(MainDlg)
        DLGRESIZE_CONTROL(IDC_MAINDLGTABCTRL, DLSZ_SIZE_X | DLSZ_SIZE_Y)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(MainDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<MainDlg>)
        REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    MainDlg() = default;
    virtual ~MainDlg() = default;

    friend class Singleton<MainDlg>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);

    /// Inserts tab window
    void insertTab(CWindow tab, uint index, const TCHAR* name);

    CDialogTabCtrl tabControl;
    PlaybackTab playbackTab;
    RecordTab recordTab;
};
