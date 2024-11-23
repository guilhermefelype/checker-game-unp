#ifndef RENDERER_H
#define RENDERER_H

#include "board.h"

class Renderer {
public:
    void drawBoard(const Board& board);
    void drawPiece(const Piece& piece);
    void initOpenGL();
};

#endif // RENDERER_H
