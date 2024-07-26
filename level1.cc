#include "level1.h"
#include <cstdlib>
#include <ctime>
#include <vector>

Level1::Level1(int color) : Computer(color, 1) {
    std::srand(std::time(0)); // Seed for random number generation
}

void Level1::computerMove(Board *board, TextDisplay *td, GraphDisplay *gd) {
    std::vector<std::pair<int, int>> moves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece *piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            moves.push_back(std::make_pair(row * 8 + col, newRow * 8 + newCol));
                        }
                    }
                }
            }
        }
    }

    if (!moves.empty()) {
        int randomIndex = std::rand() % moves.size();
        int from = moves[randomIndex].first;
        int to = moves[randomIndex].second;
        int fromRow = from / 8;
        int fromCol = from % 8;
        int toRow = to / 8;
        int toCol = to % 8;

        board->makeMove(fromRow, fromCol, toRow, toCol);

        td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        td->notify(fromRow, fromCol, '-');

        gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        gd->notify(fromRow, fromCol, '-');

        gd->show();
    }
}
