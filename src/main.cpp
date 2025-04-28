#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>

#include "../include/cube_program.h"

static demo::CubeProgram program;

void initGlut(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int width =800, height = 500;
    glutInitWindowSize(width, height);

    glutInitWindowPosition(200, 100);

    glutCreateWindow("OpenGL Window");

    program = demo::CubeProgram(width, height);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return ;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
}


void display() {
    return program.Display();
}

void onKeyboard(int key, int x, int y) {
    program.OnKeyboard(key);
}

int main(int argc, char** argv) {
    initGlut(argc, argv);

    program.CreateProgram();

    glutDisplayFunc(display);

    glutSpecialFunc(onKeyboard);
    glutSpecialFunc(onKeyboard);

    glutMainLoop();
    return 0;
}