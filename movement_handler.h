#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "main.h"
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>

bool isValidMove(const Piece& piece, int targetX, int targetZ, bool isWhiteTurn, const std::vector<Piece>& pieces);
void movePiece(Piece& piece, int targetX, int targetZ, std::vector<Piece>& pieces, bool& isWhiteTurn);

#endif // MOVEMENT_HANDLER_H