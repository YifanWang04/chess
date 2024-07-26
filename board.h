#include <memory>
#ifndef BOARD_H
#define BOARD_H

#include "textDisplay.h"
#include "graphDisplay.h"
#include "piece.h"
#include "king.h"
#include "rook.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "empty.h"
#include <vector>
#include <utility>

class Player;

class Board {
    // int boardSize;
    std::pair<int, int> enPassantTarget;



public:
    Board();
    ~Board();
    Board(const Board& other);

    int boardSize;
    Piece*** pieces;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    std::unique_ptr<King> whiteKing;
    std::unique_ptr<King> blackKing;

    void setupBoard(TextDisplay* td);
    void setupBoard(GraphDisplay* gd);
    void copyBoard(const Board board);
    Piece* createPiece(char symbol, int row, int col);
    void makeMove(int row, int col, int newRow, int newCol);
    bool isMoveable(int row, int col, int newRow, int newCol, Board* board) const;

    bool willCheckOpponent(int fromRow, int fromCol, int toRow, int toCol);
    bool willSelfBeInCheck(int fromRow, int fromCol, int toRow, int toCol);
    
    int getBoardSize() const;
    Piece* getPiece(int row, int col) const;

    bool inCheck(int color);
    bool inStalemate(bool color);
    bool inCheckmate(bool color);

    // special rules
    bool checkPromotion(int fromRow, int fromCol, int toRow, int toCol, char newPiece);
    void promotion(int row, int col, char newPiece);
    bool canCastle(int row, int col, int newRow, int newCol);
    bool canCaptureEnPassant(int row, int col, int newRow, int newCol);
    std::pair<int, int> getEnPassantTarget() const;
    void resetEnPassantTarget();
    void captureEnPassant(int row, int col, int newRow, int newCol);
};

#endif
