#include "level4.h"
#include "board.h"
#include <vector>
#include <tuple>
#include <limits>

Level4::Level4(int color) : Computer(color, 4) {}

void Level4::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    std::vector<std::tuple<int, int, int, int>> allMoves = getAllPossibleMoves(board, getColor());
    int bestValue = std::numeric_limits<int>::min();
    std::tuple<int, int, int, int> bestMove;

    for (auto move : allMoves) {
        int fromRow = std::get<0>(move);
        int fromCol = std::get<1>(move);
        int toRow = std::get<2>(move);
        int toCol = std::get<3>(move);

        int moveValue = evaluateMove(board, fromRow, fromCol, toRow, toCol);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    int fromRow = std::get<0>(bestMove);
    int fromCol = std::get<1>(bestMove);
    int toRow = std::get<2>(bestMove);
    int toCol = std::get<3>(bestMove);

    board->makeMove(fromRow, fromCol, toRow, toCol);
    td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
    td->notify(fromRow, fromCol, '-');
    gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
    gd->notify(fromRow, fromCol, '-');

    std::cout << *td;
    gd->show();
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
    if (isKingInDanger(&tempBoard, getColor())) {
        score -= 200;
    }

    // Prefer checks
    if (board->willCheckOpponent(fromRow, fromCol, toRow, toCol)) {
        score += 150;
    }

    return score;
}

bool Level4::isKingInDanger(Board* board, int color) {
    return board->inCheck(color);
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
