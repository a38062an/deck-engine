#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "model/Game.hpp"
#include <string>
#include <vector>

// Bridge between Game logic and UI
// Exposes game state without cout side effects
class GameController
{
public:
    GameController();

    // Game actions
    void makeGuess(bool guessHigher);
    void resetGame();

    // State queries
    std::string getCurrentCardString() const;
    std::string getNextCardString() const;
    int getPlayerScore(int playerIndex) const;
    int getActivePlayerIndex() const;
    bool wasLastGuessCorrect() const;
    int getLastPointsAwarded() const;

    // Get last turn info (for UI feedback)
    const std::string &getLastTurnMessage() const;
    void clearLastTurnMessage();

private:
    Game game_;
    std::string lastTurnMessage_;

    // Helper to format joker messages without cout
    std::string formatJokerMessage(const Card &joker) const;
};

#endif
