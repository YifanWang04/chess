#include <memory>
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "scoreBoard.h"
#include "board.h"

class Board; // Forward declaration

class Player {
protected:
    int color;
    int level;
    bool isPromotion;
    bool isInCheck;
    int lastRow;
    int lastCol;
    bool inStalemate;
    bool isCheckmate;

public:
    Player(int color);
    virtual ~Player();
    void getPlayer(std::string color);
    bool checkPromotion() const;
    void promotion();
    virtual void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) = 0; // Pure virtual
    bool checkMate() const;
    bool checkStalemate() const;
    void setLevel(int level);
    int getLevel() const;
    void setInCheck(bool inCheck);
    bool getInCheck() const;
    void reset();
    int getColor() const; // Add this method
};

#endif // PLAYER_H
