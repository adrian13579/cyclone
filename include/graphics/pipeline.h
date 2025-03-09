#include "matrix4.h"
#include "cyclone/core.h"

class Pipeline
{
    public:
       Pipeline(); 
       void Scale(float ScaleX, float ScaleY, float ScaleZ); 
       void WorldPos(float x, float y, float z); 
       void Rotate(float RotateX, float RotateY, float RotateZ);
       const graphics::Matrix4* GetTrans();
    private:
       cyclone::Vector3 m_scale;
       cyclone::Vector3 m_worldPos;
       cyclone::Vector3 m_rotateInfo;
       graphics::Matrix4 m_transformation;
};