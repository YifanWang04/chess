#include <memory>
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
    bool hasMoved;
    bool isCheck;
public:
    King(int row, int col, char symbol, int color);
    Piece* clone() const;
    ~King();
    bool canMove(int newRow, int newCol, Board& board) override;
    // void castling(int newRow, int newCol);
    bool getIsCheck();
    bool getHasMoved();
    void setHasMoved(bool moved);

};

#endif
