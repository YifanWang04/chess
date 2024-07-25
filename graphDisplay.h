#include "GraphDisplay.h"
#include <iostream>

GraphDisplay::GraphDisplay() {
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Cannot open display\n";
        exit(1);
    }
    screen = DefaultScreen(display);
    width = 800;
    height = 800;
    cellSize = width / 8;
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    gc = XCreateGC(display, window, 0, NULL);
}

GraphDisplay::~GraphDisplay() {
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void GraphDisplay::initBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int x = col * cellSize;
            int y = row * cellSize; // Reverse the row direction for the graphical display
            if ((row + col) % 2 == 0) {
                XSetForeground(display, gc, 0xEBECD0); // Light square color
            } else {
                XSetForeground(display, gc, 0x739552); // Dark square color
            }
            XFillRectangle(display, window, gc, x, y, cellSize, cellSize);
        }
    }
}

void GraphDisplay::notify(int row, int col, char piece) {
    int x = col * cellSize;
    int y = (7 - row) * cellSize; // Reverse the row direction for the graphical display

    XFontStruct* font = XLoadQueryFont(display, "fixed");
    if (!font) {
        std::cerr << "Unable to load font\n";
        exit(1);
    }
    XSetFont(display, gc, font->fid);

    // Draw the square first
    if ((row + col) % 2 == 0) {
        XSetForeground(display, gc, 0xEBECD0); // Light square color
    } else {
        XSetForeground(display, gc, 0x739552); // Dark square color
    }
    XFillRectangle(display, window, gc, x, y, cellSize, cellSize);

    // Set the piece color and draw the piece
    if (whitePieces.find(piece) != std::string::npos) {
        XSetForeground(display, gc, WhitePixel(display, screen));
    } else if (blackPieces.find(piece) != std::string::npos) {
        XSetForeground(display, gc, BlackPixel(display, screen));
    }

    std::string s(1, piece);
    XDrawString(display, window, gc, x + cellSize / 2 - 5, y + cellSize / 2 + 5, s.c_str(), s.length());
    XFreeFont(display, font);
}

void GraphDisplay::clear() {
    XClearWindow(display, window);
}

void GraphDisplay::show() {
    XFlush(display);
}
