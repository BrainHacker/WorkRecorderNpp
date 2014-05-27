// Plugin core class for maintaining of load/unload process

#pragma once

class PluginCore : public Singleton<PluginCore>
{
public:
    void setNppData(const NppData& data);
    const NppData& getNppData() const;

    enum Commands
    {
        cShowMainDlg = 0,
        cTotal,
    };

    FuncItem* getFunctionsArray(uint* count);

    /// Commands itself
    static void onShowMainDlg();

    static const TCHAR* strPluginName;

protected:
    PluginCore();

    /// Don't forget to deallocate shortcuts if any
    ~PluginCore() = default;

    friend class Singleton<PluginCore>;

private:
    /// Plugin initialization
    void init();

    /// Plugin command initialization
    /// @param item - command item for Npp
    /// @param name - the command name showed in plugin menu
    /// @param pFunc - function associated with command
    /// @param sk - shortcut to trigger this command
    /// @param checkOnInit - make this menu item be checked visually
    void initCommand(FuncItem* item, const TCHAR* name, PFUNCPLUGINCMD pFunc,
        ShortcutKey* sk = 0, bool checkOnInit = false);

    // The plugin data that Notepad++ needs
    FuncItem functionsArray[cTotal];

    // The data of Notepad++ that can be used in plugin commands
    NppData nppData;

    static const TCHAR* strCommandNames[cTotal];
};