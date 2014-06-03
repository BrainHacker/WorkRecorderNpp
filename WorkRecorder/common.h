#pragma once

// standard files
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
