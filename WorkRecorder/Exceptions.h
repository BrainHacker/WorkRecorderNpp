// Exception classes

#pragma once

#define assert(condition, message) \
    if (!(condition)) \
        throw ErrorException((message), __FILE__, __LINE__);

class ErrorException : public exception
{
public:
    ErrorException(const string& desc, const string& fileName, int line);
    virtual ~ErrorException() = default;

    virtual const char* what() const;

private:
    string description;
};