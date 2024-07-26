#ifndef LEVEL4_H
#define LEVEL4_H

#include "computer.h"
#include <vector>
#include <tuple>
#include <deque>

class Level4 : public Computer {
public:
    Level4(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;

private:
    bool isSafeAfterMove(Board* board, int fromRow, int fromCol, int toRow, int toCol);
    std::vector<std::tuple<int, int, int, int>> getAllPossibleMoves(Board* board, int color);
    int evaluateMove(Board* board, int fromRow, int fromCol, int toRow, int toCol);
    int getPieceValue(Piece* piece);
    bool isRepeatedCheck(int fromRow, int fromCol, int toRow, int toCol);

    std::deque<std::tuple<int, int, int, int>> recentChecks; // To track recent check moves
    static const int maxRecentChecks = 10; // Maximum number of recent check moves to track
};

#endif // LEVEL4_H
