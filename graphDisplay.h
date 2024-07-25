#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>

class GraphDisplay {
private:
    Display *display;
    Window window;
    int screen;
    GC gc;
    unsigned long blackPixel, whitePixel;
    int width, height;

    void drawSquare(int row, int col, unsigned long color);
    void drawPiece(int row, int col, char piece);

public:
    GraphDisplay(int width = 800, int height = 800);
    ~GraphDisplay();
    void notify(int row, int col, char piece);
    void clear();
    void show();
};

#endif // GRAPHDISPLAY_H
