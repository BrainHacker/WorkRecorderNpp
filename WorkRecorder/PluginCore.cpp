// Plugin core class for maintaining of load/unload process

#include "common.h"

PluginCore::PluginCore()
{
}

void PluginCore::setModuleHandle(HINSTANCE handle)
{
    moduleHandle = handle;
}

HINSTANCE PluginCore::getModuleHandle() const
{
    return moduleHandle;
}

const TCHAR* PluginCore::getModuleName() const
{
    return moduleName;
}

void PluginCore::init()
{
    // init translation
    ::GetModuleFileName(moduleHandle, moduleName, MAX_PATH);
    CLocalization& localization = CLocalization::getInstance();

    localization.Load(moduleName);
    localization.Select(LANG_ENGLISH);

    // init module name
    TCHAR* fileName = PathFindFileName(moduleName);
    if (fileName != moduleName)
    {
        StringCchCopy(moduleName, MAX_PATH, fileName);
    }

    // init commands
    initCommand(&functionsArray[cShowPlaybackWindow],  translate(IDS_MENU_SHOWPLAYBACKWND),  onShowPlaybackWindow );
    initCommand(&functionsArray[cShowRecordingWindow], translate(IDS_MENU_SHOWRECORDINGWND), onShowRecordingWindow);
}

void PluginCore::initCommand(FuncItem* item, const CString& name, PFUNCPLUGINCMD pFunc,
    ShortcutKey* sk /*= 0*/, bool checkOnInit /*=false*/)
{
    assert(item, Constants::strNullPtr);
    StringCchCopy(item->_itemName, nbChar, name);

    item->_pFunc = pFunc;
    item->_pShKey = sk;
    item->_init2Check = checkOnInit;
}

void PluginCore::setNppData(const NppData& data)
{
    nppData = data;
}

const NppData& PluginCore::getNppData() const
{
    return nppData;
}

FuncItem* PluginCore::getFunctionsArray(uint* count)
{
    assert(count, Constants::strNullPtr);

    if (!initialized)
    {
        init();
        initialized = true;
    }

    *count = cTotal;
    return functionsArray;
}

//static
void PluginCore::onShowPlaybackWindow()
{
    HICON icon = LoadIcon(getInstance().getModuleHandle(), (LPCTSTR)IDI_PLAYBACKWINDOWICON);
    CString title = translate(IDS_TITLE_PLAYWND);
    showWindow<PlaybackWindow>(cShowPlaybackWindow, title, icon);
}

//static
void PluginCore::onShowRecordingWindow()
{
    HICON icon = LoadIcon(getInstance().getModuleHandle(), (LPCTSTR)IDI_RECORDWINDOWICON);
    CString title = translate(IDS_TITLE_RECORDWND);
    showWindow<RecordingWindow>(cShowRecordingWindow, title, icon);
}

//static
template<typename Wnd>
void PluginCore::showWindow(int id, const TCHAR* title, HICON icon)
{
    PluginCore& plugin = PluginCore::getInstance();
    Wnd& dlg = Wnd::getInstance();

    if (!dlg.IsWindow())
    {
        const NppData& nppData = plugin.getNppData();
        HWND parent = nppData._nppHandle;

        dlg.Create(parent);
        ::SendMessage(parent, NPPM_MODELESSDIALOG, MODELESSDIALOGADD, (LPARAM)(HWND)dlg);

        // fill dockable info
        tTbData	data = {};

        data.hClient       = (HWND)dlg;
        data.pszName       = (TCHAR*)title;
        data.dlgID         = id;
        data.uMask         = DWS_DF_CONT_RIGHT | DWS_ICONTAB;
        data.pszModuleName = plugin.getModuleName();
        data.hIconTab      = icon;
        
        ::SendMessage(parent, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);
    }

    dlg.show();
}
