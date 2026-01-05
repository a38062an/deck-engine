#ifndef GAME_HPP
#define GAME_HPP

#include "Deck.hpp"
#include <random>

class Game
{
public:
    Game();
    void playTurn(bool guessHigher);

private:
    // Game resources
    Deck deck_;
    std::mt19937 randomiser;

    // Game State
    Card currentCard_;
    Card nextCard_;
    int scores_[2]{0, 0};
    int activePlayerIndex_{0};

    // Helpers
    void swapTurn();
    bool nextCardIsHigher();
};

#endif