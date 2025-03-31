namespace cyclone {
    /**
    * Defines a real number precision. Cyclone can be compiled in
    * single- or double-precision versions. By default single precision
    * is provided.
    */
    typedef float real;

    typedef float radian;

    /** Defines the precision of the square root operator. */
    #define real_sqrt sqrtf

    /** Defines the precision of the power operator. */
    #define real_pow powf

    #define to_radian(x) ((x) * M_PI / 180.0f)

    #define to_degree(x) ((x) * 180.0f / M_PI)
}