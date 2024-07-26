#include "piece.h"
#include "board.h"
#include "textDisplay.h" 

Piece::Piece(int row, int col, char symbol, int color)
    : row(row), col(col), symbol(symbol), color(color) {}

Piece::~Piece() {}

char Piece::getSymbol() const { return symbol; }

int Piece::getRow() const { return row; }

int Piece::getCol() const { return col; }

int Piece::getColor() const { return color; }

void Piece::setRow(int newRow) { row = newRow; }

void Piece::setCol(int newCol) { col = newCol; }

void Piece::notify(TextDisplay* text) {
    text->notify(row, col, symbol);
}

void Piece::move(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

bool Piece::isInDanger(Board &board) {
    int boardSize = board.getBoardSize();
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            Piece* currentPiece = board.getPiece(row, col);
            if (currentPiece != nullptr && currentPiece->getColor() != color && currentPiece->getSymbol() != '-') {
                if (currentPiece->canMove(this->getRow(), this->getCol(), board)) {;
                    return true;
                }
            }
        }
    }
    return false;
}

