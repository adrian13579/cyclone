#include "../../include/graphics/matrix4.h"
#include <cmath>

namespace graphics {
    Matrix4::Matrix4() {
    }

    Matrix4::~Matrix4() {
        // No dynamic memory is allocated, so nothing needs to be deleted.
    }

    Matrix4::Matrix4(const real data[4][4]) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m_data[i][j] = data[i][j];
            }
        }
    }

    Matrix4::Matrix4(real m00, real m01, real m02, real m03,
                     real m10, real m11, real m12, real m13,
                     real m20, real m21, real m22, real m23,
                     real m30, real m31, real m32, real m33) {
        m_data[0][0] = m00;
        m_data[0][1] = m01;
        m_data[0][2] = m02;
        m_data[0][3] = m03;

        m_data[1][0] = m10;
        m_data[1][1] = m11;
        m_data[1][2] = m12;
        m_data[1][3] = m13;

        m_data[2][0] = m20;
        m_data[2][1] = m21;
        m_data[2][2] = m22;
        m_data[2][3] = m23;  
        m_data[3][0] = m30;
        m_data[3][1] = m31;
        m_data[3][2] = m32;
        m_data[3][3] = m33;
    }

    real* Matrix4::operator[](int row) {
        return m_data[row];
    }

    const real* Matrix4::operator[](int row) const {
        return m_data[row];
    }

    Matrix4 Matrix4::Translation(real x, real y, real z) {
        real temp[4][4] = {
            {1.0f, 0.0f, 0.0f, x},
            {0.0f, 1.0f, 0.0f, y},
            {0.0f, 0.0f, 1.0f, 1},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };

        return Matrix4(temp);
    }

    Matrix4 Matrix4::Rotation(real angle, real x, real y, real z) {

        real temp[4][4] = {0};
        if(x == 1) {
            temp[0][0] = 1.0f; temp[0][1] = 0.0f; temp[0][2] = 0.0f; temp[0][3] = 0.0f;
            temp[1][0] = 0.0f; temp[1][1] = cosf(angle); temp[1][2] = -1 * sinf(angle); temp[1][3] = 0.0f;
            temp[2][0] = 0.0f; temp[2][1] = sinf(angle); temp[2][2] = cosf(angle); temp[2][3] = 0.0f;
            temp[3][0] = 0.0f; temp[3][1] = 0.0f; temp[3][2] = 0.0f; temp[3][3] = 1.0f;

            return Matrix4(temp);
        } 
        if(y == 1){
            temp[0][0] = cosf(angle); temp[0][1] = 0.0f; temp[0][2] = sinf(angle); temp[0][3] = 0.0f;
            temp[1][0] = 0.0f; temp[1][1] = 1.0f; temp[1][2] = 0.0f; temp[1][3] = 0.0f;
            temp[2][0] = -1 * sinf(angle); temp[2][1] = 0.0f; temp[2][2] = cosf(angle); temp[2][3] = 0.0f;
            temp[3][0] = 0.0f; temp[3][1] = 0.0f; temp[3][2] = 0.0f; temp[3][3] = 1.0f;

            return Matrix4(temp);
        }
        if(z == 1) {
            temp[0][0] = cosf(angle); temp[0][1] = -1 * sinf(angle); temp[0][2] = 0.0f; temp[0][3] = 0.0f;
            temp[1][0] = sinf(angle); temp[1][1] = cosf(angle); temp[1][2] = 0.0f; temp[1][3] = 0.0f;
            temp[2][0] = 0.0f; temp[2][1] = 0.0f; temp[2][2] = 1.0f; temp[2][3] = 0.0f;
            temp[3][0] = 0.0f; temp[3][1] = 0.0f; temp[3][2] = 0.0f; temp[3][3] = 1.0f;

            return Matrix4(temp);
        }
        // If none of the above conditions are met, return the identity matrix.
        return Matrix4::Identity();
    }

    Matrix4 Matrix4::Identity() {
        real temp[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        return Matrix4(temp);
    }

    Matrix4 Matrix4::Scale(real x, real y, real z) {
        real temp[4][4] = {
            {x, 0.0f, 0.0f, 0.0f},
            {0.0f, y, 0.0f, 0.0f},
            {0.0f, 0.0f, z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        return Matrix4(temp);
    }

    Matrix4 Matrix4::operator*(const Matrix4& m) const {
        real temp[4][4] = {0};
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    temp[i][j] += m_data[i][k] * m[k][j];
                }
            }
        }
        return Matrix4(temp);
    }

    Matrix4 Matrix4::PerspectiveProjection(radian fov, real aspectRatio, real nearPlane, real farPlane) {

        float tanHalfFov = tanf(fov / 2.0f);
        float f = 1.0f / tanHalfFov;

        float zRange = nearPlane - farPlane;

        float a = (-nearPlane - farPlane) / zRange;
        float b = (2.0f * nearPlane * farPlane) / zRange;

        real temp[4][4] = {
            {f/aspectRatio, 0.0f, 0.0f, 0.0f},
            {0.0f, f, 0.0f, 0.0f},
            {0.0f, 0.0f, a, b},
            {0.0f, 0.0f, 1,0}
        };

        //return Matrix4(
            //f/aspectRatio, 0.0f, 0.0f, 0.0f,
            //0.0f, f, 0.0f, 0.0f,
            //0.0f, 0.0f, 1, 1,
            //0.0f, 0.0f, 0, 0
        //);

       return Matrix4(temp);
    }
}
