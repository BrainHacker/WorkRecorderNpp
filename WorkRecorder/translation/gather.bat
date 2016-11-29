@echo off

set name=WorkRecorder.dll

if exist %name% (
del %name%
)

if exist %name%.xxxx.po (
del %name%.xxxx.po
)

copy ..\Debug\%name% .\
exe2po.exe %name%

winmergeu %name%.xxxx.po English.po