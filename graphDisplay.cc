#include "graphDisplay.h"
#include <iostream>

unsigned long GraphDisplay::getColorPixel(const char* color) {
    Colormap colormap = DefaultColormap(display, screen);
    XColor xcolor;
    if (XParseColor(display, colormap, color, &xcolor) && XAllocColor(display, colormap, &xcolor)) {
        return xcolor.pixel;
    } else {
        std::cerr << "Error: Unable to allocate color " << color << std::endl;
        exit(1);
    }
}

GraphDisplay::GraphDisplay(int width, int height) : width(width), height(height) {
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open X display" << std::endl;
        exit(1);
    }
    screen = DefaultScreen(display);
    
    darkPixel = getColorPixel("#739552");
    lightPixel = getColorPixel("#EBECD0");

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, darkPixel, lightPixel);
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, gc, darkPixel);
    XSetBackground(display, gc, lightPixel);

    // ÉèÖÃ×ÖÌå
    XFontStruct *font = XLoadQueryFont(display, "fixed");
    if (!font) {
        std::cerr << "Unable to load font 'fixed'" << std::endl;
        exit(1);
    }
    XSetFont(display, gc, font->fid);
}

GraphDisplay::~GraphDisplay() {
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void GraphDisplay::drawSquare(int row, int col, unsigned long color) {
    int squareWidth = width / 8;
    int squareHeight = height / 8;
    int x = col * squareWidth;
    int y = row * squareHeight;

    XSetForeground(display, gc, color);
    XFillRectangle(display, window, gc, x, y, squareWidth, squareHeight);
    XSetForeground(display, gc, darkPixel);
    XDrawRectangle(display, window, gc, x, y, squareWidth, squareHeight);
}

void GraphDisplay::drawPiece(int row, int col, char piece) {
    int squareWidth = width / 8;
    int squareHeight = height / 8;
    int x = col * squareWidth + squareWidth / 4;
    int y = row * squareHeight + squareHeight / 4;

    std::string text(1, piece);
    XDrawString(display, window, gc, x, y, text.c_str(), text.length());
}

void GraphDisplay::notify(int row, int col, char piece) {
    unsigned long color = (row + col) % 2 == 0 ? lightPixel : darkPixel;
    drawSquare(row, col, color);
    if (piece != '-') {
        drawPiece(row, col, piece);
    }
}

void GraphDisplay::clear() {
    XClearWindow(display, window);
}

void GraphDisplay::show() {
    XEvent e;
    while (true) {
        XNextEvent(display, &e);
        if (e.type == Expose) {
            // Redraw the board
        } else if (e.type == KeyPress) {
            break;
        }
    }
}
