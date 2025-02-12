#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace graphics {
    /**
     * @class OpenGLProgram
     * @brief A class to manage OpenGL shader programs.
     * 
     * This class provides functionalities to create, compile, and manage OpenGL shader programs.
     * It also includes methods to read shader files and manage vertex buffer objects.
     */
    class OpenGLProgram {
    public:
        /**
         * @brief Constructor for OpenGLProgram.
         */
        OpenGLProgram();

        /**
         * @brief Destructor for OpenGLProgram.
         */
        ~OpenGLProgram();

        /**
         * @brief Creates a new OpenGL program.
         */
        virtual void CreateProgram();

        /**
         * @brief Compiles the shaders that have been added to the program.
         */
        void CompileShaders();

        /**
         * @brief Deletes the shader program.
         */
        void DeleteProgram();

        /**
         * @brief Displays the content using the shader program.
         * 
         * This method is meant to be overridden by derived classes to provide specific display functionality.
         */
        virtual void Display();

        /**
         * @brief Sets the display callback for the OpenGL program.
         * 
         * @param programInstance A pointer to the instance of OpenGLProgram.
         */
        static void SetDisplayCallback(OpenGLProgram* programInstance);

    private:
        /**
         * @brief Reads the content of a file.
         * 
         * @param filePath The path to the file.
         * @param content A string to store the content of the file.
         * @return True if the file was read successfully, false otherwise.
         */
        bool ReadFile(const char* filePath, std::string& content);


        /**
        * @brief Attaches a shader to the program.
        * 
        * @param shaderProgram The shader program to attach the shader to.
        * @param pShaderText The shader text.
        * @param shaderType The type of the shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
        */
        void AttachShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

    protected:
        /**
         * @brief Creates a vertex buffer object.
         * 
         * This method is meant to be overridden by derived classes to provide specific vertex buffer creation functionality.
         */
        virtual void CreateVertexBuffer();

        /**
         * @brief Adds a shader to the program.
         * 
         * @param pathToShader The path to the shader file.
         * @param shaderType The type of the shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
         */
        void AddShader(const std::string& pathToShader, GLenum shaderType);

        /**
        * @brief A map to store the shaders.
        */
        std::unordered_map<std::string, GLenum> shaders; ///< An unordered map to store the shaders.

        /**
        * @brief A vector to store vertex array buffer objects.
        */
        std::vector<GLuint> vertexArrayBuffers; ///< A vector to store vertex array buffer objects.

        GLuint shaderProgram; ///< Shader program for the triangle.
    };
}