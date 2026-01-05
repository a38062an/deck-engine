cmake_minimum_required(VERSION 3.10)
project(DeckEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(deck_engine
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Game.cpp
)

target_include_directories(deck_engine PRIVATE include)