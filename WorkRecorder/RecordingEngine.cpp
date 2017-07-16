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

RecordingEngine::~RecordingEngine()
{
    if (playbackThread.joinable())
    {
        playbackThread.join();
    }
}

void RecordingEngine::setRecordingOptions(const RecordingOptions& options)
{
    this->options = options;
}

void RecordingEngine::startRecording(const wstring& fileName)
{
    //assert(state == EngineState::idle, "Engine state change failure");
    setState(EngineState::recording);
    onStartRecording(fileName);
}

void RecordingEngine::startPlaying(const wstring& fileName)
{
    auto nppData = PluginCore::getInstance().getNppData();
    HWND nppHandle = nppData._nppHandle;

    int currentScintillaViewIndex = -1;
    ::SendMessage(nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintillaViewIndex);

    if (currentScintillaViewIndex == -1)
    {
        // todo: handle this situation
    }
    else
    {
        HWND scintillaHandle = (currentScintillaViewIndex ? nppData._scintillaSecondHandle : nppData._scintillaMainHandle);

        //assert(state == EngineState::idle, "Engine state change failure");
        setState(EngineState::playing);
        playbackThread = thread(playbackRoutine, fileName, scintillaHandle);
    }
}

void RecordingEngine::stop()
{
    if (getState() == EngineState::recording)
        onStopRecording();

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
        if (options.isCleanMode && length == 1)
        {
            size_t currentStringSize = currentOpCode.strField.size();

            // check for Typing
            if (cursorPosition == position)
            {
                if (currentOpCode.code == OperationCode::insertString && currentStringSize == 1)
                    currentOpCode.code = OperationCode::typeString;

                if (currentOpCode.code == OperationCode::typeString)
                {
                    currentOpCode.strField.push_back(*text);
                    ++cursorPosition;
                    return;
                }
            }

            // check for Pushing
            if (position + 1 == cursorPosition)
            {
                if (currentOpCode.code == OperationCode::insertString && currentStringSize == 1)
                    currentOpCode.code = OperationCode::pushString;

                if (currentOpCode.code == OperationCode::pushString)
                {
                    currentOpCode.strField.push_back(*text);
                    return;
                }
            }
        }

        if (!currentOpCode.isEmpty())
            OperationCodesUtils::format(recordStream, &currentOpCode);

        if (cursorPosition != position)
        {
            OpCodeInfo opCode;
            opCode.code = OperationCode::setCursorPosition;
            opCode.numField = position;
            OperationCodesUtils::format(recordStream, &opCode);

            cursorPosition = position;
        }

        currentOpCode.clear();
        currentOpCode.code = OperationCode::insertString;
        currentOpCode.strField = string(text, length);
        
        cursorPosition += length;
    }
}

void RecordingEngine::onTextRemoved(int position, const char* text, int length, uhyper timestamp)
{
    lock_guard<mutex> lock(engineGuard);
    if (getState() == EngineState::recording)
    {
        if (options.isCleanMode && length == 1)
        {
            size_t currentStringSize = currentOpCode.strField.size();

            // check for Untyping
            if (position + 1 == cursorPosition)
            {
                if (currentOpCode.code == OperationCode::removeString && currentStringSize == 1)
                    currentOpCode.code = OperationCode::untypeString;

                if (currentOpCode.code == OperationCode::untypeString)
                {
                    currentOpCode.strField.insert(currentOpCode.strField.begin(), *text);
                    --cursorPosition;
                    return;
                }
            }

            // check for Pulling
            if (position == cursorPosition)
            {
                if (currentOpCode.code == OperationCode::removeString && currentStringSize == 1)
                    currentOpCode.code = OperationCode::pullString;

                if (currentOpCode.code == OperationCode::pullString)
                {
                    currentOpCode.strField.insert(currentOpCode.strField.begin(), *text);
                    return;
                }
            }
        }

        if (!currentOpCode.isEmpty())
            OperationCodesUtils::format(recordStream, &currentOpCode);

        if (cursorPosition != position + length)
        {
            OpCodeInfo opCode;
            opCode.code = OperationCode::setCursorPosition;
            opCode.numField = position + length; //bug!
            OperationCodesUtils::format(recordStream, &opCode);
        }

        currentOpCode.clear();
        currentOpCode.code = OperationCode::removeString;
        currentOpCode.strField = string(text, length);

        cursorPosition = position;
    }
}

void RecordingEngine::onStartRecording(const wstring& fileName)
{
    recordStream = ofstream(fileName, ios_base::binary);

    currentOpCode.clear();
    cursorPosition = 0;
}

void RecordingEngine::onStopRecording()
{
    if (!currentOpCode.isEmpty())
        OperationCodesUtils::format(recordStream, &currentOpCode);

    recordStream.close();
    recordStream = ofstream();
}

// static
void RecordingEngine::playbackRoutine(const wstring& fileName, HWND scintillaHandle)
{
    const auto numTimeout = chrono::milliseconds(100);

    ifstream inputStream = ifstream(fileName, ios::binary);
    assert(inputStream.is_open(), "IO error");

    while (inputStream.peek() != EOF)
    {
        OpCodeInfo opCode = OperationCodesUtils::parse(inputStream);
        switch (opCode.code)
        {
        case OperationCode::setCursorPosition:
            ::SendMessage(scintillaHandle, SCI_GOTOPOS, (WPARAM)opCode.numField, 0);
            break;

        case OperationCode::insertString:
            ::SendMessage(scintillaHandle, SCI_ADDTEXT, opCode.strField.size(), (LPARAM)opCode.strField.c_str());
            ::SendMessage(scintillaHandle, SCI_SCROLLCARET, 0, 0);
            break;

        case OperationCode::removeString:
            //todo
            break;

        case OperationCode::typeString:
            for (auto c : opCode.strField)
            {
                ::SendMessage(scintillaHandle, SCI_ADDTEXT, 1, (LPARAM)&c);
                ::SendMessage(scintillaHandle, SCI_SCROLLCARET, 0, 0);
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            break;
        }
    }
}
