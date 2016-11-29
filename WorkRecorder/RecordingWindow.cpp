// 
// RecordingWindow.cpp
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

void RecordingWindow::show(bool showFlag /*= true*/)
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    ::SendMessage(parent, showFlag ? NPPM_DMMSHOW : NPPM_DMMHIDE, 0, (LPARAM)m_hWnd);
}

void RecordingWindow::setEngine(EnginePtr engine)
{
    this->engine = engine;
}

LRESULT RecordingWindow::OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    GuiUtils::setSystemDefaultFont(*this);
    translateWindow(*this, IDD_RECORDINGDLG);

    setButtonImages();

    DlgResize_Init(false, false, 0);
    return S_OK;
}

void RecordingWindow::setButtonImages()
{
    CGdiPlusBitmapResource imageSource;
    imageSource.Load(IDR_CHOOSEFILEBITMAP, RT_RCDATA, PluginCore::getInstance().getModuleHandle());

    RECT rc;
    CWindow(GetDlgItem(IDC_RECORD_RECORDFILEEDIT)).GetWindowRect(&rc);
    uint size = rc.bottom - rc.top;

    imageSource.ResizeY(size);
    CBitmap imageBitmap = imageSource.GetHBITMAP(RGB(0, 0, 0));

    browseImageList.Create(size, size, ILC_COLOR32, 0, 4);
    browseImageList.Add(imageBitmap);

    browseButton.SetImageList(browseImageList);
    browseButton.SetImages(0, 1, 2, 3);
    browseButton.SubclassWindow(GetDlgItem(IDC_RECORD_BROWSEBUTTON));
}

LRESULT RecordingWindow::OnDestroy(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled)
{
    browseImageList.Destroy();
    return S_OK;
}

LRESULT RecordingWindow::OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    GuiUtils::onBrowseRecordFile(*this, IDC_RECORD_RECORDFILEEDIT);
    return S_OK;
}

LRESULT RecordingWindow::OnRecordButtonPush(WORD code, WORD id, HWND hwnd, BOOL& handled)
{
    engine->startRecording();
    return S_OK;
}
