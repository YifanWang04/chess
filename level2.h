#ifndef LEVEL2_H
#define LEVEL2_H

#include "computer.h"
#include <vector>
#include <tuple>

class Level2 : public Computer {
public:
    Level2(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;
};

#endif // LEVEL2_H
