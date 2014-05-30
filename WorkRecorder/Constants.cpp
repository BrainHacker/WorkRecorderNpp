// Constants class

#include "common.h"

namespace Constants
{
    // Plugin description
    const TCHAR* strPluginDisplayName = TEXT("Work Recorder");
    const TCHAR* strPluginShortName = TEXT("WorkRecorder");

    // Error descriptions
    const char* strNullPtr = "Null ptr";
    const char* strIndexOutOfRange = "Index out of range";

    // GUI
    //  Menu
    const TCHAR* strShowPlaybackWindow = TEXT("Show Playback Window");
    const TCHAR* strShowRecordingWindow = TEXT("Show Recording Window");

    //  Windows
    const TCHAR* strPlaybackWindowTitle = TEXT("Work Playback");
    const TCHAR* strRecordWindowTitle = TEXT("Work Recording");;

    const WCHAR* strPlayButton = L"\u25B6";
    const WCHAR* strPauseButton = L"\u2759\u2759";
    const WCHAR* strStopButton = L"\u25A0";

    const WCHAR* strPrevButton = L"\u23EE";
    const WCHAR* strBackButton = L"\u23EA";
    const WCHAR* strForwButton = L"\u23E9";
    const WCHAR* strNextButton = L"\u23ED";
} //namespace Constants
