// 
// EngineIface.h
// Engine interface.
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

class EngineIface
{
public:
    virtual ~EngineIface() = default;

    // todo: move to separate class for State handling
    virtual void startRecording() = 0;
    virtual void startPlaying() = 0;

    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void onTextAdded(int position, const char* text, int length, uhyper timestamp) = 0;
    virtual void onTextRemoved(int position, const char* text, int length, uhyper timestamp) = 0;
};

typedef shared_ptr<EngineIface> EnginePtr;
