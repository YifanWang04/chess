#include <memory>
#include "king.h"
#include "board.h"

King::King(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color), hasMoved(false), isCheck(false) {}

King::~King() {}

// paraphrase
// bool King::canMove(int newRow, int newCol, Board& board) {
//     // Checks if moved in direct one move
//     if (abs(newRow - row) <= 1 && abs(newCol - col) <= 1) {
//         return true;
//     }

//     // Check for castling
//     if (!hasMoved && newRow == row && (newCol == col + 2 || newCol == col - 2)) {
//         int rookCol = (newCol == col + 2) ? 7 : 0;
//         Piece *rookPosition = board.getPiece(row, rookCol);
//         if (Rook* rook = dynamic_cast<Rook*>(rookPosition)) {
//             if (!rook->getHasMoved() && board.canCastle(row, col, newRow, newCol)) {
//                 return true;
//             }
//         }

//     }

//     return false;
// }

bool King::canMove(int newRow, int newCol, Board& board) {

    // Regular move logic
    if (abs(newRow - row) <= 1 && abs(newCol - col) <= 1) {
        return true;
    }

    return false;
}


// void King::castling(int newRow, int newCol) {
//     // Castling logic
// }

bool King::getIsCheck() {
    return isCheck;
}

bool King::getHasMoved() {
    return hasMoved;
}

Piece* King::clone() const {
    return new King(*this);
}

void King::setHasMoved(bool moved) {
    hasMoved = moved; 
}