#include "level1.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <tuple>

Level1::Level1(int color) : Computer(color, 1) {}

void Level1::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::tuple<int, int, int, int>> possibleMoves;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            possibleMoves.push_back(std::make_tuple(row, col, newRow, newCol));
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

        int fromRow = std::get<0>(move);
        int fromCol = std::get<1>(move);
        int toRow = std::get<2>(move);
        int toCol = std::get<3>(move);

        board->makeMove(fromRow, fromCol, toRow, toCol);
        td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        td->notify(fromRow, fromCol, '-');
        gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        gd->notify(fromRow, fromCol, '-');

        cout << *td;
        gd->show();
    }
}
