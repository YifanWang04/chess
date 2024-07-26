#include <memory>
#include "textDisplay.h"
#include <iostream>

TextDisplay::TextDisplay() {
    display = new char*[size];
    for (int i = 0; i < size; ++i) {
        display[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            display[i][j] = '-'; // Initialize all squares with '-'
        }
    }
}

TextDisplay::~TextDisplay() {
    for (int i = 0; i < size; ++i) {
        delete[] display[i];
    }
    delete[] display;
}

void TextDisplay::notify(int row, int col, char symbol) {
    // cout << "notify" << endl;
    int displayRow = size - row - 1;
    display[displayRow][col] = symbol;
    // display[row][col] = symbol;
}


std::ostream& operator<<(std::ostream& out, const TextDisplay& td) {
    for (int i = 0; i < td.size; ++i) {
        out << td.size - i << " ";
        for (int j = 0; j < td.size; ++j) {
            out << td.display[i][j] << " ";
        }
        out << std::endl;
    }
    out << "  a b c d e f g h" << std::endl;
    return out;
}
