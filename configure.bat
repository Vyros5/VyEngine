@echo off

set CMAKE_CMD=cmake -S . -B out/build

echo %CMAKE_CMD%
%CMAKE_CMD%

pause