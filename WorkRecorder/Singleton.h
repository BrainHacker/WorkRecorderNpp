// Singleton class

#pragma once

template<typename T>
class Singleton
{
public:
    Singleton() = default;
    virtual ~Singleton();

    static T& getInstance();
    static void destroy();

private:
    static mutex guard;
    static T* instance;
};