#ifndef PIECE_H
#define PIECE_H

struct Position {
    int x, z;
    Position(int _x, int _z) : x(_x), z(_z) {}
};

struct Piece {
    Position pos;
    bool isWhite;
    bool isKing;

    Piece(Position _pos, bool _isWhite)
        : pos(_pos), isWhite(_isWhite), isKing(false) {}
};

#endif // PIECE_H
