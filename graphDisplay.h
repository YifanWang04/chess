#ifndef GRAPH_DISPLAY_H
#define GRAPH_DISPLAY_H
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <iostream>
#include <string>
#include <map>

class GraphDisplay {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[2];
  int width, height;
  std::map<char, Pixmap> piecePixmaps; // Map to store piece images
  std::map<char, Pixmap> pieceMasks;   // Map to store piece masks

 public:
  GraphDisplay(int width=800, int height=800);  // Constructor; displays the window.
  ~GraphDisplay();                              // Destructor; destroys the window.

  enum {Light=0, Dark}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Dark);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Dark);

  // Initializes the chessboard
  void initBoard();

  // Updates the board with a piece
  void notify(int row, int col, char piece);

  // Clears the window
  void clear();

  // Shows the updates
  void show();

  // Prints the first 10000 available fonts
  void showAvailableFonts();

 private:
  // Loads a piece image
  void loadPieceImage(char piece);
};

#endif
