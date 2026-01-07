#include "../../include/model/Deck.hpp"
#include <algorithm>
#include <random>

Deck::Deck()
{
    initialiseDeck();
}

void Deck::shuffleDeck(std::mt19937 &randomiser)
{
    std::shuffle(deck_.begin(), deck_.end(), randomiser);
}

void Deck::initialiseDeck()
{
    int cursor{0};

    for (int suit{0}; suit < 4; suit++)
    {
        for (int value{static_cast<int>(Value::Two)}; value <= static_cast<int>(Value::Ace); value++)
        {
            deck_[cursor++] = Card{
                static_cast<Value>(value),
                static_cast<Suit>(suit)};
        }

        // Add Joker for every suit (different joker suits have different abilities)
        deck_[cursor++] = Card{
            Value::Joker,
            static_cast<Suit>(suit)};
    }
}

std::optional<Card> Deck::drawCard()
{
    if (topCardIndex_ >= 56)
    {
        return std::nullopt;
    }

    return deck_[topCardIndex_++];
}

void Deck::resetDeck()
{
    topCardIndex_ = 0;
}
