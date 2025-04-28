#include "camera.h"

class Pipeline
{
    public:
       Pipeline(); 
       void Scale(float scaleX, float scaleY, float scaleZ); 
       void WorldPos(float x, float y, float z); 
       void Rotate(radian rotateX, radian rotateY, radian rotateZ);
       void SetPerspectiveProjection(radian fov, float aspectRatio, float nearPlane, float farPlane);
       void SetCamera(const Camera& camera);
       Camera* GetCamera();
       const graphics::Matrix4* GetTrans();
    private:
       radian m_fov;
       float m_aspectRatio;
       float m_nearPlane;
       float m_farPlane;
       Camera* m_camera;
       cyclone::Vector3 m_scale;
       cyclone::Vector3 m_worldPos;
       cyclone::Vector3 m_rotateInfo;
       graphics::Matrix4 m_transformation;
};