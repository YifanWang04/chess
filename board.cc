#include "board.h"
#include "player.h"
#include "textDisplay.h"
#include "graphDisplay.h"
#include <iostream>
 
// ctor
Board::Board() : boardSize(8), player1(nullptr), player2(nullptr), pieces(new Piece**[8]), enPassantTarget({-1, -1}) {
    // pieces = new Piece**[boardSize];
    for (int i = 0; i < 8; ++i) {
        pieces[i] = new Piece*[8];
        for (int j = 0; j < 8; ++j) {
            pieces[i][j] = new Empty(i, j, '-', -1);
        }
    }
    // boardSize = 8; 
    // player1 = nullptr; // Initialize players to nullptr or create Player objects if needed
    // player2 = nullptr;
    whiteKing = nullptr;
    blackKing = nullptr;
}

// dtor
Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete pieces[i][j];
        }
        delete[] pieces[i];
    }
    delete[] pieces;
    delete player1;
    delete player2;
    // delete text;
    whiteKing = nullptr;
    blackKing = nullptr;
}


// // copy ctor 
// Board::Board(const Board& other) : boardSize(other.boardSize), player1(nullptr), player2(nullptr), whiteKing(nullptr), blackKing(nullptr) {
//     pieces = new Piece**[boardSize];
//     for (int i = 0; i < boardSize; ++i) {
//         pieces[i] = new Piece*[boardSize];
//         for (int j = 0; j < boardSize; ++j) {
//             if (other.pieces[i][j]) {
//                 pieces[i][j] = other.pieces[i][j]->clone();
//                 if (pieces[i][j]->getSymbol() == 'K') whiteKing = dynamic_cast<King*>(pieces[i][j]);
//                 if (pieces[i][j]->getSymbol() == 'k') blackKing = dynamic_cast<King*>(pieces[i][j]);
//             } else {
//                 pieces[i][j] = nullptr;
//             }
//         }
//     }
// }

Board::Board(const Board& other) : boardSize(other.boardSize), player1(nullptr), player2(nullptr), whiteKing(nullptr), blackKing(nullptr) {
    pieces = new Piece**[boardSize];
    for (int i = 0; i < boardSize; ++i) {
        pieces[i] = new Piece*[boardSize];
        for (int j = 0; j < boardSize; ++j) {
            if (other.pieces[i][j]) {
                pieces[i][j] = other.pieces[i][j]->clone();
                if (pieces[i][j]->getSymbol() == 'K') {
                    whiteKing = dynamic_cast<King*>(pieces[i][j]);
                    if (!whiteKing) {
                        std::cerr << "Error: Invalid cast to whiteKing during copy" << std::endl;
                    }
                }
                if (pieces[i][j]->getSymbol() == 'k') {
                    blackKing = dynamic_cast<King*>(pieces[i][j]);
                    if (!blackKing) {
                        std::cerr << "Error: Invalid cast to blackKing during copy" << std::endl;
                    }
                }
            } else {
                pieces[i][j] = nullptr;
            }
        }
    }
}



void Board::setupBoard(TextDisplay* td) {
    for (int i = 0; i < 8; ++i) {
        pieces[1][i] = new Pawn(1, i, 'P', 0); // White pawns
        pieces[6][i] = new Pawn(6, i, 'p', 1); // Black pawns
        td->notify(1, i, 'P');
        td->notify(6, i, 'p');
    }

    pieces[0][0] = new Rook(0, 0, 'R', 0);
    pieces[0][7] = new Rook(0, 7, 'R', 0);
    pieces[7][0] = new Rook(7, 0, 'r', 1);
    pieces[7][7] = new Rook(7, 7, 'r', 1);
    td->notify(0, 0, 'R');
    td->notify(0, 7, 'R');
    td->notify(7, 0, 'r');
    td->notify(7, 7, 'r');

    pieces[0][3] = new Queen(0, 3, 'Q', 0);
    pieces[7][3] = new Queen(7, 3, 'q', 1);
    td->notify(0, 3, 'Q');
    td->notify(7, 3, 'q');

    pieces[0][1] = new Knight(0, 1, 'N', 0);
    pieces[0][6] = new Knight(0, 6, 'N', 0);
    td->notify(0, 1, 'N');
    td->notify(0, 6, 'N');

    pieces[7][1] = new Knight(7, 1, 'n', 1);
    pieces[7][6] = new Knight(7, 6, 'n', 1);
    td->notify(7, 1, 'n');
    td->notify(7, 6, 'n');

    pieces[0][2] = new Bishop(0, 2, 'B', 0);
    pieces[0][5] = new Bishop(0, 5, 'B', 0);
    pieces[7][2] = new Bishop(7, 2, 'b', 1);
    pieces[7][5] = new Bishop(7, 5, 'b', 1);
    td->notify(0, 2, 'B');
    td->notify(0, 5, 'B');
    td->notify(7, 2, 'b');
    td->notify(7, 5, 'b');

    td->notify(0, 4, 'K');
    td->notify(7, 4, 'k');

    pieces[0][4] = new King(0, 4, 'K', 0);
    whiteKing = dynamic_cast<King*>(pieces[0][4]);

    pieces[7][4] = new King(7, 4, 'k', 1);
    blackKing = dynamic_cast<King*>(pieces[7][4]);

    // blackKing = new King(7, 4, 'k', 1);
    // pieces[7][4] = blackKing;

}

