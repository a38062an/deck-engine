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
    std::mt19937 rng_;

    // Game State
    Card currentCard_;
    Card nextCard_;
    int scores_[2];
    int activePlayerIndex_;

    // Internal logic
    void swapTurn();
    bool compareCards(bool guessHigher);
};

#endif