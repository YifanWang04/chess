#include "Pawn.h"
#include "Board.h"
#include "piece.h"

Pawn::Pawn(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color), isFirstMove(true) {}

Pawn::~Pawn() {}

// need paraphrase
bool Pawn::canMove(int newRow, int newCol, Board& board) {

    int direction = (this->getColor() == 0) ? 1 : -1; // determines the movement direction based on pawn's color
    int initialRow = (this->getColor() == 0) ? 1 : 6; // sets the initial row based on pawn's color

    // Check moving forward by one square
    if (newCol == col && newRow == row + direction && board.getPiece(newRow, newCol)->getSymbol() == '-') {
        return true;
    }

    // Check moving forward by two squares from the starting position 
    if (col == newCol && row + 2 * direction == newRow) {
        if (this->getRow() == initialRow) {
            if (board.getPiece(newRow, newCol)->getSymbol() == '-' && 
                board.getPiece(newRow - direction, newCol)->getSymbol() == '-') {
                cout << "ready to return true" << endl;
                return true; 
            }
        }
    }

    // Check capturing diagonally
    if (row + direction == newRow && (col + 1 == newCol || col - 1 == newCol)) {
        if (board.getPiece(newRow, newCol)->getSymbol() != '-') {
            if (board.getPiece(newRow, newCol)->getColor() != this->getColor()) {
                return true; 
            }
        }
    }


    // check passent
    if (abs(newCol - col) == 1 && newRow == row + direction && board.getPiece(newRow, newCol)->getSymbol() == '-') {
        if (board.getEnPassantTarget().first == newRow && board.getEnPassantTarget().second == newCol) {
            return true;
        }
    }
    return false;
}

Piece* Pawn::clone() const {
    return new Pawn(*this);
}

void Pawn::setIsFirstMove(bool value) {
    isFirstMove = value;
}

bool Pawn::getIsFirstMove() const {
    return isFirstMove;
}
