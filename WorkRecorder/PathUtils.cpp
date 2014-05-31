// Path utils

#include "common.h"

//static
bool PathUtils::isFileExist(const TCHAR* fileName)
{
    return isAccessable(fileName, amExist);
}

//static
bool PathUtils::isFileReadable(const TCHAR* fileName)
{
    return isAccessable(fileName, amRead);
}

//static
bool PathUtils::isAccessable(const TCHAR* fileName, AccessMode mode)
{
    bool accessable = false;

#if defined(UNICODE)
    accessable = (_waccess(fileName, mode) == 0);
#else
    accessable = (_access(fileName, mode) == 0);
#endif //UNICODE

    return accessable;
}
