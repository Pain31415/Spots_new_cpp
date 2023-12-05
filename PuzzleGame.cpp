#include "PuzzleGame.h"
#include "PuzzleFunctions.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <string>


void printHorizontalLine(int size) {
    std::cout << "+";
    for (int i = 0; i < size * 4; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;
}

void PuzzleGame::printMenu() const
{
}

PuzzleGame::PuzzleGame()
{

}

void PuzzleGame::printAsciiCell(int value) const {
    if (value == 0) {
        std::cout << "|    ";
    }
    else {
        if (value < 10) {
            std::cout << "| " << value << "  ";
        }
        else {
            std::cout << "|" << value << "  ";
        }
    }
}

void PuzzleGame::printAsciiBoard() const {
    int size = (PuzzleGame::boardMode == BoardMode::THREE_BY_THREE) ? 3 : 4;

    printHorizontalLine(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            PuzzleGame::printAsciiCell(PuzzleGame::board[i][j]);
        }
        std::cout << "|" << std::endl;
        printHorizontalLine(size);
    }
}

void PuzzleGame::initializeBoard() {
    int size = (boardMode == THREE_BY_THREE) ? 3 : 4;
    board.resize(size, std::vector<int>(size, 0));

    int number = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = number++;
        }
    }

    emptyRow = size - 1;
    emptyCol = size - 1;
    board[emptyRow][emptyCol] = 0;
}

void PuzzleGame::setBoardMode(BoardMode mode) {
    boardMode = mode;
}

PuzzleGame::BoardMode PuzzleGame::getBoardMode() const {
    return boardMode;
}

void PuzzleGame::setPlayerMode(bool playerMode) {
    // true - гравець, false - комп'ютер
    // Зараз ця інформація не використовується, вам можливо знадобиться змінити логіку гри
}

void PuzzleGame::endGame() const {
    std::cout << "Game over. Exiting..." << std::endl;
    exit(0);
}

void PuzzleGame::startGame() {
    std::cout << "Choose board mode (3 for 3x3, 4 for 4x4): ";
    int mode;
    std::cin >> mode;

    if (mode == 3) {
        setBoardMode(THREE_BY_THREE);
    }
    else if (mode == 4) {
        setBoardMode(FOUR_BY_FOUR);
    }
    else {
        std::cout << "Invalid mode. Defaulting to 3x3." << std::endl;
        setBoardMode(THREE_BY_THREE);
    }

    std::cout << "Choose player mode (0 for computer, 1 for human): ";
    int playerMode;
    std::cin >> playerMode;

    if (playerMode == 0) {
        setPlayerMode(false);
    }
    else if (playerMode == 1) {
        setPlayerMode(true);
    }
    else {
        std::cout << "Invalid player mode. Defaulting to human player." << std::endl;
        setPlayerMode(true);
    }

    initializeBoard();
    shuffleBoard();
}

void PuzzleGame::endGame()
{
	std::cout << "Game over. Exiting..." << std::endl;
	exit(0);
}

bool PuzzleGame::isComputerPlayer() const {
    return false;
}

bool PuzzleGame::isGameOver() const
{
    return false;
}

void PuzzleGame::printRecord() const
{

}

void PuzzleGame::printWinningMessage() const
{

}

void PuzzleGame::performComputerMove() {
    // Реалізуйте хід комп'ютера тут, якщо потрібно
    // Використовуйте isComputerPlayer() для перевірки режиму гравця
}

void PuzzleGame::performPlayerMove() {
    int number, direction;
    bool successfulMove = false;  // Флаг для визначення успішності ходу
    int selectedCol = -1;

    do {
        std::cout << "Enter the number you want to move (1-"
            << (boardMode == THREE_BY_THREE ? "8" : "15") << ") or 0 to exit: ";
        std::cin >> number;

        if (number == 0) {
            endGame();
        }

        std::cout << "Choose direction (0-Left, 1-Right, 2-Up, 3-Down): ";
        std::cin >> direction;

        successfulMove = moveNumber(number, direction);

        if (!successfulMove) {
            std::cout << "Invalid move. Try again.\n";

            // Визначити, яку колонку слід виділити при невдалому ході
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] == number) {
                        selectedCol = j;
                        break;
                    }
                }
                if (selectedCol != -1) {
                    break;
                }
            }

            // Друкуємо дошку з виділеним вибраним числом
            printColoredBoard(-1, -1, selectedCol);
        }

    } while (!successfulMove);
}

void PuzzleGame::performMove() {
    if (isComputerPlayer()) {
        performComputerMove();
    }
    else {
        performPlayerMove();
    }
}

void PuzzleGame::performMoveLoop() {
    do {
        printAsciiBoard();
        performMove();

        if (isSolved()) {
            std::cout << "Congratulations! You solved the puzzle.\n";
            endGame();
        }

    } while (true);
}

