#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "../include/cyclone/core.h"

static GLuint vbo;
static GLint scaleLocation;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    static float deltaScale =  0.0005f;

    scale += deltaScale;
    if(scale >= 1.0f || scale <= -1.0f){
        deltaScale = -deltaScale;
    }
    glUniform1f(scaleLocation, scale);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const GLsizei stride = sizeof(cyclone::Vector3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(0) );

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();

    glutPostRedisplay();
};

static void CreateVertexBuffer() {
    cyclone::Vector3 vertices[3];
    vertices[0] = cyclone::Vector3(0.0f, 1.0f, 0.0f);   // Vertex 1
    vertices[1] = cyclone::Vector3(-1.0f, -1.0f, 0.0f); // Vertex 2
    vertices[2] = cyclone::Vector3(1.0f, -1.0f, 0.0f);  // Vertex 3

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
} 

bool ReadFile(const char* filePath, std::string& content) {
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        fprintf(stderr, "Could not read file %s. File does not exist.\n", filePath);
        return false;
    }
    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    content = sstr.str();
    return true;
};

static void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType) {
    GLuint shaderObj = glCreateShader(shaderType);

    if(shaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", shaderType);
        exit(1);
    }

    const GLchar* p[1];

    p[0] = pShaderText;

    GLint lengths[1];

    lengths[0] = strlen(pShaderText);

    glShaderSource(shaderObj, 1, p, lengths);

    glCompileShader(shaderObj);

    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if(!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, infoLog);
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObj);
}

static void CompileShaders() {
    GLuint shaderProgram = glCreateProgram();

    if(shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if(!ReadFile("src/shaders/vertex.glsl", vs)) {
        exit(1);
    }

    AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if(!ReadFile("src/shaders/fragment.glsl", fs)) {
        exit(1);
    }

    AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(success == 0) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
        exit(1);
    }

    scaleLocation = glGetUniformLocation(shaderProgram, "scale");
    if(scaleLocation == -1) {
        fprintf(stderr, "Error getting scale uniform location\n");
        exit(1);
    }



    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
        exit(1);
    }

    glUseProgram(shaderProgram);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    int width = 800, height = 600;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("OpenGL Window");
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    glClearColor(0, 0, 0, 0);
    CreateVertexBuffer();
    CompileShaders();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}