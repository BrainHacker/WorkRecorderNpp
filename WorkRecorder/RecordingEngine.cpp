// 
// RecordingEngine.cpp
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

#include "common.h"

void RecordingEngine::startRecording()
{
    assert(state == State::idle, "Engine state change failure");
    state = State::recording;
    onStartRecording();
}

void RecordingEngine::startPlaying()
{
    assert(state == State::idle, "Engine state change failure");
    state = State::playing;
}

void RecordingEngine::stop()
{
    state = State::idle;
}

void RecordingEngine::pause()
{
    if (state == State::playing)
    {
        state = State::playingPaused;
    }
    else if (state == State::recording)
    {
        state = State::recordingPaused;
    }
    else
        assert(false, "Engine state change failure");
}

void RecordingEngine::resume()
{
    if (state == State::playingPaused)
    {
        state = State::playing;
    }
    else if (state == State::recordingPaused)
    {
        state = State::recording;
    }
    else
        assert(state == State::idle, "Engine state change failure");
}

void RecordingEngine::onTextAdded(int position, const char* text, int length, uhyper timestamp)
{
    lock_guard<mutex> lock(engineGuard);
    if (state == State::recording)
    {
        //todo
        OpCodeInfo opCode;
        opCode.code = OperationCode::setCursorPosition;
        opCode.numField = position;
        OperationCodesUtils::format(recordStream, opCode);

        opCode.code = OperationCode::insertString;
        opCode.numField = undefined(opCode.numField);
        opCode.strField = string(text, length);
        OperationCodesUtils::format(recordStream, opCode);
    }
}

void RecordingEngine::onTextRemoved(int position, const char* text, int length, uhyper timestamp)
{
    lock_guard<mutex> lock(engineGuard);
    if (state == State::recording)
    {
        //todo
        OpCodeInfo opCode;
        opCode.code = OperationCode::setCursorPosition;
        opCode.numField = position;
        OperationCodesUtils::format(recordStream, opCode);

        opCode.code = OperationCode::removeString;
        opCode.numField = undefined(opCode.numField);
        opCode.strField = string(text, length);
        OperationCodesUtils::format(recordStream, opCode);
    }
}

void RecordingEngine::onStartRecording()
{
    recordStream = ofstream("work.rec");
}
