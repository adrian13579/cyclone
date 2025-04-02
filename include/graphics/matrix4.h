#include "../cyclone/precision.h"
#include "../cyclone/core.h"

using namespace cyclone;

namespace graphics {
    /**
     * @class Matrix4
     * @brief A 4x4 matrix class for transformations.
     *
     * This class represents a 4x4 matrix used in 3D graphics.
     * It offers multiple constructors for different initialization methods,
     * overloaded operators for element access, and a static method for creating
     * common transformation matrices.
     */
    class Matrix4 {
        public:
            real m_data[4][4]; ///< 4x4 array storing the matrix elements.

            /**
             * @brief Default constructor.
             *
             * Constructs an uninitialized 4x4 matrix.
             */
            Matrix4();

            /**
             * @brief Destructor.
             *
             * Destroys the matrix. No dynamic memory is allocated.
             */
            ~Matrix4();

            /**
             * @brief Constructs a matrix from a 2D array.
             *
             * @param data 2D array of real numbers used to initialize the matrix.
             */
            Matrix4(const real data[4][4]);

            /**
             * @brief Constructs a matrix with individual elements.
             *
             * @param m00 Element at row 0, column 0.
             * @param m01 Element at row 0, column 1.
             * @param m02 Element at row 0, column 2.
             * @param m03 Element at row 0, column 3.
             * @param m10 Element at row 1, column 0.
             * @param m11 Element at row 1, column 1.
             * @param m12 Element at row 1, column 2.
             * @param m13 Element at row 1, column 3.
             * @param m20 Element at row 2, column 0.
             * @param m21 Element at row 2, column 1.
             * @param m22 Element at row 2, column 2.
             * @param m23 Element at row 2, column 3.
             * @param m30 Element at row 3, column 0.
             * @param m31 Element at row 3, column 1.
             * @param m32 Element at row 3, column 2.
             * @param m33 Element at row 3, column 3.
             */
            Matrix4(real m00, real m01, real m02, real m03,
                    real m10, real m11, real m12, real m13,
                    real m20, real m21, real m22, real m23,
                    real m30, real m31, real m32, real m33);

            /**
             * @brief Non-const subscript operator for element access.
             *
             * Allows modification of matrix rows.
             * @param row Index of the row.
             * @return Pointer to the row array.
             */
            real* operator[](int row);

            /**
             * @brief Const subscript operator for element access.
             *
             * Provides read-only access to matrix rows.
             * @param row Index of the row.
             * @return Constant pointer to the row array.
             */
            const real* operator[](int row) const;

            /**
             * @brief Multiplies two matrices.
             *
             * Multiplies two 4x4 matrices together.
             * @param other The matrix to multiply by.
             * @return The product of the two matrices.
             */
            Matrix4 operator*(const Matrix4& other) const;

            /**
             * @brief Creates a translation matrix.
             *
             * Generates a matrix representing a translation transformation.
             *
             * @param x Translation along the x-axis.
             * @param y Translation along the y-axis.
             * @param z Translation along the z-axis.
             * @return A Matrix4 for the translation.
             */
            static Matrix4 Translation(real x, real y, real z);

            /**
            * @brief Creates a rotation matrix.
            * 
            * Generates a matrix representing a rotation transformation.
            *
            * @param angle The angle of rotation in radians.
            * @param x The x-component of the rotation axis.
            * @param y The y-component of the rotation axis.
            * @param z The z-component of the rotation axis.
            */
            static Matrix4 Rotation(real angle, real x, real y, real z);

            /**
             * @brief Creates an identity matrix.
             *
             * Creates an identity matrix.
             */
            static Matrix4 Identity();

            /**
             * @brief Creates a scaling matrix.
             *
             * Generates a matrix representing a scaling transformation.
             *
             * @param x Scaling factor along the x-axis.
             * @param y Scaling factor along the y-axis.
             * @param z Scaling factor along the z-axis.
             * @return A Matrix4 for the scaling.
             */
            static Matrix4 Scale(real x, real y, real z);


            /**
             * @brief Creates a perspective projection matrix.
             *
             * Generates a matrix for perspective projection.
             *
             * @param fov Field of view in radians.
             * @param aspectRatio Aspect ratio of the viewport.
             * @param nearPlane Distance to the near clipping plane.
             * @param farPlane Distance to the far clipping plane.
             * @return A Matrix4 for the perspective projection.
             */
            static Matrix4 PerspectiveProjection(radian fov, real aspcectRatio, real nearPlane, real farPlane);

            static Matrix4 Camera(Vector3 position, Vector3 u, Vector3 v, Vector3 n);
    };
}