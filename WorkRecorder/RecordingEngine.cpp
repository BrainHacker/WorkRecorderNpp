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

void RecordingEngine::startRecording(const wstring& fileName)
{
    //assert(state == EngineState::idle, "Engine state change failure");
    setState(EngineState::recording);
    onStartRecording(fileName);
}

void RecordingEngine::startPlaying(const wstring& fileName)
{
    //assert(state == EngineState::idle, "Engine state change failure");
    setState(EngineState::playing);
}

void RecordingEngine::stop()
{
    setState(EngineState::idle);
}

void RecordingEngine::pause()
{
    //todo
}

void RecordingEngine::resume()
{
    //todo
}

void RecordingEngine::onTextAdded(int position, const char* text, int length, uhyper timestamp)
{
    lock_guard<mutex> lock(engineGuard);
    if (getState() == EngineState::recording)
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
    if (getState() == EngineState::recording)
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

void RecordingEngine::onStartRecording(const wstring& fileName)
{
    recordStream = ofstream(fileName);
}
