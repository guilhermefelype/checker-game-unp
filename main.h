#ifndef MAIN_H
#define MAIN_H

#include <vector>

struct Position {
    int x, z;
    Position(int _x, int _z) : x(_x), z(_z) {}
};

struct Piece {
    Position pos;
    bool isWhite;
    bool isKing;
    Piece(Position _pos, bool _isWhite) : pos(_pos), isWhite(_isWhite), isKing(false) {}
};

extern std::vector<Piece> pieces;
extern float boardRotation;
extern float zOffset;
extern bool isWhiteTurn;

void initializeBoard();
Piece* findPieceAt(int x, int z);

#endif