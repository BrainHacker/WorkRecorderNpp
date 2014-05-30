// Playback tab

#include "common.h"

void PlaybackWindow::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

LRESULT PlaybackWindow::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    GuiUtils::setSystemDefaultFont(*this);
    initButtons();

    DlgResize_Init(false, false, 0);
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
