// 
// PluginCore.h
// Plugin core class for maintaining of load/unload process
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

    EnginePtr getEngine() const;

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

    EnginePtr engine;
};