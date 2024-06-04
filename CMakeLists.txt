cmake_minimum_required(VERSION 3.22)
project(Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(fmod SHARED IMPORTED GLOBAL)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(FMOD MODULE REQUIRED)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(${FMOD_INCLUDE_DIR})
link_libraries(${FMOD_LIBRARY_LIB})

add_executable(Snake ${RESOURCE_ADDED}
        main.cpp
        jeu.cpp
        snakewindow.cpp
        mainmenu.hpp
        gamewindow.hpp
        gamewindow.cpp
        global_settings.hpp
        sound.cpp sound.hpp)

target_link_libraries(Snake
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${FMOD_LIBRARY_LIB}
        )


add_custom_command(
        TARGET Snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:Snake>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:Snake>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:Snake>
)
