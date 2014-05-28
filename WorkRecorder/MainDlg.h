// Main Work Recorder dialog

class MainDlg
    : public Singleton<MainDlg>
    , public CDialogImpl<MainDlg>
    , public CDialogResize<MainDlg>
{
public:
    enum { IDD = IDD_MAINDIALOG };

    BEGIN_DLGRESIZE_MAP(MainDlg)
        DLGRESIZE_CONTROL(IDOK,     DLSZ_MOVE_X | DLSZ_MOVE_Y)
        DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X | DLSZ_MOVE_Y)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(MainDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        CHAIN_MSG_MAP(CDialogResize<MainDlg>)
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    MainDlg() = default;
    virtual ~MainDlg() = default;

    friend class Singleton<MainDlg>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
};
