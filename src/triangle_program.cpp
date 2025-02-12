#include "../include/cyclone/core.h"
#include "../include/triangle_program.h"
#include "../include/graphics/matrix4.h"

using namespace demo;

TriangleProgram::TriangleProgram() {}

TriangleProgram::~TriangleProgram() {}

void TriangleProgram::CreateProgram() {
    CreateVertexBuffer();
    AddShader("src/shaders/triangle.vert", GL_VERTEX_SHADER);
    AddShader("src/shaders/triangle.frag", GL_FRAGMENT_SHADER);
    CompileShaders();
}

void TriangleProgram::CreateVertexBuffer() {
    cyclone::Vector3 vertices[3];
    vertices[0] = cyclone::Vector3(0.0f, 1.0f, 0.0f);   // Vertex 1
    vertices[1] = cyclone::Vector3(-1.0f, -1.0f, 0.0f); // Vertex 2
    vertices[2] = cyclone::Vector3(1.0f, -1.0f, 0.0f);  // Vertex 3

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void TriangleProgram::Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    if(scaleLocation == 0) {
        scaleLocation = glGetUniformLocation(shaderProgram, "scale");
    }

    static float scale = 0.0f;
    static float delta = 0.0001f;
    scale += delta;
    if(scale >= 1.0f || scale <= 0.0f) {
        delta = -delta;
    }
    glUniform1f(scaleLocation, scale);

    static GLuint matrixLocation;
    if(matrixLocation == 0){
        matrixLocation = glGetUniformLocation(shaderProgram, "translation");
    }

    graphics::Matrix4 translationMatrix = graphics::Matrix4::Translation(scale*2, scale, 0.0f);

    glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, &translationMatrix[0][0]);

    const GLsizei stride = sizeof(cyclone::Vector3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(0) );

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();

    glutPostRedisplay();
}