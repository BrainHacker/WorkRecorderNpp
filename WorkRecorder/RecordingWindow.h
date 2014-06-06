// 
// RecordingWindow.h
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2014.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/BrainHacker/WorkRecorderNpp
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
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(RecordingWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
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

    EnginePtr engine;
};
