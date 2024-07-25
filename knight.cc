#include "knight.h"
#include "board.h"

Knight::Knight(int row, int col, char symbol, int color)
    : Piece(row, col, symbol, color) {}

Knight::~Knight() {}

// paraphrase
bool Knight::canMove(int newRow, int newCol, Board& board) {
    // Checks if input cell is in an L-shape from current cell
    if (!(abs(col - newCol) == 2 && abs(row - newRow) == 1)) {
        if (!(abs(col - newCol) == 1 && abs(row - newRow) == 2)) { 

            return false;
        }
    } 
    else if ((abs(col - newCol) == 2 && abs(row - newRow) == 1) || (abs(col - newCol) == 1 && abs(row - newRow) == 2)) {
        if (board.getPiece(newRow, newCol)->getSymbol() != '-') 
        {   
            cout << "pass1" << endl;
            if (board.getPiece(newRow, newCol)->getColor() == this->getColor()) 
            {
                return false;
            }
        }
    }
    cout << "pasS TREU" << endl;    
    return true;
}

Piece* Knight::clone() const {
    return new Knight(*this);
}
