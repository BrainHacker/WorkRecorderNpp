// Singleton class implementation

#pragma once

template<typename T>
mutex Singleton<T>::guard = mutex();

template<typename T>
T* Singleton<T>::instance = 0;


//template<typename T>
//Singleton<T>::Singleton()
//    : instance(0)
//    , guard()
//{
//}

template<typename T>
Singleton<T>::~Singleton()
{
}

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
            instance = 0;
        }
    }
}
