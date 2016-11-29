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

class RecordingEngine : public EngineIface, public EngineStateMachine
{
public:
    RecordingEngine() = default;
    virtual ~RecordingEngine() = default;

    virtual void startRecording() override;
    virtual void startPlaying() override;

    virtual void stop() override;
    virtual void pause() override;
    virtual void resume() override;

    virtual void onTextAdded(int position, const char* text, int length, uhyper timestamp) override;
    virtual void onTextRemoved(int position, const char* text, int length, uhyper timestamp) override;

private:
    void onStartRecording();

    mutex engineGuard;
    ofstream recordStream;
};
