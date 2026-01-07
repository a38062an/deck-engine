#ifndef GAME_HPP
#define GAME_HPP

#include "model/Deck.hpp"
#include <random>

class Game
{
public:
    Game();
    void playTurn(bool guessHigher);

    // Getters for UI/controller access
    const Card &getCurrentCard() const
    {
        return currentCard_;
    }

    const Card &getNextCard() const
    {
        return nextCard_;
    }

    int getScore(int playerIndex) const
    {
        return scores_[playerIndex];
    }

    int getActivePlayerIndex() const
    {
        return activePlayerIndex_;
    }

    bool wasLastGuessCorrect() const
    {
        return lastGuessCorrect_;
    }

    int getLastPointsAwarded() const
    {
        return lastPointsAwarded_;
    }

private:
    // Game resources
    Deck deck_;
    std::mt19937 randomiser;

    // Game State
    Card currentCard_;
    Card nextCard_;
    int scores_[2]{0, 0};
    int activePlayerIndex_{0};
    bool lastGuessCorrect_{false};
    int lastPointsAwarded_{0};

    // Helpers
    void swapTurn();
    bool nextCardIsHigher();
    Card drawNextCard();
    int applyJokerEffect(const Card &joker, bool guessHigher, bool actualHigher);
    bool isJoker(const Card &card) const;
};

#endif