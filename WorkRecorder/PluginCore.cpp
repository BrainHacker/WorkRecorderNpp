// Plugin core class for maintaining of load/unload process

#include "common.h"

const TCHAR* PluginCore::strPluginName = TEXT("Work Recorder");
const TCHAR* PluginCore::strCommandNames[PluginCore::cTotal] =
{
    TEXT("Show Work Recorder"),
};

PluginCore::PluginCore()
{
    init();
}

void PluginCore::init()
{
    initCommand(&functionsArray[cShowMainDlg], strCommandNames[cShowMainDlg], onShowMainDlg);
}

void PluginCore::initCommand(FuncItem* item, const TCHAR* name, PFUNCPLUGINCMD pFunc,
    ShortcutKey* sk /*= 0*/, bool checkOnInit /*=false*/)
{
    assert(item, Constants::strNullPtr);

    lstrcpy(item->_itemName, name);
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

    *count = cTotal;
    return functionsArray;
}

void PluginCore::onShowMainDlg()
{
    const NppData& nppData = PluginCore::getInstance().getNppData();

    //// Open a new document
    //::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;

    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    //// Say hello now :
    //// Scintilla control has no Unicode mode, so we use (char *) here
    //::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");

    MainDlg dlg;
    dlg.DoModal();
}
