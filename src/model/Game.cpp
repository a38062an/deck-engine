#include "../../include/model/Game.hpp"
#include <iostream>

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

bool Game::isJoker(const Card &card) const
{
    return card.value_ == Value::Joker;
}

Card Game::drawNextCard()
{
    auto drawnCard = deck_.drawCard();

    while (true)
    {
        if (drawnCard != std::nullopt)
        {
            return drawnCard.value();
        }
        else
        {
            deck_.resetDeck();
            drawnCard = deck_.drawCard();
        }
    }
}

int Game::applyJokerEffect(const Card &joker, bool guessHigher, bool actualHigher)
{
    // Calculate standard correct guess
    bool standardCorrect = (guessHigher && actualHigher) || (!guessHigher && !actualHigher);

    switch (joker.suit_)
    {
    case Suit::Clover:
        std::cout << "[C] Clover Joker! Wild Card - You automatically win!\n";
        return 1;

    case Suit::Diamond:
        std::cout << "<D> Diamond Joker! Reverse effect - Comparison is inverted!\n";
        return standardCorrect ? 0 : 1;

    case Suit::Heart:
        std::cout << "[H] Heart Joker! Double points.";
        if (standardCorrect)
        {
            std::cout << "Bonus! You earn 2 points instead of 1!\n";
            return 2;
        }
        else
        {
            std::cout << "But you guessed wrong, no points.\n";
            return 0;
        }

    case Suit::Spade:
        std::cout << "[S] Spade Joker! Scores swapped!\n";
        // Swap the scores
        std::swap(scores_[0], scores_[1]);
        return standardCorrect ? 1 : 0;
    default:
        return standardCorrect ? 1 : 0;
    }
}

void Game::playTurn(bool guessHigher)
{
    // Draw the next card
    Card drawnCard = drawNextCard();

        Card jokerCard;
        bool hasJoker = false;

        while (isJoker(drawnCard))
        {
            if (!hasJoker)
            {
                // First joker - save it for effects
                hasJoker = true;
                jokerCard = drawnCard;
                std::cout << "Drew a " << drawnCard.toString() << "!\n";
            }
            else
            {
                // Multiple jokers; Only first one counts, but announce it
                std::cout << "Drew ANOTHER " << drawnCard.toString() << "! Effects don't stack.\n";
            }

            // Draw next card (might be another joker or actual card)
            drawnCard = drawNextCard();
            std::cout << "Drawing next card for comparison...\n";
        }

        nextCard_ = drawnCard;

        bool actualHigher = nextCardIsHigher();

        int pointsToAdd;
        if (hasJoker)
        {
            pointsToAdd = applyJokerEffect(jokerCard, guessHigher, actualHigher);
        }
        else
        {
            // Standard comparison
            bool correctGuess = (guessHigher && actualHigher) || (!guessHigher && !actualHigher);
            pointsToAdd = correctGuess ? 1 : 0;
        }

        // Award points
        scores_[activePlayerIndex_] += pointsToAdd;

        // Track result
        lastGuessCorrect_ = (pointsToAdd > 0);
        lastPointsAwarded_ = pointsToAdd;

    currentCard_ = nextCard_;

    // Flip player index
    swapTurn();
}