// Singleton class

#pragma once

template<typename T>
class Singleton
{
public:
	Singleton();
	virtual ~Singleton();

	T& getInstance();
	void destroy();

private:
	mutex guard;
	T* instance;
};