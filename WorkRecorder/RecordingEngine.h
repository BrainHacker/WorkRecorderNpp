// 
// RecordingEngine.h
// Recording engine.
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

class RecordingEngine : public EngineIface
{
public:
    RecordingEngine() = default;
    virtual ~RecordingEngine();

    virtual void setRecordingOptions(const RecordingOptions& options) override;

    virtual void startRecording(const wstring& fileName) override;
    virtual void startPlaying(const wstring& fileName) override;

    virtual void stop() override;
    virtual void pause() override;
    virtual void resume() override;

    virtual void onTextAdded(int position, const char* text, int length, uhyper timestamp) override;
    virtual void onTextRemoved(int position, const char* text, int length, uhyper timestamp) override;

private:
    void onStartRecording(const wstring& fileName);
    void onStopRecording();

    static void playbackRoutine(const wstring& fileName, HWND scintillaHandle);

    mutex engineGuard;

    RecordingOptions options;
    ofstream recordStream;

    thread playbackThread;

    OpCodeInfo currentOpCode;
    int cursorPosition = 0;
};
