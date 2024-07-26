#include <memory>
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <string>

class ScoreBoard {
    double whiteScore;
    double blackScore;

public:
    ScoreBoard();
    double getWhiteScore() const;
    double getBlackScore() const;
    void setWhiteScore(double score);
    void setBlackScore(double score);
    void startGame();
    void endGame(const std::string& player);
    void endGame();
    void printResults() const;
};

#endif // SCOREBOARD_H
