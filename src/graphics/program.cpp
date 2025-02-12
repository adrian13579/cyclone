#include "../../include/graphics/program.h"
#include <cassert>
#include <string>

using namespace graphics;

OpenGLProgram::OpenGLProgram() {}
OpenGLProgram::~OpenGLProgram() {}

void OpenGLProgram::CreateProgram() {
    assert(false);
}

void OpenGLProgram::DeleteProgram() {
    assert(false);
}

void OpenGLProgram::Display() {
    assert(false);
}

void OpenGLProgram::CreateVertexBuffer() {
    assert(false);
}

bool OpenGLProgram::ReadFile(const char* filePath, std::string& content) {
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

void OpenGLProgram::AttachShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType) {
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

void OpenGLProgram::CompileShaders() {
    m_shaderProgram = glCreateProgram();

    if(m_shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string content;
    for(auto& shader : m_shaders) {
        if(!ReadFile(shader.first.c_str(), content)) {
            std::cerr << "Error reading file: " << shader.first << std::endl;
            exit(1);
        }
        AttachShader(m_shaderProgram, content.c_str(), shader.second);
    }

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(success == 0) {
        glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
        exit(1);
    }

    glValidateProgram(m_shaderProgram);
    glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", errorLog);
        exit(1);
    }


    glUseProgram(m_shaderProgram);
}

void OpenGLProgram::AddShader(const std::string& pathToShader, GLenum shaderType) {
    m_shaders[pathToShader] = shaderType;
}
