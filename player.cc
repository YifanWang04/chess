#include <memory>
#include "player.h"
#include "board.h"
#include "scoreBoard.h"

Player::Player(int color)
    : color(color), level(0), isPromotion(false), isInCheck(false),
      lastRow(-1), lastCol(-1), inStalemate(false), isCheckmate(false) {}

Player::~Player() {}

void Player::getPlayer(std::string colorStr) {
    if (colorStr == "white") {
        color = 1;
    } else if (colorStr == "black") {
        color = 0;
    }
}

void Player::setLevel(int level) {
    this->level = level;
}

int Player::getLevel() const {
    return level;
}

void Player::setInCheck(bool inCheck) {
    isInCheck = inCheck;
}

bool Player::getInCheck() const {
    return isInCheck;
}

void Player::reset() {
    isPromotion = false;
    isInCheck = false;
    lastRow = -1;
    lastCol = -1;
    inStalemate = false;
    isCheckmate = false;
}

int Player::getColor() const {
    return color;
}
