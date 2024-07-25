#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <X11/Xlib.h>
#include <string>

class GraphDisplay {
    Display* display;
    Window window;
    int screen;
    GC gc;
    int width;
    int height;
    int cellSize;
    const std::string whitePieces = "PRNBQK";
    const std::string blackPieces = "prnbqk";

public:
    GraphDisplay();
    ~GraphDisplay();
    void initBoard();
    void notify(int row, int col, char piece);
    void clear();
    void show();
};

#endif
