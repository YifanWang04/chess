#include "level1.h"
#include <vector>
#include <cstdlib>
#include <ctime>

void Level1::makeMove(Board* board) {
    std::vector<std::pair<int, int>> possibleMoves;
    std::srand(std::time(0));

    // Loop through the board to collect all legal moves for the computer's pieces
    for (int row = 0; row < board->getBoardSize(); ++row) {
        for (int col = 0; col < board->getBoardSize(); ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == this->color) {
                for (int newRow = 0; newRow < board->getBoardSize(); ++newRow) {
                    for (int newCol = 0; newCol < board->getBoardSize(); ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            possibleMoves.push_back(std::make_pair(row * 8 + col, newRow * 8 + newCol));
                        }
                    }
                }
            }
        }
    }

    // Randomly select a move from the possible moves
    if (!possibleMoves.empty()) {
        int index = std::rand() % possibleMoves.size();
        int from = possibleMoves[index].first;
        int to = possibleMoves[index].second;

        int fromRow = from / 8;
        int fromCol = from % 8;
        int toRow = to / 8;
        int toCol = to % 8;

        board->makeMove(fromRow, fromCol, toRow, toCol);
    }
}
