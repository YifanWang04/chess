#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    bool hasMoved;
public:
    Rook(int row, int col, char symbol, int color);
    ~Rook();
    bool canMove(int newRow, int newCol, Board& board) override;
    Piece* clone() const;
    // void castling(int newRow, int newCol);
    bool getHasMoved();
    void setHasMoved(bool moved);
    
};

#endif
