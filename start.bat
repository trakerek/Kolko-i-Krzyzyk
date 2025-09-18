@echo off
cd /d "%~dp0\bin"
set PATH=%CD%\..\libs;%PATH%
set bin=main.exe

if exist %bin% (
    "%bin%"
) else (
    cd ..
    call make
    cd bin
    if exist %bin% (
        "%bin%"
    ) else (
        echo ERROR: Kompilacja nie stworzyla %bin%
        pause
    )
)
