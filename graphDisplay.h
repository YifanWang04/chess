#ifndef GRAPH_DISPLAY_H
#define GRAPH_DISPLAY_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>

class GraphDisplay {
    Display* display;
    Window window;
    GC gc;
    int screen;
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

#endif // GRAPH_DISPLAY_H
