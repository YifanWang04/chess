#include "level4.h"
#include "board.h"
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

Level4::Level4(int color) : Computer(color, 4) {}

void Level4::computerMove(Board* board, TextDisplay* td, GraphDisplay* gd) {
    int bestValue = std::numeric_limits<int>::min();
    std::tuple<int, int, int, int> bestMove;

    std::vector<std::tuple<int, int, int, int>> allMoves = getAllPossibleMoves(board, getColor());
    for (auto move : allMoves) {
        int fromRow = std::get<0>(move);
        int fromCol = std::get<1>(move);
        int toRow = std::get<2>(move);
        int toCol = std::get<3>(move);

        Board tempBoard = *board;
        tempBoard.makeMove(fromRow, fromCol, toRow, toCol);

        int boardValue = minimax(&tempBoard, 3, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);

        if (boardValue > bestValue) {
            bestValue = boardValue;
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

int Level4::minimax(Board* board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    std::vector<std::tuple<int, int, int, int>> allMoves = getAllPossibleMoves(board, maximizingPlayer ? getColor() : 1 - getColor());

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (auto move : allMoves) {
            int fromRow = std::get<0>(move);
            int fromCol = std::get<1>(move);
            int toRow = std::get<2>(move);
            int toCol = std::get<3>(move);

            Board tempBoard = *board;
            tempBoard.makeMove(fromRow, fromCol, toRow, toCol);
            int eval = minimax(&tempBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (auto move : allMoves) {
            int fromRow = std::get<0>(move);
            int fromCol = std::get<1>(move);
            int toRow = std::get<2>(move);
            int toCol = std::get<3>(move);

            Board tempBoard = *board;
            tempBoard.makeMove(fromRow, fromCol, toRow, toCol);
            int eval = minimax(&tempBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

int Level4::evaluateBoard(Board* board) {
    int score = 0;
    int pieceValue[256];
    pieceValue['P'] = 100;
    pieceValue['R'] = 500;
    pieceValue['N'] = 320;
    pieceValue['B'] = 330;
    pieceValue['Q'] = 900;
    pieceValue['K'] = 20000;
    pieceValue['p'] = -100;
    pieceValue['r'] = -500;
    pieceValue['n'] = -320;
    pieceValue['b'] = -330;
    pieceValue['q'] = -900;
    pieceValue['k'] = -20000;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board->getPiece(row, col);
            char symbol = piece->getSymbol();
            score += pieceValue[symbol];
        }
    }
    return score;
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
