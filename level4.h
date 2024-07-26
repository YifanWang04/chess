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
    int minimax(Board* board, int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluateBoard(Board* board);
    std::vector<std::tuple<int, int, int, int>> getAllPossibleMoves(Board* board, int color);
};

#endif // LEVEL4_H
