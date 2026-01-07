#include "../include/model/Game.hpp"
#include <iostream>

int main()
{
    Game game;

    std::cout << "=== Higher or Lower ===\n";
    std::cout << "Current card: " << game.getCurrentCard().toString() << "\n\n";

    bool playing = true;
    while (playing)
    {
        std::cout << "Player " << (game.getActivePlayerIndex() + 1) << "'s turn\n";
        std::cout << "Score - P1: " << game.getScore(0) << " | P2: " << game.getScore(1) << "\n";

        std::cout << "\nWill next card be (h)igher or (l)ower? (q to quit): ";

        char choice;
        std::cin >> choice;

        if (choice == 'q' || choice == 'Q')
        {
            playing = false;
            continue;
        }

        bool guessHigher = (choice == 'h' || choice == 'H');
        game.playTurn(guessHigher);

        std::cout << "\nRevealed: " << game.getCurrentCard().toString() << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    std::cout << "\nFinal Scores:\n";
    std::cout << "Player 1: " << game.getScore(0) << "\n";
    std::cout << "Player 2: " << game.getScore(1) << "\n";

    return 0;
}
