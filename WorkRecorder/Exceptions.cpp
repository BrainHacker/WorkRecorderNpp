// Exception classes

#include "common.h"

ErrorException::ErrorException(const string& desc, const string& fileName, int line)
    : description()
{
    ostringstream stream;
    stream << "Error in file \"" << fileName << "\"\nLine " << line << "\n";
    stream << desc << "\n";

    description = stream.str();
}

const char* ErrorException::what() const
{
    return description.c_str();
}
