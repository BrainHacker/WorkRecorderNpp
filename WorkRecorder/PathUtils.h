// Path utils

#pragma once

class PathUtils
{
public:
    static bool isFileExist(const TCHAR* fileName);
    static bool isFileReadable(const TCHAR* fileName);

private:
    enum AccessMode
    {
        amExist     = 0,
        amRead      = 2,
        amWrite     = 4,
        amReadWrite = 6,
    };

    static bool isAccessable(const TCHAR* fileName, AccessMode mode);
};