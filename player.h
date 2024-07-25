#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "ScoreBoard.h"
#include "Board.h"

class Board; // Forward declaration

class Player {
    int color;
    // int turn;
    int level;
    bool isPromotion;
    bool isInCheck;
    int lastRow;
    int lastCol;
    bool inStalemate;
    bool isCheckmate;
    //Board* board;

public:
    Player(int color);
    ~Player();
    void getPlayer(std::string color);
    // void cleanPlayers();
    bool checkPromotion() const;
    void promotion();
    // bool movePiece(int row, int col, int newRow, int newCol, Board *board);
    void computerMove();
    bool checkMate() const;
    bool checkStalemate() const;
    void setLevel(int level);
    int getLevel() const;
    // void setTurn(int turn);
    // int getTurn() const;
    void setInCheck(bool inCheck);
    bool getInCheck() const;
    void reset();
};

#endif // PLAYER_H
