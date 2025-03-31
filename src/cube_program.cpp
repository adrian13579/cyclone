#include "../include/cube_program.h"

using namespace demo;

CubeProgram::CubeProgram() { }

CubeProgram::~CubeProgram() {}

void CubeProgram::CreateProgram() {
    CreateVertexBuffer();
    AddShader("src/shaders/cube.vert", GL_VERTEX_SHADER);
    AddShader("src/shaders/cube.frag", GL_FRAGMENT_SHADER);
    CompileShaders();
}

void CubeProgram::CreateVertexBuffer() {
    cyclone::Vector3 vertices[8];

    vertices[0] = cyclone::Vector3(0.5f, 0.5f, 0.5f);
    vertices[1] = cyclone::Vector3(-0.5f, 0.5f, -0.5f);
    vertices[2] = cyclone::Vector3(-0.5f, 0.5f, 0.5f);
    vertices[3] = cyclone::Vector3(0.5f, -0.5f, -0.5f);
    vertices[4] = cyclone::Vector3(-0.5f, -0.5f, -0.5f);
    vertices[5] = cyclone::Vector3(0.5f, 0.5f, -0.5f);
    vertices[6] = cyclone::Vector3(0.5f, -0.5f, 0.5f);
    vertices[7] = cyclone::Vector3(-0.5f, -0.5f, 0.5f);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 4,
        5, 6, 3,
        7, 3, 6,
        2, 4, 7,
        0, 7, 6,
        0, 5, 1,
        1, 5, 3,
        5, 0, 6,
        7, 4, 3,
        2, 1, 4,
        0, 2, 7
    };

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}


void CubeProgram::Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    GLuint transformation = glGetUniformLocation(m_shaderProgram, "transform");

    static float angle = 2.0f;
    static float delta = 0.005f;
    if(angle > 360.0f) {
        angle = 0.0f;
    }
    angle += delta;

    m_pipeline->Scale(0.5f, 0.5f, 0.5f);
    m_pipeline->Rotate(0, angle, 0);
    m_pipeline->SetPerspectiveProjection(to_radian(90), (float)m_width / (float)m_height, 0, 10);

    const graphics::Matrix4* transformationMatrix = m_pipeline->GetTrans();

    glUniformMatrix4fv(transformation, 1, GL_TRUE, transformationMatrix[0][0]);

    const GLsizei stride = sizeof(cyclone::Vector3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(0) );

    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutPostRedisplay();

    glutSwapBuffers();
}
