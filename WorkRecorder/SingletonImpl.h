// 
// SingletonImpl.h
//
// This file is part of Work Recorder plugin for Notepad++.
// Copyright (c) Dmitry Zakablukov, 2013-2014.
// E-mail: dmitriy.zakablukov@gmail.com
// Web: https://github.com/BrainHacker/WorkRecorderNpp
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

template<typename T>
mutex Singleton<T>::guard;

template<typename T>
T* Singleton<T>::instance = nullptr;

//static
template<typename T>
T& Singleton<T>::getInstance()
{
    if (instance)
    {
        return *instance;
    }
    else
    {
        lock_guard<mutex> lock(guard);
        if (instance)
        {
            return *instance;
        }
        else
        {
            instance = new T();
            return *instance;
        }
    }
}

//static
template<typename T>
void Singleton<T>::destroy()
{
    if (instance)
    {
        lock_guard<mutex> lock(guard);
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }
}
