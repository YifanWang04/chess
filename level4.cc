#include "level4.h"
#include "board.h"
#include <vector>
#include <tuple>
#include <limits>
#include <cstdlib>
#include <ctime>

Level4::Level4(int color) : Computer(color, 4) {}

bool Level4::isSafeAfterMove(Board* board, int fromRow, int fromCol, int toRow, int toCol) {
    Board testBoard(*board);
    testBoard.makeMove(fromRow, fromCol, toRow, toCol);
    return !testBoard.inCheck(getColor());
}

void Level4::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::tuple<int, int, int, int>> bestMoves;
    std::vector<std::tuple<int, int, int, int>> capturingMoves;
    std::vector<std::tuple<int, int, int, int>> checkingMoves;
    std::vector<std::tuple<int, int, int, int>> safeMoves;
    std::vector<std::tuple<int, int, int, int>> checkmateMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            Board testBoard(*board);
                            testBoard.makeMove(row, col, newRow, newCol);
                            
                            // Check if the move can lead to a checkmate
                            if (testBoard.inCheckmate(1 - getColor())) {
                                checkmateMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                                continue;
                            }
                            
                            // Capture move and ensure it's safe
                            if (board->getPiece(newRow, newCol)->getColor() != -1 && 
                                board->getPiece(newRow, newCol)->getColor() != piece->getColor() &&
                                isSafeAfterMove(board, row, col, newRow, newCol)) {
                                capturingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Check move
                            else if (testBoard.inCheck(1 - getColor())) {
                                checkingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Safe move
                            else {
                                safeMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                        }
                    }
                }
            }
        }
    }

    // Prefer checkmate moves, then capturing moves, then checking moves, then safe moves
    if (!checkmateMoves.empty()) {
        bestMoves = checkmateMoves;
    } else if (!capturingMoves.empty()) {
        bestMoves = capturingMoves;
    } else if (!checkingMoves.empty()) {
        bestMoves = checkingMoves;
    } else {
        bestMoves = safeMoves;
    }

    if (!bestMoves.empty()) {
        std::srand(std::time(nullptr));
        int moveIndex = std::rand() % bestMoves.size();
        auto move = bestMoves[moveIndex];

        int fromRow = std::get<0>(move);
        int fromCol = std::get<1>(move);
        int toRow = std::get<2>(move);
        int toCol = std::get<3>(move);

        board->makeMove(fromRow, fromCol, toRow, toCol);
        td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        td->notify(fromRow, fromCol, '-');
        gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
        gd->notify(fromRow, fromCol, '-');

        std::cout << *td;
        gd->show();
    }
}
