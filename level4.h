#ifndef LEVEL4_H
#define LEVEL4_H

#include "computer.h"
#include <vector>
#include <tuple>

class Level4 : public Computer {
public:
    Level4(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;

private:
    std::vector<std::tuple<int, int, int, int>> getAllPossibleMoves(Board* board, int color);
    int evaluateMove(Board* board, int fromRow, int fromCol, int toRow, int toCol);
    int getPieceValue(Piece* piece);
};

#endif // LEVEL4_H
