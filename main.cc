// main.cc
#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "human.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "textDisplay.h"
#include "scoreBoard.h"
#include "graphDisplay.h"

using namespace std;

const string validPieces = "PRNBQKprnbqk-";

int main() {
    Board* board = new Board();
    Board* customizedBoard = nullptr;
    TextDisplay *td = new TextDisplay();
    GraphDisplay *gd = new GraphDisplay();
    ScoreBoard scoreboard;
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;
    bool gameRunning = false;
    int currentPlayerTurn = 0; // 0 for white, 1 for black
    bool defaultSetup = true;

    cout << "Starting game..." << endl;
    cout << "Select your game mode" << endl;
    cout << "Enter 'quit' to leave the game" << endl;
    cout << "Enter Command" << endl;

    string command;
    while (getline(cin, command)) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "quit") {
            cout << "Quitting the game..." << endl;
            break;
        } else if (cmd == "game") {
            string white, black;
            iss >> white >> black;
            cout << "Setting up game: " << white << " vs " << black << endl;

            if (white == "human") {
                whitePlayer = new Human(0);
            } else if (white.substr(0, 8) == "computer" && white.length() == 11 && isdigit(white[9])) {
                int level = white[9] - '0';
                if (level == 1) {
                    whitePlayer = new Level1(0);
                } else if (level == 2) {
                    whitePlayer = new Level2(0);
                } else if (level == 3) {
                    whitePlayer = new Level3(0);
                }

            } else {
                cout << "Invalid player type for white player. Must be 'human' or 'computer[1-4]'." << endl;
                continue;
            }

            if (black == "human") {
                blackPlayer = new Human(1);
            } else if (black.substr(0, 8) == "computer" && black.length() == 11 && isdigit(black[9])) {
                int level = black[9] - '0';
                if (level == 1) {
                    blackPlayer = new Level1(1);
                } else if (level == 2) {
                    blackPlayer = new Level2(1);
                } else if (level == 3) {
                    blackPlayer = new Level3(1);
                }
            } else {
                cout << "Invalid player type for black player. Must be 'human' or 'computer[1-4]'." << endl;
                continue;
            }

            delete board;
            delete td;
            delete gd;

            if (defaultSetup) {
                board = new Board();
                td = new TextDisplay();
                gd = new GraphDisplay();

                board->setupBoard(td);
                board->setupBoard(gd);
            } else if (customizedBoard != nullptr) {
                board = new Board(*customizedBoard);
                td = new TextDisplay();
                gd = new GraphDisplay();

                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 8; ++j) {
                        td->notify(i, j, board->getPiece(i, j)->getSymbol());
                        gd->notify(i, j, board->getPiece(i, j)->getSymbol());
                    }
                }
            }

            gameRunning = true;
            currentPlayerTurn = 0; // Start with white player
            cout << *td;
            gd->clear();
            gd->initBoard(); // Ensure the board is initialized correctly
            // Notify all pieces to graphical display
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    gd->notify(i, j, board->getPiece(i, j)->getSymbol());
                }
            }
            gd->show();  // Show the entire board at once
        } else if (cmd == "resign") {
            if (!gameRunning) {
                cout << "No game is currently running." << endl;
                continue;
            }

            if (currentPlayerTurn == 0) {
                cout << "Black wins!" << endl;
                scoreboard.endGame("black");
            } else if (currentPlayerTurn == 1) {
                cout << "White wins!" << endl;
                scoreboard.endGame("white");
            }
            gameRunning = false;
        } else if (cmd == "move") {
            if (!gameRunning) {
                cout << "No game is currently running. You can't move" << endl;
                continue;
            }

            Player* currentPlayer = (currentPlayerTurn == 0) ? whitePlayer : blackPlayer;

            if (dynamic_cast<Computer*>(currentPlayer)) {
                currentPlayer->computerMove(board, td, gd);
                currentPlayerTurn = (currentPlayerTurn == 0) ? 1 : 0;
                board->inCheck(currentPlayerTurn);

                // Check for end conditions
                if (board->inCheckmate(currentPlayerTurn)) {
                    scoreboard.endGame(currentPlayerTurn == 0 ? "black" : "white");
                    gameRunning = false;
                }
                if (board->inStalemate(currentPlayerTurn)) {
                    scoreboard.endGame();
                    gameRunning = false;
                }
                cout << "Moved" << endl;
            } else {
                string from, to, promoteTo;
                iss >> from >> to >> promoteTo;

                int fromRow = from[1] - '1';
                int fromCol = from[0] - 'a';
                int toRow = to[1] - '1';
                int toCol = to[0] - 'a';

                if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
                    cout << "You cannot move out of bound" << endl;
                    continue;
                }
                if (board->getPiece(fromRow, fromCol)->getSymbol() == '-') {
                    cout << "You cannot move an empty square" << endl;
                    continue;
                }

                if (currentPlayerTurn != board->getPiece(fromRow, fromCol)->getColor()) {
                    cout << "You cannot move your opponent's piece. Try again." << endl;
                    continue;
                }

                // Check if the move puts the player in self-check
                if (board->willSelfBeInCheck(fromRow, fromCol, toRow, toCol)) {
                    cout << "This move puts yourself in check" << endl;
                    continue;
                }

                // Check for castling
                if ((board->getPiece(fromRow, fromCol)->getSymbol() == 'K' || board->getPiece(fromRow, fromCol)->getSymbol() == 'k') &&
                    abs(toCol - fromCol) == 2) {
                    if (board->canCastle(fromRow, fromCol, toRow, toCol)) {
                        board->makeMove(fromRow, fromCol, toRow, toCol);

                        td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                        td->notify(fromRow, fromCol, '-');

                        int rookCol = (toCol == fromCol + 2) ? 7 : 0;
                        int newRookCol = (toCol == fromCol + 2) ? toCol - 1 : toCol + 1;
                        int rookRow = fromRow;

                        // Update rook position
                        td->notify(rookRow, newRookCol, board->getPiece(rookRow, newRookCol)->getSymbol());
                        td->notify(rookRow, rookCol, '-');

                        // Update GraphDisplay
                        gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                        gd->notify(fromRow, fromCol, '-');
                        gd->notify(rookRow, newRookCol, board->getPiece(rookRow, newRookCol)->getSymbol());
                        gd->notify(rookRow, rookCol, '-');

                        cout << *td;
                        gd->show();
                        currentPlayerTurn = (currentPlayerTurn == 0) ? 1 : 0;
                        board->inCheck(currentPlayerTurn);
                        if (board->inCheckmate(currentPlayerTurn)) {
                            scoreboard.endGame(currentPlayerTurn == 0 ? "black" : "white");
                            gameRunning = false;
                        }
                        if (board->inStalemate(currentPlayerTurn)) {
                            scoreboard.endGame();
                            gameRunning = false;
                        }
                        continue;
                    } else {
                        cout << "Castling move is not valid" << endl;
                        continue;
                    }
                }

                // Check for en passant
                if ((board->getPiece(fromRow, fromCol)->getSymbol() == 'P' || board->getPiece(fromRow, fromCol)->getSymbol() == 'p') &&
                    board->canCaptureEnPassant(fromRow, fromCol, toRow, toCol)) {
                    board->captureEnPassant(fromRow, fromCol, toRow, toCol);
                    td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                    td->notify(fromRow, fromCol, '-');
                    td->notify((board->getPiece(toRow, toCol)->getSymbol() == 'P') ? toRow - 1 : toRow + 1, toCol, '-');
                    gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                    gd->notify(fromRow, fromCol, '-');
                    gd->notify((board->getPiece(toRow, toCol)->getSymbol() == 'P') ? toRow - 1 : toRow + 1, toCol, '-');
                    cout << *td;
                    gd->show();
                    currentPlayerTurn = (currentPlayerTurn == 0) ? 1 : 0;
                    board->inCheck(currentPlayerTurn);
                    if (board->inCheckmate(currentPlayerTurn)) {
                        scoreboard.endGame(currentPlayerTurn == 0 ? "black" : "white");
                        gameRunning = false;
                    }
                    if (board->inStalemate(currentPlayerTurn)) {
                        scoreboard.endGame();
                        gameRunning = false;
                    }
                    continue;
                }

                if (board->isMoveable(fromRow, fromCol, toRow, toCol, board)) {

                    // check promotion
                    if (promoteTo.size() == 1) {
                        if (!board->checkPromotion(fromRow, fromCol, toRow, toCol, promoteTo[0])) continue;
                        board->makeMove(fromRow, fromCol, toRow, toCol);
                        board->promotion(toRow, toCol, promoteTo[0]);
                    } else {
                        board->makeMove(fromRow, fromCol, toRow, toCol);
                    }

                    // notify display
                    td->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                    td->notify(fromRow, fromCol, '-');
                    gd->notify(toRow, toCol, board->getPiece(toRow, toCol)->getSymbol());
                    gd->notify(fromRow, fromCol, '-');

                    cout << *td;
                    gd->show();
                    currentPlayerTurn = (currentPlayerTurn == 0) ? 1 : 0;
                    board->inCheck(currentPlayerTurn);

                    // Check for end conditions
                    if (board->inCheckmate(currentPlayerTurn)) {
                        scoreboard.endGame(currentPlayerTurn == 0 ? "black" : "white");
                        gameRunning = false;
                    }
                    if (board->inStalemate(currentPlayerTurn)) {
                        scoreboard.endGame();
                        gameRunning = false;
                    }

                } else {
                    cout << "Move is not valid for this piece" << endl;
                    continue;
                }
                cout << "Moved" << endl;
            }
        } else if (cmd == "setup") {
            if (gameRunning) {
                cout << "Cannot enter setup mode while a game is running." << endl;
                continue;
            }
            delete board;
            board = new Board();
            delete td;
            td = new TextDisplay();
            delete gd;
            gd = new GraphDisplay();
            string setupCmd;
            bool whiteKingExist = false;
            bool blackKingExist = false;
            cout << "enter setup mode" << endl;
            cout << *td;
            gd->initBoard();
            gd->show();
            while (getline(cin, setupCmd)) {
                istringstream setupIss(setupCmd);
                string setup;
                setupIss >> setup;

                if (setup == "+") {
                    char piece;
                    string position;
                    setupIss >> piece >> position;
                    int row = position[1] - '1';
                    int col = position[0] - 'a';
                    // check out of bound
                    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
                      cout << "the setup position is out of bound" << endl;
                      continue;
                    }

                    // check valid piece
                    if (validPieces.find(piece) == string::npos) {
                      cout << "the piece is invalid" << endl;
                      continue;
                    }

                    // check if the position already exists a piece
                    if (board->getPiece(row, col)->getSymbol() != '-') {
                        cout << "This position has already been occupied" << endl;
                        continue;
                    }

                    // check pawn
                    if ((piece == 'p' || piece == 'P') && (row == 0 || row == 7)) {
                        cout << "Pawns cannot be placed on the first or last row." << endl;
                        continue;
                    }

                    // check king
                    if (piece == 'k' && !blackKingExist) {
                        blackKingExist = true;
                        board->createPiece('k', row, col);
                        board->pieces[row][col] = board->createPiece('k', row, col);
                        // notify display
                        td->notify(row, col, piece);
                        gd->notify(row, col, piece);
                        cout << *td;
                        gd->show();
                    } else if (piece == 'K' && !whiteKingExist) {
                        whiteKingExist = true;
                        board->pieces[row][col] = board->createPiece('K', row, col);
                        // notify display
                        td->notify(row, col, piece);
                        gd->notify(row, col, piece);
                        cout << *td;
                        gd->show();
                    } else if (piece != 'k' && piece != 'K') {
                        board->pieces[row][col] = board->createPiece(piece, row, col);
                        // notify display
                        td->notify(row, col, piece);
                        gd->notify(row, col, piece);
                        cout << *td;
                        gd->show();
                    } else {
                        cout << "Only one King is allowed per color." << endl;
                    }
                } else if (setup == "-") {
                    string position;
                    setupIss >> position;
                    int row = position[1] - '1';
                    int col = position[0] - 'a';
                    char piece = board->getPiece(row, col)->getSymbol();

                    if (piece == 'k') {
                        blackKingExist = false;
                    } else if (piece == 'K') {
                        whiteKingExist = false;
                    }
                    board->pieces[row][col] = board->createPiece('-', row, col);
                    td->notify(row, col, '-');
                    gd->notify(row, col, '-');
                    cout << *td;
                    gd->show();

                } else if (setup == "=") {
                    string color;
                    setupIss >> color;
                    if (color == "white") {
                        currentPlayerTurn = 0;
                    } else if (color == "black") {
                        currentPlayerTurn = 1;
                    }
                } else if (setup == "done") {
                    if (!whiteKingExist || !blackKingExist) {
                        cout << "You need exactly one white king and one black king to finish setup" << endl;
                        continue;
                    }
                    if (board->inCheck(1) || board->inCheck(0)) {
                        cout << "A King is in Check!" << endl;
                        continue;
                    }
                    customizedBoard = new Board(*board); // Save the customized board
                    cout << "Setup complete!" << endl;
                    defaultSetup = false;
                    break;
                } else {
                    cout << "Invalid setup command" << endl;
                }
            }
        } else {
            cout << "Invalid command." << endl;
        }
    }

    cout << "Final Score:" << endl;
    scoreboard.printResults();

    delete board;
    delete customizedBoard;
    delete td;
    delete gd;

    return 0;
}
