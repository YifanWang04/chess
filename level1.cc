#include "level1.h"
#include <cstdlib>
#include <ctime>

Level1::Level1(int color) : Computer(color, 1) {}

void Level1::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::pair<int, int>> possibleMoves;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            possibleMoves.push_back({row, col, newRow, newCol});
                        }
                    }
                }
            }
        }
    }

    if (!possibleMoves.empty()) {
        std::srand(std::time(nullptr));
        int moveIndex = std::rand() % possibleMoves.size();
        auto move = possibleMoves[moveIndex];

        board->makeMove(move[0], move[1], move[2], move[3]);
        td->notify(move[2], move[3], board->getPiece(move[2], move[3])->getSymbol());
        td->notify(move[0], move[1], '-');
        gd->notify(move[2], move[3], board->getPiece(move[2], move[3])->getSymbol());
        gd->notify(move[0], move[1], '-');

        cout << *td;
        gd->show();
    }
}