void Board::setupBoard(GraphDisplay* gd) {
    for (int i = 0; i < 8; ++i) {
        pieces[1][i] = new Pawn(1, i, 'P', 0); // White pawns
        pieces[6][i] = new Pawn(6, i, 'p', 1); // Black pawns
        gd->notify(1, i, 'P');
        gd->notify(6, i, 'p');
    }

    pieces[0][0] = new Rook(0, 0, 'R', 0);
    pieces[0][7] = new Rook(0, 7, 'R', 0);
    pieces[7][0] = new Rook(7, 0, 'r', 1);
    pieces[7][7] = new Rook(7, 7, 'r', 1);
    gd->notify(0, 0, 'R');
    gd->notify(0, 7, 'R');
    gd->notify(7, 0, 'r');
    gd->notify(7, 7, 'r');

    pieces[0][3] = new Queen(0, 3, 'Q', 0);
    pieces[7][3] = new Queen(7, 3, 'q', 1);
    gd->notify(0, 3, 'Q');
    gd->notify(7, 3, 'q');

    pieces[0][1] = new Knight(0, 1, 'N', 0);
    pieces[0][6] = new Knight(0, 6, 'N', 0);
    gd->notify(0, 1, 'N');
    gd->notify(0, 6, 'N');

    pieces[7][1] = new Knight(7, 1, 'n', 1);
    pieces[7][6] = new Knight(7, 6, 'n', 1);
    gd->notify(7, 1, 'n');
    gd->notify(7, 6, 'n');

    pieces[0][2] = new Bishop(0, 2, 'B', 0);
    pieces[0][5] = new Bishop(0, 5, 'B', 0);
    pieces[7][2] = new Bishop(7, 2, 'b', 1);
    pieces[7][5] = new Bishop(7, 5, 'b', 1);
    gd->notify(0, 2, 'B');
    gd->notify(0, 5, 'B');
    gd->notify(7, 2, 'b');
    gd->notify(7, 5, 'b');

    gd->notify(0, 4, 'K');
    gd->notify(7, 4, 'k');

    pieces[0][4] = new King(0, 4, 'K', 0);
    whiteKing = dynamic_cast<King*>(pieces[0][4]);

    pieces[7][4] = new King(7, 4, 'k', 1);
    blackKing = dynamic_cast<King*>(pieces[7][4]);
}


Piece* Board::createPiece(char symbol, int row, int col) {
    Piece* newPiece = nullptr;
    if (symbol == 'p') {
        newPiece = new Pawn(row, col, 'p', 1);
    } else if (symbol == 'P') {
        newPiece = new Pawn(row, col, 'P', 0);
    } else if (symbol == 'r') {
        newPiece = new Rook(row, col, 'r', 1);
    } else if (symbol == 'R') {
        newPiece = new Rook(row, col, 'R', 0);
    } else if (symbol == 'n') {
        newPiece = new Knight(row, col, 'n', 1);
    } else if (symbol == 'N') {
        newPiece = new Knight(row, col, 'N', 0);
    } else if (symbol == 'b') {
        newPiece = new Bishop(row, col, 'b', 1);
    } else if (symbol == 'B') {
        newPiece = new Bishop(row, col, 'B', 0);
    } else if (symbol == 'q') {
        newPiece = new Queen(row, col, 'q', 1);
    } else if (symbol == 'Q') {
        newPiece = new Queen(row, col, 'Q', 0);
    } else if (symbol == 'k') {
        newPiece = new King(row, col, 'k', 1);
        blackKing = dynamic_cast<King*>(newPiece);
    } else if (symbol == 'K') {
        newPiece = new King(row, col, 'K', 0);
        whiteKing = dynamic_cast<King*>(newPiece);
    } else if (symbol == '-') {
        newPiece = new Empty(row, col, '-', -1);
    }
    return newPiece;
}


