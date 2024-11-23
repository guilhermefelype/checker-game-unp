#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"

class Board {
public:
    std::vector<Piece> pieces;

    void initialize();
    void printState() const;
    Piece* findPieceAt(int x, int z);
};

#endif // BOARD_H
