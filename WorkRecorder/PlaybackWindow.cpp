// 
// PlaybackWindow.cpp
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2017.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/dmitry-zakablukov/WorkRecorderNpp
//
// Work Recorder plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Work Recorder plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Work Recorder plugin. If not, see <http://www.gnu.org/licenses/>.
//

#include "common.h"

array<PlaybackWindow::SpeedInfo, PlaybackWindow::numSpeedCount> PlaybackWindow::speedArray =
{
    SpeedInfo{ TEXT("-10.0"), -10.0f  },
    SpeedInfo{ TEXT("-5.0"),  - 5.0f  },
    SpeedInfo{ TEXT("-2.5"),  - 2.5f  },
    SpeedInfo{ TEXT("-2.0"),  - 2.0f  },
    SpeedInfo{ TEXT("-1.5"),  - 1.5f  },
    SpeedInfo{ TEXT("-1.0"),  - 1.0f  },
    SpeedInfo{ TEXT("-0.5"),  - 0.5f  },
    SpeedInfo{ TEXT("-0.2"),  - 0.2f  },
    SpeedInfo{ TEXT("-0.1"),  - 0.1f  },
    SpeedInfo{ TEXT("0.0"),     0.0f  },
    SpeedInfo{ TEXT("0.1"),     0.1f  },
    SpeedInfo{ TEXT("0.2"),     0.2f  },
    SpeedInfo{ TEXT("0.5"),     0.5f  },
    SpeedInfo{ TEXT("1.0"),     1.0f  },
    SpeedInfo{ TEXT("1.5"),     1.5f  },
    SpeedInfo{ TEXT("2.0"),     2.0f  },
    SpeedInfo{ TEXT("2.5"),     2.5f  },
    SpeedInfo{ TEXT("5.0"),     5.0f  },
    SpeedInfo{ TEXT("10.0"),   10.0f  },
};

void PlaybackWindow::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

void PlaybackWindow::setEngine(EnginePtr&& engine)
{
    this->engine = move(engine);
}

LRESULT PlaybackWindow::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    GuiUtils::setSystemDefaultFont(*this);
    translateWindow(*this, IDD_PLAYBACKDLG);

    initButtons();
    initSpeedControl();
    initToolTips();

    setError(translate(IDS_ERR_RECORDFILENAMEEMPTY), false);
    
    DlgResize_Init(false, false, 0);
    return S_OK;
}

LRESULT PlaybackWindow::OnDestroy(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    // destroy image lists
    browseImageList.Destroy();
    warningImageList.Destroy();

    // destroy tooltips
    for (CToolTipCtrl& toolTip : toolTips)
    {
        if (toolTip.IsWindow())
        {
            toolTip.DestroyWindow();
        }
    }

    return S_OK;
}

LRESULT PlaybackWindow::OnClick(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    HWND focusedWindow = GetFocus();
    if (focusedWindow != *this && !IsChild(focusedWindow))
    {
        SetFocus();
    }

    return S_OK;
}

void PlaybackWindow::initButtons()
{
    using ButtonInfo = pair<uint, uint>; // (id, fontSize) 
    array<ButtonInfo, 4> infos =
    {
        ButtonInfo{ IDC_PLAY_PREVBUTTON,  10 },
        ButtonInfo{ IDC_PLAY_BACKBUTTON,  10 },
        ButtonInfo{ IDC_PLAY_FORWBUTTON,  10 },
        ButtonInfo{ IDC_PLAY_NEXTBUTTON,  10 },
    };

    for (const ButtonInfo& info : infos)
    {
        GuiUtils::changeControlFontSize(*this, info.first, info.second);
    }

    setButtonImages();
    enableControl(IDC_PLAY_WARNINGBUTTON, false);
}

void PlaybackWindow::setButtonImages()
{
    // set image for browse button
    CGdiPlusBitmapResource imageSource;
    imageSource.Load(IDR_CHOOSEFILEBITMAP, RT_RCDATA, PluginCore::getInstance().getModuleHandle());

    RECT rc;
    CWindow(GetDlgItem(IDC_PLAY_RECORDFILEEDIT)).GetWindowRect(&rc);
    uint size = rc.bottom - rc.top;

    imageSource.ResizeY(size);
    CBitmap imageBitmap = imageSource.GetHBITMAP(RGB(0, 0, 0));

    browseImageList.Create(size, size, ILC_COLOR32, 0, 4);
    browseImageList.Add(imageBitmap);

    browseButton.SetImageList(browseImageList);
    browseButton.SetImages(0, 1, 2, 3);
    browseButton.SubclassWindow(GetDlgItem(IDC_PLAY_BROWSEBUTTON));

    // set image for warning button
    size -= 2;
    warningImageList.Create(size, size, ILC_COLOR32, 1, 0);
    warningImageList.AddIcon(LoadIcon(PluginCore::getInstance().getModuleHandle(), (LPCTSTR)IDI_WARNINGICON));

    warningButton.SetImageList(warningImageList);
    warningButton.SetImages(0);
    warningButton.SubclassWindow(GetDlgItem(IDC_PLAY_WARNINGBUTTON));
}

