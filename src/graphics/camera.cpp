#include "../include/graphics/camera.h"
#include <GL/freeglut_std.h>
#include <iostream>

Camera::Camera(){
    std::cout<<"Camera constructor"<<std::endl;
}

void Camera::SetPosition(const cyclone::Vector3& position){
    this->m_position = position;
}


cyclone::Vector3 Camera::GetPosition() const{
    return m_position;
}

graphics::Matrix4 Camera::GetViewMatrix(){
    cyclone::Vector3 n = m_target;
    n.normalize();

    cyclone::Vector3 u = m_up % n; // cross product
    u.normalize();

    cyclone::Vector3 v = n % u; // cross product
    v.normalize();

    //std::cout << "postion" << position.x << " " << position.y << " " << position.z << std::endl;
    graphics::Matrix4 viewMatrix = graphics::Matrix4::Camera(m_position, u, v, n);
    return viewMatrix;
}

void Camera::SetTarget(const cyclone::Vector3& target){
    m_target = target;
}

void Camera::SetUp(const cyclone::Vector3& up){
    m_up = up;
}

void Camera::OnKeyboard(unsigned char key){
    std::cout << "key: " << key << std::endl;
    switch (key) {
        case GLUT_KEY_UP:
            m_position += m_target * m_speed;
            break;
        case GLUT_KEY_DOWN:
            m_position -= m_target * m_speed;
            break;
        case GLUT_KEY_LEFT:
        {
            cyclone::Vector3 left = m_target % m_up;
            left.normalize();
            m_position += left * m_speed;
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            cyclone::Vector3 right = m_up % m_target;
            right.normalize();
            m_position += right * m_speed;
            break;
        }
        case GLUT_KEY_PAGE_UP:
            m_position.y -= m_speed; 
            break;
        case GLUT_KEY_PAGE_DOWN:
            m_position.y += m_speed; 
            break;

        case '+':
            m_speed += 0.1f;
            break;
        case '-':
            m_speed -= 0.1f;
            if(m_speed < 0.1f)
                m_speed = 0.1f;
            break;
    }
} 