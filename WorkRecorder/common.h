#pragma once

// standard files
#include <sstream>
#include <mutex>

using namespace std;

// WTL
#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include <atlstr.h>
#define _WTL_NO_CSTRING

// Windows
#include <Strsafe.h>
#include <Shlwapi.h>

// Framework files
#include "Types.h"
#include "Constants.h"
#include "Exceptions.h"
#include "Singleton.h"
#include "SingletonImpl.h"

// Notepad++ files
#include "menuCmdID.h"
#include "Docking.h"

// Plug-in files
#include "PluginInterface.h"
#include "PluginCore.h"

// GUI
#include "resource.h"
#include "GuiUtils.h"
#include "PlaybackWindow.h"
#include "RecordingWindow.h"
