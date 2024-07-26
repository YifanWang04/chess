#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "graphDisplay.h"

using namespace std;

GraphDisplay::GraphDisplay(int width, int height): width(width), height(height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 11, 11, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[2][8]={"#EBECD0", "#739552"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 2; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Dark]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

GraphDisplay::~GraphDisplay() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void GraphDisplay::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Dark]);
}

void GraphDisplay::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFontStruct* font = XLoadQueryFont(d, "-*-helvetica-*-r-bold--48-*-*-*-*-*-*-*");
  if (!font) {
      font = XLoadQueryFont(d, "fixed");
  }
  if (!font) {
      std::cerr << "Unable to load any font\n";
      return;
  }
  XSetFont(d, gc, font->fid);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
  XFreeFont(d, font);
  XSetForeground(d, gc, colours[Dark]);
  XFlush(d);
}

void GraphDisplay::initBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int x = col * (width / 8);
            int y = row * (height / 8);
            if ((row + col) % 2 == 0) {
                fillRectangle(x, y, width / 8, height / 8, Light);  // Light color
            } else {
                fillRectangle(x, y, width / 8, height / 8, Dark);  // Dark color
            }
        }
    }
}

void GraphDisplay::notify(int row, int col, char piece) {
    int x = col * (width / 8);
    int y = (7 - row) * (height / 8);  // Adjusted for white pieces at the bottom

    // Redraw the background color of the square
    if ((row + col) % 2 == 0) {
        fillRectangle(x, y, width / 8, height / 8, Light);  // Light color
    } else {
        fillRectangle(x, y, width / 8, height / 8, Dark);  // Dark color
    }

    // Draw the piece using text
    if (piece != '-') {
        string pieceStr(1, piece);
        drawString(x + width / 16, y + height / 16 + 30, pieceStr);  // Center the text within the square
    }

    XFlush(d); // Ensure the drawing operations are flushed and displayed
}

void GraphDisplay::clear() {
    XClearWindow(d, w);
}

void GraphDisplay::show() {
    XFlush(d);
}

void GraphDisplay::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}