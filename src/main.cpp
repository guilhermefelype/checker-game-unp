#include "/opt/homebrew/include/GL/glut.h"
#include "../include/piece.h"
#include "../include/movement_handler.h"
#include "../include/capture_handler.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

// Variáveis globais
std::vector<Piece> pieces;
bool isWhiteTurn = true;

// Inicializa o estado do jogo e do tabuleiro
void initializeGame() {
    initializeBoard(pieces);
    std::cout << "Jogo inicializado!" << std::endl;
}

// Função que manipula o teclado para interações do jogador
void handleInput() {
    int selectedX, selectedZ, targetX, targetZ;
    std::cout << "Selecione a posição da peça (x z): ";
    std::cin >> selectedX >> selectedZ;

    Piece* piece = findPieceAt(selectedX, selectedZ, pieces);
    if (!piece) {
        std::cout << "Movimento inválido: Nenhuma peça encontrada na posição selecionada." << std::endl;
        return;
    }

    if (piece->isWhite != isWhiteTurn) {
        std::cout << "Movimento inválido: É o turno das " << (isWhiteTurn ? "brancas" : "pretas") << "." << std::endl;
        return;
    }

    std::cout << "Selecione a posição de destino (x z): ";
    std::cin >> targetX >> targetZ;

    if (isValidMove(*piece, targetX, targetZ, isWhiteTurn, pieces)) {
        if (isCapturePossible(*piece, targetX, targetZ, pieces)) {
            capturePiece(*piece, targetX, targetZ, pieces);
            std::cout << "Peça capturada!" << std::endl;
        }

        movePiece(*piece, targetX, targetZ, pieces, isWhiteTurn);
        std::cout << "Movimento realizado de (" << selectedX << ", " << selectedZ << ") para (" << targetX << ", " << targetZ << ")." << std::endl;
    } else {
        std::cout << "Movimento inválido!" << std::endl;
    }
}

// Funções principais do OpenGL
void display() {
    // Renderiza o tabuleiro e as peças
}

void reshape(int w, int h) {
    // Gerencia redimensionamento de janela
}

void initOpenGL() {
    // Configuração inicial do OpenGL
    initializeGame(); // Inicializa o tabuleiro e as peças
}

// Função principal do programa
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Jogo de Damas 3D");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc([](unsigned char key, int x, int y) {
        if (key == ' ') {
            handleInput();
        }
    });

    glutMainLoop();
    return 0;
}
