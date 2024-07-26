#ifndef LEVEL3_H
#define LEVEL3_H

#include "computer.h"
#include <vector>
#include <tuple>

class Level3 : public Computer {
public:
    Level3(int color);
    void computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) override;
private:
    bool isSafeAfterMove(Board* board, int fromRow, int fromCol, int toRow, int toCol);
};

#endif // LEVEL3_H
