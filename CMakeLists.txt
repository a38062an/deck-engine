cmake_minimum_required(VERSION 3.10)
project(DeckEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wc++20-compat)

# Shared game logic library (Model layer)
add_library(game_logic STATIC
    src/model/Card.cpp
    src/model/Deck.cpp
    src/model/Game.cpp
)
target_include_directories(game_logic PUBLIC include)

# CLI executable (original version)
add_executable(deck_engine_cli
    src/main.cpp
)
target_link_libraries(deck_engine_cli PRIVATE game_logic)

# GUI executable (Qt version)
# Find Qt6 or Qt5
find_package(Qt6 COMPONENTS Core Gui Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
endif()

# Enable Qt features BEFORE defining target
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(deck_engine_gui
    src/main_gui.cpp
    src/view/MainWindow.cpp
    src/controller/GameController.cpp
    include/view/MainWindow.hpp
)

target_link_libraries(deck_engine_gui PRIVATE 
    game_logic
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

target_include_directories(deck_engine_gui PRIVATE include)
