#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer(int color, int level);
    void makeMove(Board* board) override;
private:
    int level;
    
};

#endif
