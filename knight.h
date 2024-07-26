#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    Knight(int row, int col, char symbol, int color);
    ~Knight();
    Piece* clone() const;
    bool canMove(int newRow, int newCol, Board& board) override;
};

#endif
