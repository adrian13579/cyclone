#include "../include/graphics/matrix4.h"

class Camera 
{
    public:
        Camera();
        void OnKeyboard(unsigned char key);
        graphics::Matrix4 GetViewMatrix();

        void SetPosition(const cyclone::Vector3& position);
        void SetTarget(const cyclone::Vector3& target);
        void SetUp(const cyclone::Vector3& up);
        void SetSpeed(float speed) { m_speed = speed; }

        cyclone::Vector3 GetPosition() const;

    private:
        cyclone::Vector3 m_position;
        cyclone::Vector3 m_up;
        cyclone::Vector3 m_target;
        float m_speed;
};