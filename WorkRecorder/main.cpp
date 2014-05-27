// Main file

#include "common.h"

void pluginInit(HANDLE hModule)
{
}

void pluginCleanUp()
{
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        pluginInit(hModule);
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

// Implementation of plugin interface

extern "C"
{
    __declspec(dllexport) void setInfo(NppData notpadPlusData)
    {
        PluginCore::getInstance().setNppData(notpadPlusData);
    }

    __declspec(dllexport) const TCHAR * getName()
    {
        return PluginCore::strPluginName;
    }

    __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
    {
        uint count = 0;
        FuncItem* functionsArray = PluginCore::getInstance().getFunctionsArray(&count);

        *nbF = (int)count;
        return functionsArray;
    }

    static void destroySingletons()
    {
        PluginCore::destroy();
    }

    __declspec(dllexport) void beNotified(SCNotification *notifyCode)
    {
        switch (notifyCode->nmhdr.code)
        {
        case NPPN_SHUTDOWN:
        {
            destroySingletons();
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
