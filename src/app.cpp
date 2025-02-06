#include "app.h"
#include <GL/freeglut_std.h>
#include <GL/glut.h>

void Application::initGraphics() {
    // Set up the display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(10, 10);
    glutCreateWindow("Cyclone Demo");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}