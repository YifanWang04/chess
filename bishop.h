#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(int row, int col, char symbol, int color);
    Piece* clone() const;
    ~Bishop();
    bool canMove(int newRow, int newCol, Board& board) override;
};

#endif
