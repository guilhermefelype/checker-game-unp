#include "../include/renderer.h"
#include <GL/glut.h>

void Renderer::drawBoard(const Board& board) {
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

void Renderer::drawPiece(const Piece& piece) {
    glPushMatrix();
    glTranslatef(piece.pos.x - 3.5f + 0.5f, 0.2f, piece.pos.z - 3.5f);

    if (piece.isWhite) {
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }

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

void Renderer::initOpenGL() {
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
}
