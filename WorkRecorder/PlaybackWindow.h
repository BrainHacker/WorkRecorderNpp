// 
// PlaybackWindow.h
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

class PlaybackWindow
    : public Singleton<PlaybackWindow>
    , public CDialogImpl<PlaybackWindow>
    , public CDialogResize<PlaybackWindow>
{
public:
    enum { IDD = IDD_PLAYBACKDLG };

    BEGIN_DLGRESIZE_MAP(PlaybackWindow)
        DLGRESIZE_CONTROL(IDC_PLAY_CHOOSERECORDSTATIC, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_RECORDFILEEDIT, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_BROWSEBUTTON, DLSZ_MOVE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_CONTROLSSTATIC, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_PLAY_ERRORSTATIC, DLSZ_SIZE_X)
    END_DLGRESIZE_MAP()

    BEGIN_MSG_MAP(PlaybackWindow)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnClick)
        COMMAND_ID_HANDLER(IDC_PLAY_BROWSEBUTTON, OnBrowseRecordFile)
        COMMAND_HANDLER(IDC_PLAY_RECORDFILEEDIT, EN_CHANGE, OnRecordFileNameChanged)
        CHAIN_MSG_MAP(CDialogResize<PlaybackWindow>)
    END_MSG_MAP()

    void show(bool showFlag = true);

protected:
    PlaybackWindow() = default;
    virtual ~PlaybackWindow() = default;

    friend class Singleton<PlaybackWindow>;

private:
    /// Message handlers
    LRESULT OnInitDialog(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
    LRESULT OnDestroy(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);
    LRESULT OnClick(UINT msgId, WPARAM wP, LPARAM lp, BOOL& handled);

    /// Command handlers
    LRESULT OnBrowseRecordFile(WORD code, WORD id, HWND hwnd, BOOL& handled);
    LRESULT OnRecordFileNameChanged(WORD code, WORD id, HWND hwnd, BOOL& handled);

    /// Init controls
    void initButtons();
    void changeControlTextSize(uint id, uint fontSize);
    void setButtonImages();

    void initSpeedControl();

    /// Enable all media buttons
    void enableMediaButtons(bool enable = true);

    void enableControl(uint id, bool enable = true);
    void showControl(uint id, bool show = true);

    /// Playback state controlling
    void onReadyToPlay();

    /// Error handling
    /// @param errorDesc - error description, if 0 error message will be hided
    void setError(const CString& errorDesc = CString(), bool showErrorIcon = true);

    typedef struct 
    {
        const TCHAR* displayText;
        float value;
    } SpeedInfo;

    static const uint numSpeedCount = 19;
    static SpeedInfo speedArray[numSpeedCount];

    CButtonWithImage browseButton = CButtonWithImage(BMPBTN_AUTOSIZE | BMPBTN_HOVER);
    CImageList browseImageList;

    CButtonWithImage warningButton;
    CImageList warningImageList;
};
