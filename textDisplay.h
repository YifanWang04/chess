#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>

class TextDisplay {
private:
    char** display;
    static const int size = 8; // Assuming an 8x8 chessboard

public:
    TextDisplay();
    ~TextDisplay();

    void notify(int row, int col, char symbol);
    friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};

#endif // TEXTDISPLAY_H
