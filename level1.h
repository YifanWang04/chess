#ifndef LEVEL1_H
#define LEVEL1_H

#include "computer.h"

class Level1 : public Computer {
public:
    Level1(int color);
    void computerMove(Board *board, TextDisplay *td, GraphDisplay *gd) override; // Override the pure virtual function
};

#endif // LEVEL1_H
