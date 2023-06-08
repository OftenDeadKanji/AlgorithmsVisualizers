cmake_minimum_required(VERSION 3.20)

project(PathFinding)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    "src/main.cpp"
    "src/application.cpp" 
    "src/application.hpp"
    
    "src/MVC/model.cpp" 
    "src/MVC/model.hpp" 

    "src/MVC/view.cpp"
    "src/MVC/view.hpp"

    "src/MVC/controller.cpp"
    "src/MVC/controller.hpp"

    "src/Utils/Timer/timer.cpp"
)

add_executable(PathFinding ${SOURCES})

set_target_properties(PathFinding PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_include_directories(PathFinding PRIVATE "dependencies/include/")

set(SFML_SUFFIX "")

#
# Compiler detection
#

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("MSVC Compiler")
    set(COMPILER_NAME "msvc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND WIN32)
    message("MINGW Compiler")
     set(COMPILER_NAME "mingw")
endif()

#
# Configuration detection
#

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug configuration detected")

    set(CONFIGURATION_NAME "Debug/")
    string(APPEND SFML_SUFFIX "-d")

    add_compile_definitions("_DEBUG")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release configuration detected")

    set(CONFIGURATION_NAME "RelWithDebInfo")

    add_compile_definitions("_RELEASE")
elseif(CMAKE_BUILD_TYPE STREQUAL "Dist")
    message("Dist configuration detected")

    set(CONFIGURATION_NAME "Release")

    add_compile_definitions("_DIST")
else()
    message(FATAL_ERROR "Unknown configuration detected")
endif()

add_compile_definitions("SFML_STATIC")

set(LIB_NAMES 
    "opengl32" "freetype" "winmm" "gdi32" "openal32" "flac" "vorbisenc" "vorbisfile" "vorbis" "ogg" "ws2_32" 
    "sfml-graphics-s${SFML_SUFFIX}" "sfml-window-s${SFML_SUFFIX}" "sfml-audio-s${SFML_SUFFIX}" "sfml-network-s${SFML_SUFFIX}" "sfml-main${SFML_SUFFIX}" "sfml-system-s${SFML_SUFFIX}"
)

set(LIBS)

foreach(LIB_NAME IN LISTS LIB_NAMES)
    message(${LIB_NAME})

    find_library(LIB_${LIB_NAME} NAMES ${LIB_NAME} PATHS "dependencies/lib/${COMPILER_NAME}/${CONFIGURATION_NAME}/" "dependencies/lib/${COMPILER_NAME}/General/")
    
    message(${LIB_${LIB_NAME}})
    
    list(APPEND LIBS ${LIB_${LIB_NAME}})
endforeach()

add_subdirectory("dependencies/src/ImGUI/")

target_link_libraries(PathFinding PUBLIC ImGui ${LIBS})
