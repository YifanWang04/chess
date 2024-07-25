#include "Empty.h"
#include "Board.h"

Empty::Empty(int row, int col, char symbol, int color)
    : Piece(row, col, '-', -1) {}

// need paraphrase
bool Empty::canMove(int newRow, int newCol, Board& board) {
    return false;
}

Piece* Empty::clone() const {
    return new Empty(*this);
}
