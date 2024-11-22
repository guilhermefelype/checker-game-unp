#include "movement_handler.h"

bool isValidMove(const Piece& piece, int targetX, int targetZ, bool isWhiteTurn, const std::vector<Piece>& pieces) {
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;
    
    if (targetX < 0 || targetX >= 8 || targetZ < 0 || targetZ >= 8) {
        return false;
    }
    
    for (const auto& p : pieces) {
        if (p.pos.x == targetX && p.pos.z == targetZ) {
            return false;
        }
    }

    if (!piece.isKing) {
        if (piece.isWhite && deltaZ == -1 && std::abs(deltaX) == 1) {
            return true;
        } else if (!piece.isWhite && deltaZ == 1 && std::abs(deltaX) == 1) {
            return true;
        }
    } else {
        if (std::abs(deltaX) == std::abs(deltaZ)) {
            return true;
        }
    }

    if (std::abs(deltaX) == 2 && std::abs(deltaZ) == 2) {
        int midX = piece.pos.x + deltaX / 2;
        int midZ = piece.pos.z + deltaZ / 2;
        for (const auto& p : pieces) {
            if (p.pos.x == midX && p.pos.z == midZ && p.isWhite != piece.isWhite) {
                return true;
            }
        }
    }
    
    return false;
}

void movePiece(Piece& piece, int targetX, int targetZ, std::vector<Piece>& pieces, bool& isWhiteTurn) {
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;
    
    if (std::abs(deltaX) == 2 && std::abs(deltaZ) == 2) {
        int midX = piece.pos.x + deltaX / 2;
        int midZ = piece.pos.z + deltaZ / 2;
        auto it = std::find_if(pieces.begin(), pieces.end(), [midX, midZ](const Piece& p) {
            return p.pos.x == midX && p.pos.z == midZ;
        });
        if (it != pieces.end()) {
            pieces.erase(it);
        }
    }

    piece.pos.x = targetX;
    piece.pos.z = targetZ;

    if ((piece.isWhite && targetZ == 0) || (!piece.isWhite && targetZ == 7)) {
        piece.isKing = true;
    }

    isWhiteTurn = !isWhiteTurn;
}