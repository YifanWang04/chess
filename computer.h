#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {
public:
    Computer(int color) : Player(color) {}
    virtual void makeMove(Board* board) = 0;
};

#endif // COMPUTER_H
