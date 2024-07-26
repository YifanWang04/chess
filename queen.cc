#include <memory>
#include "queen.h"
#include "board.h"

Queen::Queen(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color) {}

Queen::~Queen() {}

// paraphrase
bool Queen::canMove(int newRow, int newCol, Board& board) {
    // Check if the target position is on the same column, same row, or diagonal
    if (!((abs(col - newCol) == abs(row - newRow)) || (col == newCol) || (row == newRow))) {
        return false;
    }

    // Check if the pathway is blocked
    if (col == newCol) { // column path
        int rowDirection = (newRow > row) ? 1 : -1;
        for (int i = row + rowDirection; i != newRow; i += rowDirection) {
            if (board.getPiece(i, col)->getSymbol() != '-') {
                return false;
            }
        }
    } else if (row == newRow) { // row path
        int colDirection = (newCol > col) ? 1 : -1;
        for (int i = col + colDirection; i != newCol; i += colDirection) {
            if (board.getPiece(row, i)->getSymbol() != '-') {
                return false;
            }
        }
    } else { // diagonal path
        int colDirection = (newCol > col) ? 1 : -1;
        int rowDirection = (newRow > row) ? 1 : -1;
        int j = row + rowDirection;
        for (int i = col + colDirection; i != newCol; i += colDirection) {
            if (board.getPiece(j, i)->getSymbol() != '-') {
                return false;
            }
            j += rowDirection;
        }
    }

    return true;
}

Piece* Queen::clone() const {
    return new Queen(*this);
}
