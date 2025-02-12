#include "../../include/graphics/matrix4.h"

namespace graphics {
    Matrix4::Matrix4() {
    }

    Matrix4::~Matrix4() {
        // No dynamic memory is allocated, so nothing needs to be deleted.
    }

    Matrix4::Matrix4(const real data[4][4]) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    }

    Matrix4::Matrix4(real m00, real m01, real m02, real m03,
                     real m10, real m11, real m12, real m13,
                     real m20, real m21, real m22, real m23,
                     real m30, real m31, real m32, real m33) {
        data[0][0] = m00;
        data[0][1] = m01;
        data[0][2] = m02;
        data[0][3] = m03;

        data[1][0] = m10;
        data[1][1] = m11;
        data[1][2] = m12;
        data[1][3] = m13;

        data[2][0] = m20;
        data[2][1] = m21;
        data[2][2] = m22;
        data[2][3] = m23;  
        data[3][0] = m30;
        data[3][1] = m31;
        data[3][2] = m32;
        data[3][3] = m33;
    }

    real* Matrix4::operator[](int row) {
        return data[row];
    }

    const real* Matrix4::operator[](int row) const {
        return data[row];
    }

    Matrix4 Matrix4::Translation(real x, real y, real z) {
        real data[4][4] = {
            {1.0f, 0.0f, 0.0f, x},
            {0.0f, 1.0f, 0.0f, y},
            {0.0f, 0.0f, 1.0f, z},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };

        return Matrix4(data);
    }
}
