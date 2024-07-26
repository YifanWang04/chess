#include <memory>
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

// class Board; // Forward declaration of Board class

class Pawn : public Piece {
    // bool isEnpassant;
    bool isFirstMove;
public:
    Pawn(int row, int col, char symbol, int color);
    ~Pawn();
    bool canMove(int newRow, int newCol, Board& board) override;
    Piece* clone() const;
    void setIsFirstMove(bool value);
    bool getIsFirstMove() const;
};

#endif
