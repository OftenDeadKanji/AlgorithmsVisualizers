cmake_minimum_required(VERSION 3.20)

project(AlgorithmVisualizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    "src/main.cpp"

    "src/Application/application.cpp" 
    "src/Application/application.hpp"
     
    "src/MVC/Base/Model/model.hpp" 
    "src/MVC/Base/View/view.cpp"
    "src/MVC/Base/View/view.hpp"
    "src/MVC/Base/Controller/controller.cpp"
    "src/MVC/Base/Controller/controller.hpp"

    "src/MVC/Menu/Model/menuModel.hpp" 
    "src/MVC/Menu/View/menuView.cpp" 
    "src/MVC/Menu/View/menuView.hpp" 
    "src/MVC/Menu/Controller/menuController.cpp"
    "src/MVC/Menu/Controller/menuController.hpp"

    "src/MVC/Sorting/Model/sortingModel.cpp" 
    "src/MVC/Sorting/Model/sortingModel.hpp" 
    "src/MVC/Sorting/View/sortingView.cpp" 
    "src/MVC/Sorting/View/sortingView.hpp" 
    "src/MVC/Sorting/View/algorithmSelector.cpp"
    "src/MVC/Sorting/View/algorithmSelector.hpp"
    "src/MVC/Sorting/View/arraySizeSelector.cpp"
    "src/MVC/Sorting/View/arraySizeSelector.hpp"
    "src/MVC/Sorting/View/delaySelector.cpp"
    "src/MVC/Sorting/View/delaySelector.hpp"
    "src/MVC/Sorting/Controller/sortingController.cpp"
    "src/MVC/Sorting/Controller/sortingController.hpp"

    "src/Sorting/Sorters/sorter.hpp"
    "src/Sorting/Sorters/sorter.cpp"
    "src/Sorting/Sorters/bubbleSorter.cpp"
    "src/Sorting/Sorters/bubbleSorter.hpp"
    "src/Sorting/Sorters/insertionSorter.cpp"
    "src/Sorting/Sorters/insertionSorter.hpp"
    "src/Sorting/Sorters/quickSorter.cpp"
    "src/Sorting/Sorters/quickSorter.hpp"

    "src/MVC/PathFinding/Model/pathFindingModel.hpp" 
    "src/MVC/PathFinding/View/pathFindingView.cpp" 
    "src/MVC/PathFinding/View/pathFindingView.hpp" 
    "src/MVC/PathFinding/Controller/pathFindingController.cpp"
    "src/MVC/PathFinding/Controller/pathFindingController.hpp"

    "src/Utils/Timer/timer.cpp"
    "src/Utils/Random/random.cpp"
    "src/Utils/Random/random.hpp"
    
 "src/Sorting/Sorters/heapSorter.cpp")

add_executable(AlgorithmVisualizer ${SOURCES})

set_target_properties(AlgorithmVisualizer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_include_directories(AlgorithmVisualizer PRIVATE "dependencies/include/")

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
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message("Release configuration detected")

    set(CONFIGURATION_NAME "RelWithDebInfo")

    add_compile_definitions("_RELEASE")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
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

target_link_libraries(AlgorithmVisualizer PUBLIC ImGui ${LIBS})
