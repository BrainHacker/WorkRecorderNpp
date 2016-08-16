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

    DlgResize_Init(false, false, 0);
    return S_OK;
}
