// Main Work Recorder dialog

class MainDlg : public CDialogImpl<MainDlg>
{
public:
    enum { IDD = IDD_MAINDIALOG };

    BEGIN_MSG_MAP(MainDlg)
        MESSAGE_HANDLER(WM_CLOSE, OnClose)
    END_MSG_MAP()

    MainDlg() = default;
    virtual ~MainDlg() = default;

private:
    LRESULT OnClose(UINT msgId, WPARAM wP, LPARAM lP, BOOL& handled);
};