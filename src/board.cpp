#include "../include/board.h"
#include <iostream>

void Board::initialize() {
    pieces.clear();
    // Peças pretas (topo do tabuleiro)
    for (int z = 0; z < 3; z++) {
        for (int x = 0; x < 8; x++) {
            if ((x + z) % 2 == 1) {
                pieces.emplace_back(Position(x, z), false);
            }
        }
    }
    // Peças brancas (base do tabuleiro)
    for (int z = 5; z < 8; z++) {
        for (int x = 0; x < 8; x++) {
            if ((x + z) % 2 == 1) {
                pieces.emplace_back(Position(x, z), true);
            }
        }
    }

    printState();
}

void Board::printState() const {
    std::cout << "Estado inicial do tabuleiro:" << std::endl;
    for (const auto& piece : pieces) {
        std::cout << (piece.isWhite ? "Peça branca" : "Peça preta")
                  << " na posição (" << piece.pos.x << ", " << piece.pos.z << ")" << std::endl;
    }
}

Piece* Board::findPieceAt(int x, int z) {
    for (auto& piece : pieces) {
        if (piece.pos.x == x && piece.pos.z == z) {
            return &piece;
        }
    }
    return nullptr;
}
