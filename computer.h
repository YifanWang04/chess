#include <memory>
#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {
public:
    Computer(int color, int level);
    virtual ~Computer();
    virtual void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) = 0; // Pure virtual
};

#endif // COMPUTER_H