void PuzzleGame::shuffleBoard() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 1000; ++i) {
        int direction = rand() % 4;
        move(direction);
    }
}

void PuzzleGame::printBoard()
{

}

bool PuzzleGame::move(int direction) {
    // Ваша реалізація руху тут
    int newRow = emptyRow;
    int newCol = emptyCol;

    switch (direction) {
    case 0: // Вліво
        newCol = emptyCol - 1;
        break;
    case 1: // Вправо
        newCol = emptyCol + 1;
        break;
    case 2: // Вгору
        newRow = emptyRow - 1;
        break;
    case 3: // Вниз
        newRow = emptyRow + 1;
        break;
    }

    if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board.size()) {
        std::swap(board[emptyRow][emptyCol], board[newRow][newCol]);
        emptyRow = newRow;
        emptyCol = newCol;
        return true;
    }
    else {
        return false;
    }
}

bool PuzzleGame::moveNumber(int number, int direction) {
    // Ваша реалізація руху числа тут

    const int minNumber = 1;
    const int maxNumber = (boardMode == THREE_BY_THREE) ? 8 : 15;

    // Перевірка діапазону чисел
    if (number < minNumber || number > maxNumber) {
        std::cout << "Invalid number. Please choose a number between "
            << minNumber << " and " << maxNumber << ".\n";
        return false;
    }

    int row = -1, col = -1;

    // Знаходження позиції числа на дошці
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == number) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) {
            break;
        }
    }

    // Перевірка, чи число знайдено
    if (row == -1 || col == -1) {
        std::cout << "Number not found on the board.\n";
        return false;
    }

    int newRow = row, newCol = col;

    // Визначення нової позиції в залежності від напрямку
    switch (direction) {
    case 0: // Вліво
        newCol = col - 1;
        break;
    case 1: // Вправо
        newCol = col + 1;
        break;
    case 2: // Вгору
        newRow = row - 1;
        break;
    case 3: // Вниз
        newRow = row + 1;
        break;
    }

    // Перевірка коректності нової позиції
    if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board.size() && board[newRow][newCol] == 0) {
        // Обмін значеннями між старою і новою позиціями
        std::swap(board[row][col], board[newRow][newCol]);

        // Перевірка, чи гра вирішена
        if (isSolved()) {
            std::cout << "Congratulations! You solved the puzzle.\n";
            endGame();
        }

        return true;
    }
    else {
        std::cout << "Invalid move. The number cannot be moved in the chosen direction.\n";
        return false;
    }
}

void PuzzleGame::printColoredBoard(int selectedRow, int selectedCol, int newCol) {
    size_t size = board.size();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << "+----";
        }

        std::cout << "+" << std::endl;

        for (size_t j = 0; j < size; ++j) {
            std::cout << "|";

            // Змініть кольори для всіх чисел
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);

            std::cout << " ";

            if (board[i][j] == 0) {
                std::cout << "   ";
            }
            else {
                if (board[i][j] < 10) {
                    std::cout << " ";
                }
                std::cout << board[i][j] << " ";
            }
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "|" << std::endl;
    }

    for (size_t i = 0; i < size; ++i) {
        std::cout << "+----";
    }

    std::cout << "+" << std::endl;
}

bool PuzzleGame::isAdjacentToEmpty(int number, int emptyRow, int emptyCol) const {
    // Перевіряємо, чи число знаходиться в сусідстві з порожньою клітинкою
    int row = -1, col = -1;

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == number) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) {
            break;
        }
    }

    // Перевірка, чи число знаходиться в сусідстві з порожньою клітинкою
    return ((row == emptyRow && std::abs(col - emptyCol) == 1) ||
        (col == emptyCol && std::abs(row - emptyRow) == 1));
}

void PuzzleGame::setRecordFileName(const std::string& filename)
{
    
}

void PuzzleGame::saveRecord()
{
}

void PuzzleGame::loadRecord()
{
}

bool PuzzleGame::isSolved() const {
    size_t size = board.size();
    int number = 1;

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (board[i][j] != number % (size * size)) {
                return false;
            }
            ++number;
        }
    }

    return true;
}

void PuzzleGame::saveScore(int moves) const {
    std::ofstream file("scores.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }

    PuzzleGame::BoardMode mode = PuzzleGame::getBoardMode();
    file << "Mode: " << (mode == PuzzleGame::THREE_BY_THREE ? "3x3" : "4x4") << ", Moves: " << moves << "\n";
    file.close();
}

void PuzzleGame::displayScores() const {
    std::ifstream file("scores.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file for reading.\n";
        return;
    }

    std::cout << "High Scores:\n";
    std::cout << "----------------\n";

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }

    file.close();
}