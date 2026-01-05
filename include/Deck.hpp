#ifndef DECK_HPP
#define DECK_HPP

#include <array>
#include "Card.hpp"
#include <optional>

class Deck
{
public:
    Deck();
    void shuffleDeck();
    std::optional<Card> drawCard();
    void resetDeck();

private:
    std::array<Card, 56> deck_;
    int topCardIndex_{0}; // To track what next card to draw
    void initialiseDeck();
};

#endif