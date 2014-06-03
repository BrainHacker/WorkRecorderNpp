// Main file

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
            addToolbarIcon(IDB_RECORDTOOLBARICON,   PluginCore::cShowRecordingWindow);
        }
        break;

        case NPPN_SHUTDOWN:
        {
            onNppShutdown();
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
     ::MessageBox(NULL, "move", "", MB_OK);
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
