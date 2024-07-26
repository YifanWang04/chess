#include "computer.h"

Computer::Computer(int color, int level) : Player(color) {
    setLevel(level);
}

Computer::~Computer() {}
