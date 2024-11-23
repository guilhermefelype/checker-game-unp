#include "../include/capture_handler.h"

bool isCapturePossible(const Piece& piece, int targetX, int targetZ, const std::vector<Piece>& pieces) {
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;

    // Verifica se o movimento é de captura
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

void capturePiece(Piece& piece, int targetX, int targetZ, std::vector<Piece>& pieces) {
    int deltaX = targetX - piece.pos.x;
    int deltaZ = targetZ - piece.pos.z;

    if (std::abs(deltaX) == 2 && std::abs(deltaZ) == 2) {
        int midX = piece.pos.x + deltaX / 2;
        int midZ = piece.pos.z + deltaZ / 2;
        auto it = std::find_if(pieces.begin(), pieces.end(), [midX, midZ](const Piece& p) {
            return p.pos.x == midX && p.pos.z == midZ;
        });
        if (it != pieces.end()) {
            // Remove a peça capturada
            std::cout << "Peça capturada na posição (" << midX << ", " << midZ << ")" << std::endl;
            pieces.erase(it);
        }
    }
}