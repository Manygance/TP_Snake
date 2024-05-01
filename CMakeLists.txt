cmake_minimum_required(VERSION 3.22)
project(Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


add_executable(Snake ${RESOURCE_ADDED}
        main.cpp
        jeu.cpp
        snakewindow.cpp
        mainmenu.hpp gamewindow.hpp gamewindow.cpp global_settings.hpp)

target_link_libraries(Snake
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

add_custom_command(
        TARGET Snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:Snake>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:Snake>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:Snake>
)