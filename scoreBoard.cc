#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : whiteScore(0.0), blackScore(0.0) {}

double ScoreBoard::getWhiteScore() const {
    return whiteScore;
}

double ScoreBoard::getBlackScore() const {
    return blackScore;
}

void ScoreBoard::setWhiteScore(double score) {
    whiteScore = score;
}

void ScoreBoard::setBlackScore(double score) {
    blackScore = score;
}

void ScoreBoard::startGame() {
    whiteScore = 0.0;
    blackScore = 0.0;
}

// win or lose
void ScoreBoard::endGame(const std::string& player) {
    if (player == "white") {
        whiteScore += 1.0;
    } else if (player == "black") {
        blackScore += 1.0;
    }
}

// stalemate
void ScoreBoard::endGame() {
    whiteScore += 0.5;
    blackScore += 0.5;
}

void ScoreBoard::printResults() const {
    std::cout << "White: " << whiteScore << "\n";
    std::cout << "Black: " << blackScore << "\n";
}
