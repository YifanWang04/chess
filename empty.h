#ifndef EMPTY_H
#define EMPTY_H


#include "piece.h"

class Empty: public Piece {
public:
    Empty(int row, int col, char symbol, int color);
    bool canMove(int newRow, int newCol, Board& board) override;
    Piece* clone() const;
};

#endif
