
#include "../include/graphics/program.h"

namespace demo {

    /**
     * @class TriangleProgram
     * @brief A class to manage an OpenGL program for rendering a triangle.
     * 
     * This class inherits from OpenGLProgram and provides specific implementations
     * for creating vertex buffers and displaying a triangle.
     */
    class TriangleProgram : public graphics::OpenGLProgram {
    public:
        /**
         * @brief Constructor for TriangleProgram.
         */
        TriangleProgram();

        /**
         * @brief Destructor for TriangleProgram.
         */
        ~TriangleProgram();

        /**
         * @brief Creates the OpenGL program for rendering a triangle.
         */
        void CreateProgram() override;

        /**
         * @brief Displays the triangle.
         */
        void Display() override;

    protected:
        /**
         * @brief Creates the vertex buffer for the triangle.
         */
        void CreateVertexBuffer() override;

    private:
        GLuint vbo; ///< Vertex buffer object for the triangle.
    };
}