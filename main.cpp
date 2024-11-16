#include <GL/glut.h>
#include <vector>
#include <cmath>

// Estruturas de dados
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

// Variáveis globais
std::vector<Piece> pieces;
float boardRotation = 0.0f; // Rotação do tabuleiro

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
}

// Desenha uma peça
void drawPiece(const Piece& piece) {
    glPushMatrix();
    glTranslatef(piece.pos.x - 3.5f, 0.2f, piece.pos.z - 3.5f);
    if (piece.isWhite) {
        glColor3f(1.0f, 1.0f, 1.0f); // Peça branca
    } else {
        glColor3f(0.2f, 0.2f, 0.2f); // Peça preta
    }
    // Corpo da peça
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.4f, 0.4f, 0.2f, 32, 32);
    gluDisk(quad, 0, 0.4f, 32, 1);
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
                glColor3f(0.8f, 0.8f, 0.8f); // Casas brancas
            } else {
                glColor3f(0.3f, 0.3f, 0.3f); // Casas pretas
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

    // Configuração da câmera
    gluLookAt(0.0f, 12.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Rotação do tabuleiro
    glRotatef(boardRotation, 0.0f, 1.0f, 0.0f);

    // Desenha tabuleiro e peças
    drawBoard();
    for (const auto& piece : pieces) {
        drawPiece(piece);
    }

    glutSwapBuffers();
}

// Inicialização do OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_position[] = { 0.0f, 10.0f, 5.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    initializeBoard();
}

// Redimensiona a janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Jogo de Damas 3D");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
