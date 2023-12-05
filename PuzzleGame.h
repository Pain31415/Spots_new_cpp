#ifndef PUZZLE_GAME_H
#define PUZZLE_GAME_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>
#include <fstream>
#include <string>

class PuzzleGame {
private:
    enum BoardMode {
        THREE_BY_THREE = 3,
        FOUR_BY_FOUR = 4
    };
    BoardMode boardMode;
private:
    std::vector<std::vector<int>> board;
    int emptyRow, emptyCol;
    
    std::string recordFileName;
    void printMenu() const;

public:
    PuzzleGame();
    void printAsciiCell(int value) const;
    void printAsciiBoard() const;
    void initializeBoard();
    void shuffleBoard();
    void printBoard();
    bool move(int direction);
    bool moveNumber(int number, int direction);
    bool isSolved() const;
    void saveScore(int moves) const;
    void displayScores() const;
    void startGame();
    void endGame();
    void setBoardMode(BoardMode mode);
    BoardMode getBoardMode() const;
    void setPlayerMode(bool playerMode);
    void endGame() const;
    void printColoredBoard(int selectedRow, int selectedCol, int newCol);

    bool isAdjacentToEmpty(int number, int emptyRow, int emptyCol) const;

    int movesCount;

    void setRecordFileName(const std::string& filename);
    void saveRecord();
    void loadRecord();

    void performPlayerMove();
    void performComputerMove();
    void performMove();
    void performMoveLoop();
    bool isComputerPlayer() const;
    bool isGameOver() const;
    void printRecord() const;
    
    void printWinningMessage() const;
};

#endif // PUZZLE_GAME_H