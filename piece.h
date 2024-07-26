#include <memory>
#ifndef PIECE_H
#define PIECE_H

#include "textDisplay.h"
#include <cmath> 
#include <vector>

using namespace std;

class Board;

class Piece {
protected:
    int row;
    int col;
    char symbol;
    int color;

public:
    Piece(int row, int col, char symbol, int color);
    virtual Piece* clone() const = 0;
    virtual ~Piece();

    void move(int newRow, int newCol);
    virtual bool canMove(int newRow, int newCol, Board& board) = 0;
    bool isInDanger(Board &board);
    void notify(TextDisplay* text);

    char getSymbol() const;
    int getRow() const;
    int getCol() const;
    void setRow(int newRow);
    void setCol(int newCol);
    int getColor() const;
};

#endif // PIECE_H
