// Playback tab

#include "common.h"

PlaybackWindow::SpeedInfo PlaybackWindow::speedArray[PlaybackWindow::numSpeedCount] =
{
    { TEXT("-10.0"), -10.0f  },
    { TEXT("-5.0"),  - 5.0f  },
    { TEXT("-2.5"),  - 2.5f  },
    { TEXT("-2.0"),  - 2.0f  },
    { TEXT("-1.5"),  - 1.5f  },
    { TEXT("-1.0"),  - 1.0f  },
    { TEXT("-0.5"),  - 0.5f  },
    { TEXT("-0.2"),  - 0.2f  },
    { TEXT("-0.1"),  - 0.1f  },
    { TEXT("0.0"),     0.0f  },
    { TEXT("0.1"),     0.1f  },
    { TEXT("0.2"),     0.2f  },
    { TEXT("0.5"),     0.5f  },
    { TEXT("1.0"),     1.0f  },
    { TEXT("1.5"),     1.5f  },
    { TEXT("2.0"),     2.0f  },
    { TEXT("2.5"),     2.5f  },
    { TEXT("5.0"),     5.0f  },
    { TEXT("10.0"),   10.0f  },
};

void PlaybackWindow::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

LRESULT PlaybackWindow::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    GuiUtils::setSystemDefaultFont(*this);

    initButtons();
    initSpeedControl();

    setError(Constants::strRecordFileNameEmpty, false);

    CGdiPlusBitmapResource imageSource;
    imageSource.Load(IDR_CHOOSEFILEBITMAP, RT_RCDATA, PluginCore::getInstance().getModuleHandle());

    RECT rc;
    CWindow(GetDlgItem(IDC_PLAY_RECORDFILEEDIT)).GetWindowRect(&rc);
    uint size = rc.bottom - rc.top;

    imageSource.ResizeY(size);
    CBitmap imageBitmap = imageSource.GetHBITMAP(RGB(0, 0, 0));

    imageList.Create(size, size, ILC_COLOR32, 0, 4);
    imageList.Add(imageBitmap);

    browseButton.SetImageList(imageList);
    browseButton.SetImages(0, 1, 2);
    browseButton.SubclassWindow(GetDlgItem(IDC_PLAY_BROWSEBUTTON));
    browseButton.SetBitmapButtonExtendedStyle(browseButton.GetBitmapButtonExtendedStyle() | BMPBTN_HOVER);
    //browseButton.SizeToImage();
    
    DlgResize_Init(false, false, 0);
    return S_OK;
}

LRESULT PlaybackWindow::OnClick(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    SetFocus();
    return S_OK;
}

void PlaybackWindow::initButtons()
{
    using namespace Constants;

    typedef struct 
    {
        uint id;
        const WCHAR* text;
        uint fontSize;
    } ButtonInfo;

    ButtonInfo infos[] =
    {
        { IDC_PLAY_PLAYBUTTON,  strPlayButton,   9 },
        { IDC_PLAY_PAUSEBUTTON, strPauseButton,  9 },
        { IDC_PLAY_STOPBUTTON,  strStopButton,   9 },
        { IDC_PLAY_PREVBUTTON,  strPrevButton,  10 },
        { IDC_PLAY_BACKBUTTON,  strBackButton,  10 },
        { IDC_PLAY_FORWBUTTON,  strForwButton,  10 },
        { IDC_PLAY_NEXTBUTTON,  strNextButton,  10 },
    };

    uint count = sizeof(infos) / sizeof(ButtonInfo);
    while (count--)
    {
        const ButtonInfo& info = infos[count];
        setButtonText(info.id, info.text, true, info.fontSize);
    }
}

void PlaybackWindow::setButtonText(uint id, const WCHAR* text,
    bool changeFont /*= true*/, uint fontSize /*= 9*/)
{
    CWindow button = GetDlgItem(id);
    button.SetWindowText(text);

    if (changeFont)
    {
        CFontHandle font = button.GetFont();
        CLogFont logFont;
        font.GetLogFont(&logFont);

        logFont.SetHeight(fontSize);
        font = logFont.CreateFontIndirect();
        button.SetFont(font);
    }
}

