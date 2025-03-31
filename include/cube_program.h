#include "../include/graphics/program.h"
#include "../include/graphics/pipeline.h"

namespace demo {

    class CubeProgram : public graphics::OpenGLProgram {

        public:
            CubeProgram();
            CubeProgram(int width, int height) : m_width(width), m_height(height) {};
            ~CubeProgram();

            void CreateProgram() override;
            void Display() override;

        protected:
            void CreateVertexBuffer() override;

        private:
            int m_width = 500;
            int m_height = 500;
            GLuint m_vbo;
            GLuint m_ibo;
            Pipeline* m_pipeline = new Pipeline();
    };
}