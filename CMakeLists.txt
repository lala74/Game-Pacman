cmake_minimum_required(VERSION 3.5)

project(Pacman)

add_compile_options(${CMAKE_CXX_FLAGS} -Wall)

# Settings
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH
"/home/lala/Qt/5.12.5"
"/home/lala/Qt/5.12.5/gcc_64/lib/cmake"
CACHE FILEPATH "CMake PrefixPath")

# Constant name
set(BASE_TARGET main)

# Include dynamic libraries
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# Bring header file into project
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${Qt5Core_INCLUDES}
    ${Qt5Gui_INCLUDES}
    ${Qt5Widgets_INCLUDES}
)

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})

# Create base objects
set(BASE_OBJECTS jeu.cpp pacmanwindow.cpp)

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "-fPIC")

# Executable for server
add_executable(${BASE_TARGET} ${BASE_OBJECTS} main.cpp)

target_link_libraries(${BASE_TARGET} 
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

add_custom_target(run
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/${BASE_TARGET} .
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${BASE_TARGET}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR/build}
)