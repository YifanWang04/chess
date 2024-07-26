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
    return !testBoard.getPiece(toRow, toCol)->isInDanger(testBoard);
}

void Level4::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
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
                            int moveValue = evaluateMove(board, row, col, newRow, newCol);

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

    // 优先捕获高价值棋子的移动，然后是将军，安全的移动，最后是其他移动
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

        std::cout << *td;
        gd->show();
    }
}

std::vector<std::tuple<int, int, int, int>> Level4::getAllPossibleMoves(Board* board, int color) {
    std::vector<std::tuple<int, int, int, int>> moves;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            if (piece->getColor() == color) {
                for (int newRow = 0; newRow < 8; ++newRow) {
                    for (int newCol = 0; newCol < 8; ++newCol) {
                        if (board->isMoveable(row, col, newRow, newCol, board) && 
                            !board->willSelfBeInCheck(row, col, newRow, newCol)) {
                            moves.push_back(std::make_tuple(row, col, newRow, newCol));
                        }
                    }
                }
            }
        }
    }
    return moves;
}

int Level4::evaluateMove(Board* board, int fromRow, int fromCol, int toRow, int toCol) {
    int score = 0;
    Piece* targetPiece = board->getPiece(toRow, toCol);

    // Value capturing opponent pieces
    if (targetPiece->getSymbol() != '-') {
        score += getPieceValue(targetPiece);
    }

    // Avoid moving into danger
    Board tempBoard = *board;
    tempBoard.makeMove(fromRow, fromCol, toRow, toCol);
    if (tempBoard.inCheck(getColor())) {
        score -= 100; // A smaller penalty to still consider this move if it captures a high value piece
    }

    return score;
}

int Level4::getPieceValue(Piece* piece) {
    switch (piece->getSymbol()) {
        case 'P': case 'p':
            return 1;
        case 'N': case 'n': case 'B': case 'b':
            return 3;
        case 'R': case 'r':
            return 5;
        case 'Q': case 'q':
            return 9;
        case 'K': case 'k':
            return 100;
        default:
            return 0;
    }
}
