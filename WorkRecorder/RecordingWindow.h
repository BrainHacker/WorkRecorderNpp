// 
// RecordingWindow.h
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

#pragma once

class RecordingWindow
    : public Singleton<RecordingWindow>
    , public CDialogImpl<RecordingWindow>
    , public CDialogResize<RecordingWindow>
{
public:
    enum { IDD = IDD_RECORDINGDLG };

    BEGIN_DLGRESIZE_MAP(RecordingWindow)
        DLGRESIZE_CONTROL(IDC_RECORD_CHOOSERECORDSTATIC, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_RECORD_RECORDFILEEDIT, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_RECORD_BROWSEBUTTON, DLSZ_MOVE_X)
        DLGRESIZE_CONTROL(IDC_RECORD_STATESTATIC, DLSZ_SIZE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(RecordingWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(IDC_RECORD_BROWSEBUTTON, OnBrowseRecordFile)
        COMMAND_ID_HANDLER(IDC_RECORD_TOGGLEBUTTON, OnRecordButtonPush)
        CHAIN_MSG_MAP(CDialogResize<RecordingWindow>)
    END_MSG_MAP()

    void show(bool showFlag = true);

    void setEngine(EnginePtr engine);

protected:
    RecordingWindow() = default;
    virtual ~RecordingWindow() = default;

    friend class Singleton<RecordingWindow>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
    LRESULT OnDestroy(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);

    /// Command handlers
    LRESULT OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled);
    LRESULT OnRecordButtonPush(WORD code, WORD id, HWND hwnd, BOOL& handled);

    void setButtonImages();

    CButtonWithImage browseButton = CButtonWithImage(BMPBTN_AUTOSIZE | BMPBTN_HOVER);
    CImageList browseImageList;

    EnginePtr engine;
};
