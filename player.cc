#include "Player.h"
#include "Board.h"
#include "ScoreBoard.h"

Player::Player(int color)
    : color(color), level(0), isPromotion(false), isInCheck(false),
      lastRow(-1), lastCol(-1), inStalemate(false), isCheckmate(false) {}

Player::~Player() {
    // delete board;
    // board = NULL;
}


void Player::getPlayer(std::string colorStr) {
    if (colorStr == "white") {
        color = 1;
    } else if (colorStr == "black") {
        color = 0;
    }
}


// void Player::cleanPlayers() {
//     // Implementation for cleaning players if needed
// }


// bool Player::checkPromotion() const {
//     return isPromotion;
// }

// void Player::promotion() {
//     // Promotion logic: Usually involves changing a pawn to a queen, rook, bishop, or knight
//     isPromotion = true;
// }

// bool Player::movePiece(int row, int col, int newRow, int newCol, Board *board) {
//     if (board->isMoveable(row, col, newRow, newCol, board)) {
//         board->makeMove(row, col, newRow, newCol);
//         return true;
//     }
//     return false;
// }

void Player::computerMove() {
    // Logic for computer move (if any)
}

bool Player::checkMate() const {
    return isCheckmate;
}

bool Player::checkStalemate() const {
    return inStalemate;
}

void Player::setLevel(int level) {
    this->level = level;
}

int Player::getLevel() const {
    return level;
}

// void Player::setTurn(int turn) {
//     this->turn = turn;
// }

// int Player::getTurn() const {
//     return turn;
// }

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