void PlaybackWindow::initSpeedControl()
{
    uint currentSpeedIndex = 0;
    CComboBox box = GetDlgItem(IDC_PLAY_SPEEDCOMBOBOX);

    uint index = 0;
    for (const SpeedInfo& info : speedArray)
    {
        box.AddString(info.first);
        if (info.second == 1.0f)
        {
            currentSpeedIndex = index;
        }
        ++index;
    }

    box.SetCurSel(currentSpeedIndex);
}

void PlaybackWindow::initToolTips()
{
    using TooltipInfo = pair<uint, CString>;
    array<TooltipInfo, 10> infos =
    {
        TooltipInfo{ IDC_PLAY_RECORDFILEEDIT,  translate(IDS_TIP_PLAY_FILLRECORDNAME) },
        TooltipInfo{ IDC_PLAY_BROWSEBUTTON,    translate(IDS_TIP_PLAY_BROWSE)         },
        TooltipInfo{ IDC_PLAY_PLAYBUTTON,      translate(IDS_TIP_PLAY_PLAY)           },
        TooltipInfo{ IDC_PLAY_PAUSEBUTTON,     translate(IDS_TIP_PLAY_PAUSE)          },
        TooltipInfo{ IDC_PLAY_STOPBUTTON,      translate(IDS_TIP_PLAY_STOP)           },
        TooltipInfo{ IDC_PLAY_PREVBUTTON,      translate(IDS_TIP_PLAY_PREV)           },
        TooltipInfo{ IDC_PLAY_BACKBUTTON,      translate(IDS_TIP_PLAY_DECREASESPEED)  },
        TooltipInfo{ IDC_PLAY_FORWBUTTON,      translate(IDS_TIP_PLAY_INCREASESPEED)  },
        TooltipInfo{ IDC_PLAY_NEXTBUTTON,      translate(IDS_TIP_PLAY_NEXT)           },
        TooltipInfo{ IDC_PLAY_SPEEDCOMBOBOX,   translate(IDS_TIP_PLAY_CHANGESPEED)    },
    };

    for (TooltipInfo& tooltipInfo : infos)
    {
        CToolTipCtrl toolTip;
        toolTip.Create(*this, 0, (LPCTSTR)0, WS_POPUP | TTS_ALWAYSTIP);

        TOOLINFO info   = {};

        info.cbSize     = sizeof(TOOLINFO);
        info.hwnd       = *this;
        info.uFlags     = TTF_IDISHWND | TTF_SUBCLASS;
        info.uId        = (UINT_PTR)(HWND)GetDlgItem(tooltipInfo.first);
        info.lpszText   = tooltipInfo.second.GetBuffer();

        toolTip.AddTool(&info);
        toolTips.push_back(toolTip);
    }
}

LRESULT PlaybackWindow::OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    GuiUtils::onBrowseRecordFile(*this, IDC_PLAY_RECORDFILEEDIT);
    return S_OK;
}

LRESULT PlaybackWindow::OnRecordFileNameChanged(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    CEdit edit = GetDlgItem(IDC_PLAY_RECORDFILEEDIT);

    CString fileName;
    edit.GetWindowText(fileName);

    CString errorDesc;
    bool showErrorIcon = false;

    if (fileName.IsEmpty())
    {
        errorDesc = translate(IDS_ERR_RECORDFILENAMEEMPTY);
    }
    else if (!PathUtils::isFileExist(fileName))
    {
        errorDesc = translate(IDS_ERR_RECORDFILENOTEXIST);
        showErrorIcon = true;
    }
    else if (!PathUtils::isFileReadable(fileName))
    {
        errorDesc = translate(IDS_ERR_RECORDFILENOTREADABLE);
        showErrorIcon = true;
    }

    if (!errorDesc.IsEmpty())
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

void PlaybackWindow::setError(const CString& errorDesc /*= CString()*/,
    bool showErrorIcon /*= true*/)
{
    bool error = !errorDesc.IsEmpty();
    enableMediaButtons(!error);

    if (error)
    {
        showControl(IDC_PLAY_ERRORSTATIC);
        SetDlgItemText(IDC_PLAY_ERRORSTATIC, errorDesc);
        showControl(IDC_PLAY_WARNINGBUTTON);
    }
    else
    {
        showControl(IDC_PLAY_ERRORSTATIC, false);
        showControl(IDC_PLAY_WARNINGBUTTON, false);
    }
}

void PlaybackWindow::onReadyToPlay()
{
    setError();
    
    enableControl(IDC_PLAY_PAUSEBUTTON, false);
    enableControl(IDC_PLAY_STOPBUTTON, false);
}
