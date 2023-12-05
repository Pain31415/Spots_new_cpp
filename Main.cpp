#include "PuzzleGame.h"
#include "PuzzleFunctions.h"

void printMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Perform move\n";
    std::cout << "2. Exit\n";
}

void performMove(PuzzleGame& game) {
    game.performMove();
    ++game.movesCount;
}

int main() {
    PuzzleGame puzzle;
    puzzle.startGame();

    while (!puzzle.isGameOver()) {
        puzzle.printBoard();
        puzzle.printRecord();
        puzzle.printColoredBoard(1, 1, 1);

        printMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            puzzle.performMove();
            break;
        case 2:
            puzzle.endGame();
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }

        if (puzzle.isSolved()) {
            std::cout << "Congratulations! You solved the puzzle.\n";
            puzzle.endGame();
        }
    }

    return 0;
}