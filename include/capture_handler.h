#ifndef CAPTURE_HANDLER_H
#define CAPTURE_HANDLER_H

#include "piece.h" // Substitui o main.h
#include <vector>
#include <algorithm>
#include <iostream>

bool isCapturePossible(const Piece& piece, int targetX, int targetZ, const std::vector<Piece>& pieces);
void capturePiece(Piece& piece, int targetX, int targetZ, std::vector<Piece>& pieces);

#endif // CAPTURE_HANDLER_H