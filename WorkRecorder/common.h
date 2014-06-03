// 
// common.h
// All includes in one place for using PCH.
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

// standard files
#include <list>
#include <sstream>
#include <mutex>

using namespace std;

// WTL
#include <atlbase.h>
#include <atlapp.h>
#include <atlcoll.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atldlgs.h>

#include <atlstr.h>
#define _WTL_NO_CSTRING

// Windows
#include <Strsafe.h>
#include <Shlwapi.h>
#include <gdiplus.h>

// Framework files
#include "Types.h"
#include "Constants.h"
#include "Exceptions.h"
#include "Singleton.h"
#include "SingletonImpl.h"
#include "PathUtils.h"

// Notepad++ files
#include "menuCmdID.h"
#include "Docking.h"

// Plug-in files
#include "PluginInterface.h"
#include "PluginCore.h"

// GUI
#include "resource.h"
#include "GdiPlusHelper.h"
#include "CGdiPlusBitmap.h"
#include "CButtonWithImage.h"
#include "Localization.h"
#include "GuiUtils.h"
#include "PlaybackWindow.h"
#include "RecordingWindow.h"
