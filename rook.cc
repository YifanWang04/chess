#include "rook.h"
#include "board.h"

Rook::Rook(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color), hasMoved(false) {}

Rook::~Rook() {}


bool Rook::canMove(int newRow, int newCol, Board& board) {
    // Checks if the path is on the same row or column
    if (col != newCol && row != newRow) {
        return false;
    }

    // Checks if pathway is blocked
    if (col == newCol) {
        int rowDirection = (newRow > row) ? 1 : -1;
        for (int i = this->getRow() + rowDirection; i != newRow; i += rowDirection) {
            if (board.getPiece(i, col)->getSymbol() != '-') {
                return false;
            }
        }
    } else if (row == newRow) {
        int colDirection = (newCol > col) ? 1 : -1;
        for (int i = this->getCol() + colDirection; i != newCol; i += colDirection) {
            if (board.getPiece(row, i)->getSymbol() != '-') {
                return false;
            }
        }
    }

    return true;
}


bool Rook::getHasMoved() {
    return hasMoved;
}

Piece* Rook::clone() const {
    return new Rook(*this);
}

void Rook::setHasMoved(bool moved) {
    hasMoved = moved;
}
