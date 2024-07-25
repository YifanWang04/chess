#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(int row, int col, char symbol, int color);
    ~Queen();
    bool canMove(int newRow, int newCol, Board& board);
    Piece* clone() const;
};

#endif
