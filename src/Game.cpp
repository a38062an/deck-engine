#include "../include/Game.hpp"

Game::Game() : randomiser(std::random_device{}())
{
    deck_.shuffleDeck(randomiser);

    auto card = deck_.drawCard();

    if (card != std::nullopt)
    {
        currentCard_ = card.value();
    }
}

bool Game::nextCardIsHigher()
{
    return nextCard_ > currentCard_;
}

void Game::swapTurn()
{
    activePlayerIndex_ = 1 - activePlayerIndex_;
}

void Game::playTurn(bool guessHigher)
{
    auto drawnCard = deck_.drawCard();

    bool drawn = false;
    while (!drawn)
    {
        if (drawnCard != std::nullopt)
        {
            nextCard_ = drawnCard.value();
            drawn = true;
        }
        else
        {
            deck_.resetDeck();
            drawnCard = deck_.drawCard(); // Try gain
        }
    }
    if ((guessHigher && nextCardIsHigher()) || (!guessHigher && !nextCardIsHigher()))
    {
        scores_[activePlayerIndex_] += 1;
    }

    currentCard_ = nextCard_;

    // Flip player index
    swapTurn();
}