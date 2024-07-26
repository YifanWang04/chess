#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player {
public:
    Human(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;
};

#endif // HUMAN_H
