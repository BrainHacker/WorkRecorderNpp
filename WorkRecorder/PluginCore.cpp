// Plugin core class for maintaining of load/unload process

#include "common.h"

const TCHAR* PluginCore::strCommandNames[PluginCore::cTotal] =
{
    TEXT("Show Work Recorder"),
};

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
    // init module name
    ::GetModuleFileName(moduleHandle, moduleName, MAX_PATH);
    TCHAR* fileName = PathFindFileName(moduleName);

    if (fileName != moduleName)
    {
        StringCchCopy(moduleName, MAX_PATH, fileName);
    }

    // init commands
    initCommand(&functionsArray[cShowMainDlg], strCommandNames[cShowMainDlg], onShowMainDlg);
}

void PluginCore::initCommand(FuncItem* item, const TCHAR* name, PFUNCPLUGINCMD pFunc,
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

void PluginCore::onShowMainDlg()
{
    PluginCore& plugin = PluginCore::getInstance();
    MainDlg& dlg = MainDlg::getInstance();

    if (dlg.IsWindow())
    {
        dlg.show();
    }
    else
    {
        const NppData& nppData = plugin.getNppData();
        HWND parent = nppData._nppHandle;

        dlg.Create(parent);
        ::SendMessage(parent, NPPM_MODELESSDIALOG, MODELESSDIALOGADD, (LPARAM)(HWND)dlg);

        // fill dockable info
        tTbData	data = {};

        data.hClient       = (HWND)dlg;
        data.pszName       = (TCHAR*)Constants::strPluginDisplayName;
        data.dlgID         = cShowMainDlg;
        data.uMask         = DWS_DF_CONT_RIGHT;
        data.pszModuleName = plugin.getModuleName();
        
        ::SendMessage(parent, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);
    }

}
