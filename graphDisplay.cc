#include "graphDisplay.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>

GraphDisplay::GraphDisplay(int width, int height) : width(width), height(height) {
    d = XOpenDisplay(NULL);
    if (d == nullptr) {
        throw std::runtime_error("Cannot open display");
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);
    XFlush(d);

    gc = XCreateGC(d, w, 0, nullptr);
    cmap = DefaultColormap(d, s);
}

GraphDisplay::~GraphDisplay() {
    for (auto &pair : piecePixmaps) {
        XFreePixmap(d, pair.second);
    }
    for (auto &pair : pieceMasks) {
        XFreePixmap(d, pair.second);
    }
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void GraphDisplay::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Dark]);
    XFlush(d);
}

void GraphDisplay::drawString(int x, int y, std::string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFontStruct *font = XLoadQueryFont(d, "-*-helvetica-*-r-bold--48-*-*-*-*-*-*-*");
    if (!font) {
        font = XLoadQueryFont(d, "fixed");
    }
    if (font) {
        XSetFont(d, gc, font->fid);
        XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
        XFreeFont(d, font);
    }
    XSetForeground(d, gc, colours[Dark]);
    XFlush(d);
}

void GraphDisplay::notify(int row, int col, char piece) {
    int x = col * (width / 8);
    int y = row * (height / 8);
    XSetClipMask(d, gc, pieceMasks[piece]);
    XSetClipOrigin(d, gc, x, y);
    XCopyArea(d, piecePixmaps[piece], w, gc, 0, 0, width / 8, height / 8, x, y);
    XSetClipMask(d, gc, None);
    XFlush(d); // Ensure the drawing operations are flushed and displayed
}

void GraphDisplay::clear() {
    XClearWindow(d, w);
    XFlush(d);
}

void GraphDisplay::show() {
    XFlush(d);
}

void GraphDisplay::showAvailableFonts() {
    int count;
    char **fnts = XListFonts(d, "*", 10000, &count);
    for (int i = 0; i < count; ++i) {
        std::cout << fnts[i] << std::endl;
    }
    XFreeFontNames(fnts);
}

void GraphDisplay::loadPieceImage(char piece) {
    std::string filepath = "images/";
    filepath += piece;
    filepath += ".xpm";
    Pixmap pixmap;
    Pixmap mask;
    XpmAttributes attributes;
    int status = XpmReadFileToPixmap(d, w, filepath.c_str(), &pixmap, &mask, &attributes);
    if (status != XpmSuccess) {
        std::cerr << "Error loading XPM file: " << filepath << std::endl;
        return;
    }
    piecePixmaps[piece] = pixmap;
    pieceMasks[piece] = mask;
}
