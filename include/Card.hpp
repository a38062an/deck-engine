#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <cstdint>

enum class Suit : uint8_t
{
    Clover,  // C (Alphabetical 1st)
    Diamond, // D (Alphabetical 2nd)
    Heart,   // H (Alphabetical 3rd)
    Spade    // S (Alphabetical 4th)
};

enum class Value : uint8_t
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
    // Order matters here: Value is compared before Suit
    Value value_;
    Suit suit_;

    std::string toString() const;

    bool operator<(const Card &other) const
    {
        if (value_ != other.value_)
            return value_ < other.value_;
        return suit_ < other.suit_;
    }

    bool operator>(const Card &other) const { return other < *this; }
    bool operator<=(const Card &other) const { return !(other < *this); }
    bool operator>=(const Card &other) const { return !(*this < other); }
    bool operator==(const Card &other) const { return !(*this < other) && !(other < *this); }
};

#endif