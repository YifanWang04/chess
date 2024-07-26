#include "level3.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <tuple>

Level3::Level3(int color) : Computer(color, 3) {}

bool Level3::isSafeAfterMove(Board* board, int fromRow, int fromCol, int toRow, int toCol) {
    // Simulate the move
    Board testBoard(*board);
    testBoard.makeMove(fromRow, fromCol, toRow, toCol);
    
    // Check if the piece will be in danger after the move
    return !testBoard.getPiece(toRow, toCol)->isInDanger(testBoard);
}

void Level3::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::tuple<int, int, int, int>> bestMoves;
    std::vector<std::tuple<int, int, int, int>> capturingMoves;
    std::vector<std::tuple<int, int, int, int>> checkingMoves;
    std::vector<std::tuple<int, int, int, int>> safeMoves;
    std::vector<std::tuple<int, int, int, int>> otherMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            
                            // Capture move and ensure it's safe
                            if (board->getPiece(newRow, newCol)->getColor() != -1 && 
                                board->getPiece(newRow, newCol)->getColor() != piece->getColor() &&
                                isSafeAfterMove(board, row, col, newRow, newCol)) {
                                capturingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Check move and ensure it's safe
                            else if (board->willCheckOpponent(row, col, newRow, newCol) &&
                                     isSafeAfterMove(board, row, col, newRow, newCol)) {
                                checkingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Safe move
                            else if (isSafeAfterMove(board, row, col, newRow, newCol)) {
                                safeMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Other move
                            else {
                                otherMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                        }
                    }
                }
            }
        }
    }

    // Prefer capturing moves, then checking moves, then safe moves, and lastly other moves
    if (!capturingMoves.empty()) {
        bestMoves = capturingMoves;
    } else if (!checkingMoves.empty()) {
        bestMoves = checkingMoves;
    } else if (!safeMoves.empty()) {
        bestMoves = safeMoves;
    } else {
        bestMoves = otherMoves;
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

        cout << *td;
        gd->show();
    }
}
