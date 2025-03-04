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

    glGenBuffers(1, &m_vbo); // Updated to m_vbo
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void TriangleProgram::Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // Updated to m_vbo

    m_transformation = glGetUniformLocation(m_shaderProgram, "transformation");

    static float angle = 2.0f;
    static float delta = 0.01f;
    if(angle > 360.0f) {
        angle = 0.0f;
    }
    angle += delta;

    static float scale = 0.01f;
    static float scaleDelta = 0.001f;
    if(scale > 1.0f || scale < -1.0f) {
        scaleDelta *= -1 ;
    }
    scale+=scaleDelta;

    graphics::Matrix4 scaleMatrix = graphics::Matrix4::Scale(scale,scale,scale);
    graphics::Matrix4 rotationMatrix = graphics::Matrix4::Rotation(angle,1,0,0);

    graphics::Matrix4 transformationMatrix = scaleMatrix * rotationMatrix;

    glUniformMatrix4fv(m_transformation, 1, GL_TRUE, &transformationMatrix[0][0]);

    const GLsizei stride = sizeof(cyclone::Vector3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(0) );

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();

    glutPostRedisplay();
}