// void Board::makeMove(int row, int col, int newRow, int newCol) {
//     Piece* piece = getPiece(row, col);


//     // check castling 
//     if ((piece->getSymbol() == 'K' || piece->getSymbol() == 'k') && abs(newCol - col) == 2) {
//         bool isKingSide = (newCol == col + 2);
//         int rookCol = isKingSide ? 7 : 0;
//         int newRookCol = isKingSide ? newCol - 1 : newCol + 1;

//         Piece* rook = getPiece(row, rookCol);
//         pieces[row][newRookCol] = rook;
//         pieces[row][rookCol] = new Empty(row, rookCol, '-', -1);
//         rook->setCol(newRookCol);

//         pieces[newRow][newCol] = piece;
//         pieces[row][col] = new Empty(row, col, '-', -1);
//         piece->setRow(newRow);
//         piece->setCol(newCol);

//         King* k = dynamic_cast<King*>(piece);
//         Rook* r = dynamic_cast<Rook*>(rook);
//         if (k) k->setHasMoved(true);
//         if (r) r->setHasMoved(true);

//         return;
//     }

//     // check en passant
//     if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && col != newCol && getPiece(newRow, newCol)->getSymbol() == '-') {
//         captureEnPassant(row, col, newRow, newCol);
//         resetEnPassantTarget();
//         return;
//     }

//     // make move
//     Piece* newPiece = createPiece(piece->getSymbol(), newRow, newCol);
//     if (pieces[newRow][newCol] != nullptr) {
//         delete pieces[newRow][newCol];
//     }
//     pieces[newRow][newCol] = newPiece;

//     Piece *newEmpty = createPiece('-', row, col);
//     if (pieces[row][col] != nullptr) {
//         delete pieces[row][col];
//     }
//     pieces[row][col] = newEmpty;

//     // set en passant target
//     if (Pawn* pawn = dynamic_cast<Pawn*>(newPiece)) {
//         if (abs(newRow - row) == 2) {
//             enPassantTarget = std::make_pair((row + newRow) / 2, col);
//         } else {
//             resetEnPassantTarget();
//         }
//         pawn->setIsFirstMove(false);
//     } else {
//         resetEnPassantTarget();
//     }

//     // set castling/en passant status
//     if (Rook* rook = dynamic_cast<Rook*>(newPiece)) {
//         rook->setHasMoved(true);
//     } else if (King* king = dynamic_cast<King*>(newPiece)) {
//         king->setHasMoved(true);
//     }
// }

void Board::makeMove(int row, int col, int newRow, int newCol) {
    Piece* piece = getPiece(row, col);

    // check castling 
    if ((piece->getSymbol() == 'K' || piece->getSymbol() == 'k') && abs(newCol - col) == 2) {
        std::cout << "Castling detected" << std::endl;
        bool isKingSide = (newCol == col + 2);
        int rookCol = isKingSide ? 7 : 0;
        int newRookCol = isKingSide ? newCol - 1 : newCol + 1;

        Piece* rook = getPiece(row, rookCol);
        pieces[row][newRookCol] = rook;
        pieces[row][rookCol] = new Empty(row, rookCol, '-', -1);
        rook->setCol(newRookCol);

        // Update GraphDisplay for rook
        gd->notify(row, newRookCol, rook->getSymbol());
        gd->notify(row, rookCol, '-');

        pieces[newRow][newCol] = piece;
        pieces[row][col] = new Empty(row, col, '-', -1);
        piece->setRow(newRow);
        piece->setCol(newCol);

        // Update GraphDisplay for king
        gd->notify(newRow, newCol, piece->getSymbol());
        gd->notify(row, col, '-');

        King* k = dynamic_cast<King*>(piece);
        if (k) {
            k->setHasMoved(true);
        } else {
            std::cerr << "Error: Castling piece is not a King" << std::endl;
        }

        Rook* r = dynamic_cast<Rook*>(rook);
        if (r) {
            r->setHasMoved(true);
        } else {
            std::cerr << "Error: Castling rook is not a Rook" << std::endl;
        }

        return;
    }

    // check en passant
    if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && col != newCol && getPiece(newRow, newCol)->getSymbol() == '-') {
        std::cout << "En passant detected" << std::endl;
        captureEnPassant(row, col, newRow, newCol);
        resetEnPassantTarget();
        return;
    }

    // make move
    Piece* newPiece = createPiece(piece->getSymbol(), newRow, newCol);
    if (pieces[newRow][newCol] != nullptr) {
        delete pieces[newRow][newCol];
    }
    pieces[newRow][newCol] = newPiece;

    Piece *newEmpty = createPiece('-', row, col);
    if (pieces[row][col] != nullptr) {
        delete pieces[row][col];
    }
    pieces[row][col] = newEmpty;

    // set en passant target
    if (Pawn* pawn = dynamic_cast<Pawn*>(newPiece)) {
        if (abs(newRow - row) == 2) {
            enPassantTarget = std::make_pair((row + newRow) / 2, col);
        } else {
            resetEnPassantTarget();
        }
        pawn->setIsFirstMove(false);
    } else {
        resetEnPassantTarget();
    }

    // set castling/en passant status
    if (Rook* rook = dynamic_cast<Rook*>(newPiece)) {
        rook->setHasMoved(true);
    } else if (King* king = dynamic_cast<King*>(newPiece)) {
        king->setHasMoved(true);
    }

    std::cout << "Move completed" << std::endl;

    // Update GraphDisplay
    gd->notify(newRow, newCol, newPiece->getSymbol());
    gd->notify(row, col, '-');
}






