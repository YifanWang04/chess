#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "board.h"

class Computer : public Player {
public:
    Computer(int color, int level);
    virtual ~Computer();
    virtual void computerMove(Board *board, TextDisplay *td, GraphDisplay *gd) = 0; // Pure virtual function
};

#endif // COMPUTER_H