void PlaybackWindow::initSpeedControl()
{
    uint currentSpeedIndex = 0;
    CComboBox box = GetDlgItem(IDC_PLAY_SPEEDCOMBOBOX);

    for (uint index = 0; index < numSpeedCount; ++index)
    {
        const SpeedInfo& info = speedArray[index];
        box.AddString(info.displayText);

        if (info.value == 1.0f)
        {
            currentSpeedIndex = index;
        }
    }

    box.SetCurSel(currentSpeedIndex);
}

LRESULT PlaybackWindow::OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    const TCHAR* strDefaultExtension = TEXT("");
    const TCHAR* strFileName = TEXT("");
    DWORD flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
    const TCHAR* strFilter = Constants::strFileDialogFilter;

    CFileDialog dlg(TRUE, strDefaultExtension, strFileName, flags, strFilter, *this);
    // TODO: fill initial folder and file name based on the previous choice

    INT_PTR answer = dlg.DoModal();
    if (answer == IDOK)
    {
        CEdit edit = GetDlgItem(IDC_PLAY_RECORDFILEEDIT);
        edit.SetWindowText(dlg.m_szFileName);

        int length = edit.GetWindowTextLength();
        edit.SetSel(length, length);
    }

    return S_OK;
}

LRESULT PlaybackWindow::OnRecordFileNameChanged(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    CEdit edit = GetDlgItem(IDC_PLAY_RECORDFILEEDIT);

    CString fileName;
    edit.GetWindowText(fileName);

    const TCHAR* errorDesc = 0;
    bool showErrorIcon = false;

    if (fileName.IsEmpty())
    {
        errorDesc = Constants::strRecordFileNameEmpty;
    }
    else if (!PathUtils::isFileExist(fileName))
    {
        errorDesc = Constants::strRecordFileNotExist;
        showErrorIcon = true;
    }
    else if (!PathUtils::isFileReadable(fileName))
    {
        errorDesc = Constants::strRecordFileNotReadable;
        showErrorIcon = true;
    }

    if (errorDesc)
    {
        setError(errorDesc, showErrorIcon);
    }
    else
    {
        // ready to play
        onReadyToPlay();
    }

    return S_OK;
}

void PlaybackWindow::enableMediaButtons(bool enable /*= true*/)
{
    typedef struct
    {
        uint id;
        bool enabled;
    } ControlInfo;

    ControlInfo infos[] =
    {
        { IDC_PLAY_PLAYBUTTON,    enable },
        { IDC_PLAY_PAUSEBUTTON,   enable },
        { IDC_PLAY_STOPBUTTON,    enable },
        { IDC_PLAY_PREVBUTTON,    enable },
        { IDC_PLAY_BACKBUTTON,    enable },
        { IDC_PLAY_FORWBUTTON,    enable },
        { IDC_PLAY_NEXTBUTTON,    enable },
        { IDC_PLAY_SPEEDCOMBOBOX, enable },
    };

    uint count = sizeof(infos) / sizeof(ControlInfo);
    while (count--)
    {
        const ControlInfo& info = infos[count];
        enableControl(info.id, info.enabled);
    }
}

void PlaybackWindow::enableControl(uint id, bool enable /*= true*/)
{
    CWindow wnd = GetDlgItem(id);
    wnd.EnableWindow(enable);
}

void PlaybackWindow::showControl(uint id, bool show /*= true*/)
{
    CWindow wnd = GetDlgItem(id);
    wnd.ShowWindow(show ? SW_SHOW : SW_HIDE);
}

void PlaybackWindow::setError(const TCHAR* errorDesc /*= 0*/,
    bool showErrorIcon /*= true*/)
{
    bool error = (errorDesc != 0);

    enableMediaButtons(!error);
    if (error)
    {
        showControl(IDC_PLAY_ERRORSTATIC);
        SetDlgItemText(IDC_PLAY_ERRORSTATIC, errorDesc);
    }
    else
    {
        showControl(IDC_PLAY_ERRORSTATIC, false);
    }
}

void PlaybackWindow::onReadyToPlay()
{
    setError();
    
    enableControl(IDC_PLAY_PAUSEBUTTON, false);
    enableControl(IDC_PLAY_STOPBUTTON, false);
}
