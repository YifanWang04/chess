#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color) {}

Bishop::~Bishop() {}

// need paraphrase
bool Bishop::canMove(int newRow, int newCol, Board& board) {
    
    // Checks if the target position is on the same col
    if (abs(col - newCol) != abs(row - newRow)) return false;

    // check if pathway is blocked
    int colDirection = (newCol > col) ? 1 : -1;
    int rowDirection = (newRow > row) ? 1 : -1;
    int currentRow = row + rowDirection;
    int currentCol = col + colDirection;

    while (currentRow != newRow && currentCol != newCol) {
        if (board.getPiece(currentRow, currentCol)->getSymbol() != '-') {
            return false;
        }
        currentRow += rowDirection;
        currentCol += colDirection;
    }

    return true;
}

Piece* Bishop::clone() const {
    return new Bishop(*this);
}