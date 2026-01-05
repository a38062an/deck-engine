#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum Suit
{
    Heart,
    Diamond,
    Spade,
    Clover,
};

enum Value
{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    Joker

};

struct Card
{
    Suit suit_;
    Value value_;

    std::string toString() const;

    // Overload comparison operator
    bool operator>(const Card &other) const
    {
        return static_cast<int>(value_) > static_cast<int>(other.value_);
    }
};

#endif