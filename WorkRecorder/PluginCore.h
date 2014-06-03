// Plugin core class for maintaining of load/unload process

#pragma once

class PluginCore : public Singleton<PluginCore>
{
public:
    void setModuleHandle(HINSTANCE handle);
    HINSTANCE getModuleHandle() const;

    const TCHAR* getModuleName() const;

    void setNppData(const NppData& data);
    const NppData& getNppData() const;

    enum Commands
    {
        cShowPlaybackWindow = 0,
        cShowRecordingWindow,
        cTotal,
    };

    FuncItem* getFunctionsArray(uint* count);

    /// Commands itself
    static void onShowPlaybackWindow();
    static void onShowRecordingWindow();

    template<typename Wnd>
    static void showWindow(int id, const TCHAR* title, HICON icon);

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
    void initCommand(FuncItem* item, const CString& name, PFUNCPLUGINCMD pFunc,
        ShortcutKey* sk = 0, bool checkOnInit = false);

    bool initialized = false;

    // The plugin data that Notepad++ needs
    FuncItem functionsArray[cTotal];

    // The data of Notepad++ that can be used in plugin commands
    NppData nppData = NppData{};

    HINSTANCE moduleHandle = 0;
    TCHAR moduleName[MAX_PATH];
};