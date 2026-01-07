#include "../../include/controller/GameController.hpp"
#include <sstream>

GameController::GameController() : game_()
{
    lastTurnMessage_ = "";
}

void GameController::makeGuess(bool guessHigher)
{
    // Clear previous message
    lastTurnMessage_.clear();

    // Play turn (this modifies game state)
    game_.playTurn(guessHigher);

    // For GUI, we don't use cout in Game.cpp
    // Instead, we'd need to refactor Game to return turn results
    // For now, basic feedback
    lastTurnMessage_ = "Turn played. Current card: " + getCurrentCardString();
}

void GameController::resetGame()
{
    game_ = Game(); // Create new game
    lastTurnMessage_ = "Game reset!";
}

std::string GameController::getCurrentCardString() const
{
    return game_.getCurrentCard().toString();
}

std::string GameController::getNextCardString() const
{
    return game_.getNextCard().toString();
}

int GameController::getPlayerScore(int playerIndex) const
{
    return game_.getScore(playerIndex);
}

int GameController::getActivePlayerIndex() const
{
    return game_.getActivePlayerIndex();
}

bool GameController::wasLastGuessCorrect() const
{
    return game_.wasLastGuessCorrect();
}

int GameController::getLastPointsAwarded() const
{
    return game_.getLastPointsAwarded();
}

const std::string &GameController::getLastTurnMessage() const
{
    return lastTurnMessage_;
}

void GameController::clearLastTurnMessage()
{
    lastTurnMessage_.clear();
}
