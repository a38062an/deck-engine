#include "../include/Card.hpp"

std::string Card::toString() const
{
    if (value_ == Value::Joker)
    {
        return "Joker";
    }

    std::string valueStr;
    switch (value_)
    {
    case Value::Ace:
        valueStr = "Ace";
        break;
    case Value::King:
        valueStr = "King";
        break;
    case Value::Queen:
        valueStr = "Queen";
        break;
    case Value::Jack:
        valueStr = "Jack";
        break;
    default:
        valueStr = std::to_string(static_cast<int>(value_));
        break;
    }

    std::string suitStr;
    switch (suit_)
    {
    case Suit::Heart:
        suitStr = "Hearts";
        break;
    case Suit::Spade:
        suitStr = "Spades";
        break;
    case Suit::Diamond:
        suitStr = "Diamonds";
        break;
    case Suit::Clover:
        suitStr = "Clovers";
        break;
    default:
        suitStr = "Unknown";
        break;
    }

    return valueStr + " of " + suitStr;
}
