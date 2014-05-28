// Main Work Recorder dialog

class MainDlg : public Singleton<MainDlg>, public CDialogImpl<MainDlg>
{
public:
    enum { IDD = IDD_MAINDIALOG };

    BEGIN_MSG_MAP(MainDlg)
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    MainDlg() = default;
    virtual ~MainDlg() = default;

    friend class Singleton<MainDlg>;

private:
};
