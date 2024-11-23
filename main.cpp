#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "main.h"
#include "movement_handler.h"
#include "capture_handler.h"

// Variáveis globais
std::vector<Piece> pieces;
float boardRotation = 0.0f;
float zOffset = 0.5f;
bool isWhiteTurn = true;
int windowWidth = 800;
int windowHeight = 600;
float aspectRatio;

// Função para imprimir as posições das peças no tabuleiro
void printBoardState() {
    std::cout << "Estado inicial do tabuleiro:" << std::endl;
    for (const auto& piece : pieces) {
        std::cout << (piece.isWhite ? "Peça branca" : "Peça preta") << " na posição (" << piece.pos.x << ", " << piece.pos.z << ")" << std::endl;
    }
}

// Configuração inicial do tabuleiro
void initializeBoard() {
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

    // Imprimir o estado inicial do tabuleiro para debug
    printBoardState();
}

// Encontra uma peça na posição fornecida
Piece* findPieceAt(int x, int z) {
    for (auto& piece : pieces) {
        if (piece.pos.x == x && piece.pos.z == z) {
            return &piece;
        }
    }
    return nullptr;
}

// Função para processar o clique do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Converte as coordenadas 2D do clique para 3D
        float winX = (float)x;
        float winY = (float)(windowHeight - y); // O Y da janela é invertido

        // Mapeia as coordenadas do mouse para as coordenadas do tabuleiro
        int selectedX = (int)(winX / (windowWidth / 28));
        int selectedZ = (int)(winY / (windowHeight / 27));

        // Desloca as coordenadas para a esquerda e para baixo, aplicando um fator de 60%
        selectedX = (int)(selectedX * 0.7f);  // 60% para a esquerda
        selectedZ = (int)(selectedZ * 0.6f);  // 60% para baixo

        // Ajusta as coordenadas para o sistema de coordenadas do tabuleiro 3D (0, 0) no canto inferior esquerdo
        selectedX = selectedX - 4;  // Inverte a coordenada X
        selectedZ = selectedZ - 10;  // Inverte a coordenada Z

        std::cout << "Clicado em (" << selectedX << ", " << selectedZ << ")" << std::endl;

        // Verificar se existe uma peça nessa posição
        Piece* piece = findPieceAt(selectedX, selectedZ);
        if (piece == nullptr) {
            std::cout << "Movimento inválido: Nenhuma peça encontrada na posição (" << selectedX << ", " << selectedZ << ")." << std::endl;
            return;
        }

        if (piece->isWhite != isWhiteTurn) {
            std::cout << "Movimento inválido: É o turno das " << (isWhiteTurn ? "peças brancas" : "peças pretas") << "." << std::endl;
            return;
        }

        // Seleciona a posição de destino (exemplo simples)
        int targetX = selectedX + 1;
        int targetZ = selectedZ + 1;

        if (!isValidMove(*piece, targetX, targetZ, isWhiteTurn, pieces)) {
            std::cout << "Movimento inválido: Movimento não permitido de (" << selectedX << ", " << selectedZ << ") para (" << targetX << ", " << targetZ << ")." << std::endl;
            return;
        }

        if (isCapturePossible(*piece, targetX, targetZ, pieces)) {
            std::cout << "Captura possível! Capturando a peça adversária..." << std::endl;
            capturePiece(*piece, targetX, targetZ, pieces);
        }

        movePiece(*piece, targetX, targetZ, pieces, isWhiteTurn);
        std::cout << "Movimento realizado de (" << selectedX << ", " << selectedZ << ") para (" << targetX << ", " << targetZ << ")." << std::endl;

        glutPostRedisplay();
    }
}

// Desenha uma peça
void drawPiece(const Piece& piece) {
    glPushMatrix();
    glTranslatef(piece.pos.x - 3.5f + 0.5f, 0.2f, piece.pos.z - 3.5f + zOffset);

    if (piece.isWhite) {
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }

    GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.4f, 0.4f, 0.2f, 32, 32);

    glPushMatrix();
    gluDisk(quad, 0, 0.4f, 32, 1);
    glPopMatrix();

    glTranslatef(0.0f, 0.0f, 0.2f);
    gluDisk(quad, 0, 0.4f, 32, 1);

    gluDeleteQuadric(quad);

    glPopMatrix();
}

// Desenha o tabuleiro
void drawBoard() {
    for (int z = 0; z < 8; z++) {
        for (int x = 0; x < 8; x++) {
            glPushMatrix();
            glTranslatef(x - 3.5f, 0.0f, z - 3.5f);
            if ((x + z) % 2 == 0) {
                glColor3f(0.8f, 0.8f, 0.8f);
            } else {
                glColor3f(0.3f, 0.3f, 0.3f);
            }
            glBegin(GL_QUADS);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
            glEnd();
            glPopMatrix();
        }
    }
}

// Renderização
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 12.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(boardRotation, 0.0f, 1.0f, 0.0f);

    drawBoard();
    for (const auto& piece : pieces) {
        drawPiece(piece);
    }

    glutSwapBuffers();
}

// Função de redimensionamento
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (float)w / (float)h;
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tabuleiro de Xadrez 3D");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    initializeBoard();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
