#include "../include/input_handler.h"
#include <iostream>
#include <GL/glut.h>

void handleKeyboardInput(unsigned char key, Board& board, bool& isWhiteTurn) {
    if (key == ' ') {
        int selectedX, selectedZ, targetX, targetZ;
        std::cout << "Selecione a posição da peça (x z): ";
        std::cin >> selectedX >> selectedZ;

        Piece* piece = board.findPieceAt(selectedX, selectedZ);
        if (piece == nullptr) {
            std::cout << "Movimento inválido: Nenhuma peça encontrada na posição (" << selectedX << ", " << selectedZ << ")." << std::endl;
            return;
        }

        std::cout << "Selecione a posição de destino (x z): ";
        std::cin >> targetX >> targetZ;

        if (!isValidMove(*piece, targetX, targetZ, isWhiteTurn, board.pieces)) {
            std::cout << "Movimento inválido." << std::endl;
            return;
        }

        if (isCapturePossible(*piece, targetX, targetZ, board.pieces)) {
            capturePiece(*piece, targetX, targetZ, board.pieces);
        }

        movePiece(*piece, targetX, targetZ, board.pieces, isWhiteTurn);
        glutPostRedisplay();
    }
}
