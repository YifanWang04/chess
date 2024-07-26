#include "level3.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <tuple>

Level3::Level3(int color) : Computer(color, 3) {}

void Level3::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::tuple<int, int, int, int>> avoidingMoves;
    std::vector<std::tuple<int, int, int, int>> capturingMoves;
    std::vector<std::tuple<int, int, int, int>> checkingMoves;
    std::vector<std::tuple<int, int, int, int>> otherMoves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == getColor()) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            
                            // Temporarily make the move
                            Piece* targetPiece = board->getPiece(newRow, newCol);
                            Piece* movingPiece = board->getPiece(row, col);
                            board->makeMove(row, col, newRow, newCol);

                            // Avoiding capture move
                            if (!movingPiece->isInDanger(*board)) {
                                avoidingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Capture move
                            if (targetPiece->getColor() != -1 && targetPiece->getColor() != piece->getColor()) {
                                capturingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Check move
                            if (board->willCheckOpponent(newRow, newCol, movingPiece->getRow(), movingPiece->getCol())) {
                                checkingMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }
                            // Other move
                            else {
                                otherMoves.push_back(std::make_tuple(row, col, newRow, newCol));
                            }

                            // Undo the move
                            board->makeMove(newRow, newCol, row, col);
                        }
                    }
                }
            }
        }
    }

    // Prefer avoiding capture moves, then capturing moves, then checking moves, and lastly other moves
    std::vector<std::tuple<int, int, int, int>>* chosenMoves = nullptr;
    if (!avoidingMoves.empty()) {
        chosenMoves = &avoidingMoves;
    } else if (!capturingMoves.empty()) {
        chosenMoves = &capturingMoves;
    } else if (!checkingMoves.empty()) {
        chosenMoves = &checkingMoves;
    } else {
        chosenMoves = &otherMoves;
    }

    if (chosenMoves != nullptr && !chosenMoves->empty()) {
        std::srand(std::time(nullptr));
        int moveIndex = std::rand() % chosenMoves->size();
        auto move = (*chosenMoves)[moveIndex];

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
