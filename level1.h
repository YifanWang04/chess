#include <memory>
#ifndef LEVEL1_H
#define LEVEL1_H

#include "computer.h"
#include <vector>
#include <tuple>

class Level1 : public Computer {
public:
    Level1(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;
};

#endif // LEVEL1_H
