cmake_minimum_required(VERSION 3.10)
project(VampireSurvivors)

set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Find the SFML library
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

# Collect all .cpp files in the src/ directory and subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable with all source files
add_executable(VampireSurvivors ${SOURCES})

# Link SFML to your project
target_link_libraries(VampireSurvivors sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# For Windows: Include the SFML DLLs in the output folder automatically
if (WIN32)
    set(SFML_DLLS 
        "${CMAKE_SOURCE_DIR}/SFML/bin/sfml-system-d-2.dll"
        "${CMAKE_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll"
        "${CMAKE_SOURCE_DIR}/SFML/bin/sfml-graphics-d-2.dll"
        "${CMAKE_SOURCE_DIR}/SFML/bin/sfml-audio-d-2.dll"
        "${CMAKE_SOURCE_DIR}/SFML/bin/sfml-network-d-2.dll"
    )

    foreach(dll ${SFML_DLLS})
        add_custom_command(TARGET VampireSurvivors POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll}" $<TARGET_FILE_DIR:VampireSurvivors>)
    endforeach()
endif()
