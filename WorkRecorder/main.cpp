// 
// main.cpp
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

void pluginInit(HANDLE moduleHandle)
{
    PluginCore::getInstance().setModuleHandle((HINSTANCE)moduleHandle);
    GdiPlusHelper::getInstance().init();
}

void pluginCleanUp()
{
    // destroy singletons
    PlaybackWindow::destroy();
    RecordingWindow::destroy();
    GdiPlusHelper::destroy();

    CLocalization::destroy();
    PluginCore::destroy();
}

BOOL APIENTRY DllMain(HANDLE moduleHandle, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        pluginInit(moduleHandle);
        break;

    case DLL_PROCESS_DETACH:
        pluginCleanUp();
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;
}

template<typename Wnd>
static void removePluginWindow(HWND parent)
{
    Wnd& dlg = Wnd::getInstance();
    if (dlg.IsWindow())
    {
        ::SendMessage(parent, NPPM_MODELESSDIALOG, MODELESSDIALOGREMOVE, (LPARAM)(HWND)dlg);
        dlg.DestroyWindow();
    }
}

static void onNppShutdown()
{
    HWND parent = PluginCore::getInstance().getNppData()._nppHandle;
    removePluginWindow<PlaybackWindow>(parent);
    removePluginWindow<RecordingWindow>(parent);

    GdiPlusHelper::getInstance().uninit();
}

static void addToolbarIcon(uint bitmapResourceId, uint cmdId)
{
    PluginCore& plugin = PluginCore::getInstance();
    HINSTANCE hinstance = plugin.getModuleHandle();

    uint count = 0;
    FuncItem* functions = plugin.getFunctionsArray(&count);
    assert(cmdId < count, Constants::strIndexOutOfRange);

    toolbarIcons info = {};
    info.hToolbarBmp = CreateMappedBitmap(hinstance, (INT_PTR)bitmapResourceId, 0, 0, 0);

    ::SendMessage(plugin.getNppData()._nppHandle, NPPM_ADDTOOLBARICON,
        (WPARAM)functions[cmdId]._cmdID, (LPARAM)&info);
}

// Implementation of plugin interface
extern "C"
{
    __declspec(dllexport) void setInfo(NppData notpadPlusData)
    {
        PluginCore::getInstance().setNppData(notpadPlusData);
    }

    __declspec(dllexport) const TCHAR * getName()
    {
        static CString pluginName = translate(IDS_PLUGIN_DISPLAYNAME);
        return pluginName;
    }

    __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
    {
        uint count = 0;
        FuncItem* functionsArray = PluginCore::getInstance().getFunctionsArray(&count);

        *nbF = (int)count;
        return functionsArray;
    }

    __declspec(dllexport) void beNotified(SCNotification *notifyCode)
    {
        switch (notifyCode->nmhdr.code)
        {
            case NPPN_TBMODIFICATION:
            {
                addToolbarIcon(IDB_PLAYBACKTOOLBARICON, PluginCore::cShowPlaybackWindow);
                addToolbarIcon(IDB_RECORDTOOLBARICON, PluginCore::cShowRecordingWindow);
            }
            break;

            case NPPN_SHUTDOWN:
            {
                onNppShutdown();
            }
            break;

            case SCN_MODIFIED:
            {
                if (notifyCode->modificationType == SC_MOD_INSERTTEXT)
                {
                    int i = 0;
                }
            }
            break;

            default:
            return;
        }
    }


    // Here you can process the Npp Messages 
    // I will make the messages accessible little by little, according to the need of plugin development.
    // Please let me know if you need to access to some messages :
    // http://sourceforge.net/forum/forum.php?forum_id=482781
    //
    __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
    {/*
     if (Message == WM_MOVE)
     {
     ::MessageBox(nullptr, "move", "", MB_OK);
     }
     */
        return TRUE;
    }

#ifdef UNICODE
    extern "C" __declspec(dllexport) BOOL isUnicode()
    {
        return TRUE;
    }
#endif //UNICODE
}