bool Board::isMoveable(int row, int col, int newRow, int newCol, Board* board) const {
    Piece *currentPiece = board->getPiece(row, col);
    Piece *targetPiece = board->getPiece(newRow,newCol);
    
    // check en passant
    if ((currentPiece->getSymbol() == 'P' || currentPiece->getSymbol() == 'p') &&
        col != newCol && targetPiece->getSymbol() == '-') {
        if (board->canCaptureEnPassant(row, col, newRow, newCol)) {
            return true;
        }
    }

    // Check if moving to a position occupied by a friendly piece
    if (targetPiece->getColor() == currentPiece->getColor()) {
        cout << "The target position is occupied by a friendly piece" << endl;
        return false;
    }

    // Check the piece type and validate the move
    bool canMove = currentPiece->canMove(newRow, newCol, *board);
    return canMove;
}


bool Board::inCheck(int color) {
    Piece* king = (color == 0) ? whiteKing : blackKing;
    if (king->isInDanger(*this)) {
        cout << (color == 0 ? "White" : "Black") << " is in check." << endl;
        return true;
    }
    return false;
}


bool Board::inStalemate(bool color) {
    if (inCheck(color)) return false;

    // Loop through each cell on the board
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            Piece* piece = this->getPiece(row, col);
            if (piece->getSymbol() != '-' && piece->getColor() == color) {
                for (int newRow = 0; newRow < boardSize; ++newRow) {
                    for (int newCol = 0; newCol < boardSize; ++newCol) {
                        //if (piece->canMove(newRow, newCol, *this) && !willSelfBeInCheck(row, col, newRow, newCol)) {
                        if (this->isMoveable(row, col, newRow, newCol, this)  && !willSelfBeInCheck(row, col, newRow, newCol)) {
                            // cout << piece->getSymbol() << endl;
                            // cout << newRow << endl;
                            // cout << newCol << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    cout << "Stalemate! It's a draw!" << endl;
    return true;
}


bool Board::inCheckmate(bool color) {
    if (!inCheck(color))  return false;

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            Piece* piece = this->getPiece(row, col);
            if (piece->getSymbol() != '-' && piece->getColor() == color) {
                for (int newRow = 0; newRow < boardSize; ++newRow) {
                    for (int newCol = 0; newCol < boardSize; ++newCol) {
                        if (this->isMoveable(row, col, newRow, newCol, this) && !willSelfBeInCheck(row, col, newRow, newCol)) {
                            return false; 
                        }
                    }
                }
            }
        }
    }

    
    string winner = (color) ? "White" : "Black";
    cout << "Checkmate! " << winner << " wins!" << endl;
    return true;
}


bool Board::willCheckOpponent(int fromRow, int fromCol, int toRow, int toCol) {
    // Get the color of the current piece
    int pieceColor = this->getPiece(fromRow, fromCol)->getColor();

    // Simulate the move
    Board testBoard = *this; // Copy the current board
    testBoard.makeMove(fromRow, fromCol, toRow, toCol);

    // Check if the opponent's king is in check
    int opponentColor = 1 - pieceColor; // If pieceColor is 0 (white), opponentColor is 1 (black), and vice versa
    
    return testBoard.inCheck(opponentColor);
}

bool Board::willSelfBeInCheck(int fromRow, int fromCol, int toRow, int toCol) {
    Board testBoard(*this);
    testBoard.makeMove(fromRow, fromCol, toRow, toCol);
    int pieceColor = this->getPiece(fromRow, fromCol)->getColor();
    bool result = testBoard.inCheck(pieceColor);
    return result;
}

int Board::getBoardSize() const {
    return boardSize;
}

Piece* Board::getPiece(int row, int col) const {
    return pieces[row][col];
}


// Special Rules

// promotion
bool Board::checkPromotion(int fromRow, int fromCol, int toRow, int toCol, char newPiece) {
    char currentPiece = pieces[fromRow][fromCol]->getSymbol();
    int color = pieces[fromRow][fromCol]->getColor();  //white is 0, black is 1
    string validPromotion = "QRNBqrnb";

    // check position
    if ((currentPiece == 'P' && toRow == 7) || (currentPiece == 'p' && toRow == 0)) {
        
        // check promotion is to a valid piece type
        if (validPromotion.find(newPiece) == string::npos) {
            cout << "Invalid promotion piece type." << endl;
            return false;
        }
        
        // check promotion is same color
        if ((isupper(newPiece) && color == 0) || (islower(newPiece) && color == 1)) {
            return true;
        } else {
            cout << "Invalid promotion color." << endl;
            return false;
        }
    } else {
        cout << "Invalid promotion position." << endl;
        return false;
    }
}

void Board::promotion(int row, int col, char newPiece) {
    delete pieces[row][col];
    pieces[row][col] = createPiece(newPiece, row, col);
    std::cout << "Pawn promoted to " << newPiece << "!" << std::endl;
}


// // castling
// bool Board::canCastle(int row, int col, int newRow, int newCol) {
//     Piece* king = this->getPiece(row, col);
//     if (king->getSymbol() != 'K' && king->getSymbol() != 'k') return false;

//     King* k = dynamic_cast<King*>(king);
//     if (k == nullptr || k->getHasMoved()) return false;

//     bool isKingSide = (newCol == col + 2);
//     bool isQueenSide = (newCol == col - 2);

//     if (!isKingSide && !isQueenSide) return false;

//     int rookCol = isKingSide ? 7 : 0;
//     Piece* rook = this->getPiece(row, rookCol);

//     Rook* r = dynamic_cast<Rook*>(rook);
//     if (r == nullptr || r->getHasMoved()) return false;

//     int direction = isKingSide ? 1 : -1;
//     for (int i = col + direction; i != rookCol; i += direction) {
//         if (this->getPiece(row, i)->getSymbol() != '-') {
//             return false;
//         }
//     }

//     for (int i = col; i != newCol + direction; i += direction) {
//         if (willSelfBeInCheck(row, col, row, i)) {
//             return false;
//         }
//     }

//     return true;
// }

bool Board::canCastle(int row, int col, int newRow, int newCol) {
    Piece* king = this->getPiece(row, col);
    if (king->getSymbol() != 'K' && king->getSymbol() != 'k') return false;

    King* k = dynamic_cast<King*>(king);
    if (k == nullptr || k->getHasMoved()) return false;

    bool isKingSide = (newCol == col + 2);
    bool isQueenSide = (newCol == col - 2);

    if (!isKingSide && !isQueenSide) return false;

    int rookCol = isKingSide ? 7 : 0;
    Piece* rook = this->getPiece(row, rookCol);

    Rook* r = dynamic_cast<Rook*>(rook);
    if (r == nullptr || r->getHasMoved()) return false;

    int direction = isKingSide ? 1 : -1;
    for (int i = col + direction; i != newCol + direction; i += direction) {
        if (i != col && this->getPiece(row, i)->getSymbol() != '-') {
            return false;
        }
        if (willSelfBeInCheck(row, col, row, i)) {
            return false;
        }
    }

    return true;
}




// en passent
bool Board::canCaptureEnPassant(int row, int col, int newRow, int newCol) {
    Piece* piece = getPiece(row, col);
    if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && enPassantTarget == std::make_pair(newRow, newCol)) {
        return true;
    }
    return false;
}

std::pair<int, int> Board::getEnPassantTarget() const {
    return enPassantTarget;
}

void Board::resetEnPassantTarget() {
    enPassantTarget = { -1, -1 };
}

void Board::captureEnPassant(int row, int col, int newRow, int newCol) {
    Piece* piece = getPiece(row, col);
    int captureRow = (piece->getSymbol() == 'P') ? newRow - 1 : newRow + 1;

    // captured pawn 
    delete pieces[captureRow][newCol];
    pieces[captureRow][newCol] = new Empty(captureRow, newCol, '-', -1);

    // moving pawn
    pieces[newRow][newCol] = piece;
    pieces[row][col] = new Empty(row, col, '-', -1);
    piece->setRow(newRow);
    piece->setCol(newCol);
}
