# Deck Engine - Higher or Lower Card Game

A Higher or Lower card game with both CLI and GUI interfaces. Includes joker mechanics with unique effects, two-player mode, and Qt-based graphical interface.

## Features

- Standard 52-card deck plus 4 jokers with unique effects
- Shuffling mechanism using std::random_device
- Higher/Lower game rules with card comparison
- CLI and GUI interfaces
- Two-player mode
- Visual player turn indicator
- In-game instructions dialog

## Screenshots

### GUI Version

<img src="screenshots/gui-gameplay.png" alt="GUI Gameplay" width="600">

### CLI Version

<img src="screenshots/cli-gameplay.png" alt="CLI Gameplay" width="600">

## Quick Start

```bash
# Build
./build.sh

# Run GUI
./build/deck_engine_gui

# Run CLI
./build/deck_engine_cli
```

### Manual Build

```bash
mkdir build && cd build
cmake ..
make
```

## Project Structure

```
deck-engine/
├── include/
│   ├── model/              # Business logic
│   │   ├── Card.hpp
│   │   ├── Deck.hpp
│   │   └── Game.hpp
│   ├── controller/         # Application coordination
│   │   └── GameController.hpp
│   └── view/              # User interface
│       └── MainWindow.hpp
├── src/
│   ├── model/             # Game logic implementation
│   ├── controller/        # Controller implementation
│   ├── view/             # UI implementation
│   ├── main.cpp          # CLI entry point
│   └── main_gui.cpp      # GUI entry point
├── CMakeLists.txt
├── build.sh
├── README.md             # This file
├── STRUCTURE.md          # Detailed structure documentation
└── DESIGN_DECISIONS.md   # Architecture rationale
```

## Architecture Overview

### Design Decisions

**Separation of Concerns**
The codebase is structured into three layers:

1. **Core Logic** (Game, Deck, Card)
   - Pure C++, no dependencies
   - Contains all game rules and state management
   - Testable independently of UI

The codebase uses MVC architecture with three layers:

**Model** (Game, Deck, Card)

- Pure C++ with no UI dependencies
- Game rules and state management
- Testable independently

**Controller** (GameController)

- Bridges game logic and UI
- Exposes game state through clean API
- Framework-agnostic

**View** (MainWindow, CLI)

- User interaction handling
- Visual rendering
- No business logic

### Key Classes

**Card** - Represents a single card with Value and Suit enums. Implements comparison operators.

**Deck** - Manages 56-card deck (52 standard + 4 jokers). Handles shuffling and drawing.

**Game** - Core game state and Higher/Lower rules. Implements 4 joker effects:

- Clover: Auto-win
- Diamond: Reverse comparison
- Heart: Double points
- Spade: Swaps player scores

**GameController** - Wraps Game class for UI consumption. Query methods for rendering.

**MainWindow** - Qt Widgets interface with buttons, score display, and color coding

### GUI Version (requires Qt)

```bash
# Install Qt first:
# macOS: brew install qt
# Ubuntu: apt install qtbase5-dev
# Windows: Download from qt.io

mkdir build && cd build
cmake ..
cmake --build .
./deck_engine_gui
```

## Game Rules

1. Players alternate guessing if next card is higher or lower
2. Correct guess = 1 point
3. Joker modifies rules for that turn based on suit
4. Cards ranked: 2 (lowest) to Ace (highest)
5. Suit tiebreaker: Clubs < Diamonds < Hearts < Spades

## Design Decisions

**MVC Architecture**: Separates game logic from UI, enabling independent testing and framework flexibility.

**Qt for GUI**: Cross-platform framework with professional appearance and built-in memory management.

**Four Joker Abilities**: Adds strategic depth. Each suit provides different gameplay modification.

**Two-Player Mode**: Turn-based competitive play with state management for two players.

**C++20**: Modern standard with enum classes, const correctness, and RAII principles.wnership

### Memory Management

- All Qt widgets have parents (automatic cleanup)
- No memory leaks (verified with usage patterns)
- RAII for resource management
