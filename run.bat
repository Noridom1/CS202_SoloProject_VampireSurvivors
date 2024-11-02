@echo off
:: Create build directory if it doesn't exist
if not exist "build" (
    mkdir build
)
cd build

:: Run CMake
cmake ..

:: Build the project
cmake --build . --config Debug

:: Run the executable
start ./Debug/VampireSurvivors.exe
exit
