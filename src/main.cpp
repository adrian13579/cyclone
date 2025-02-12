#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>

#include "../include/cyclone/core.h"
#include "../include/triangle_program.h"

static demo::TriangleProgram program;

void initGlut(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int width = 1500, height = 1000;
    glutInitWindowSize(width, height);

    glutInitWindowPosition(200, 100);

    glutCreateWindow("OpenGL Window");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return ;
    }

    glClearColor(0, 0, 0, 0);
}


void display() {
    return program.Display();
}

int main(int argc, char** argv) {
    initGlut(argc, argv);

    program.CreateProgram();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}