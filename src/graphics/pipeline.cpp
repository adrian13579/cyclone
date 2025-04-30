#include "../include/graphics/pipeline.h"
#include <iostream>

Pipeline::Pipeline() {

    std::cout << "Pipeline constructor"<<std::endl;
    m_scale = cyclone::Vector3(1.0f, 1.0f, 1.0f);
    m_worldPos = cyclone::Vector3(0.0f, 0.0f, 0.0f);
    m_rotateInfo = cyclone::Vector3(0.0f, 0.0f, 0.0f);

    m_camera = new Camera(); 
    m_camera->SetPosition(cyclone::Vector3(1,0,0));
    m_camera->SetTarget(cyclone::Vector3 (0, 0, 1));
    m_camera->SetUp(cyclone::Vector3 (0,1, 0));
    m_camera->SetSpeed(0.1f);
    SetCamera(*m_camera);
}

Pipeline::~Pipeline() {
    if(m_camera != nullptr) {
        delete m_camera;
    }
}

void Pipeline::Scale(float scaleX, float scaleY, float scaleZ) {
    m_scale.x = scaleX;
    m_scale.y = scaleY;
    m_scale.z = scaleZ;
}

void Pipeline::WorldPos(float x, float y, float z) {
    m_worldPos.x = x;
    m_worldPos.y = y;
    m_worldPos.z = z;
}


void Pipeline::Rotate(float rotateX, float rotateY, float rotateZ) {
    m_rotateInfo.x = rotateX;
    m_rotateInfo.y = rotateY;
    m_rotateInfo.z = rotateZ;
}

const graphics::Matrix4* Pipeline::GetTrans() {
    graphics::Matrix4 scaleMatrix = graphics::Matrix4::Scale(m_scale.x, m_scale.y, m_scale.z);

    graphics::Matrix4 rotation_x = graphics::Matrix4::Rotation(m_rotateInfo.x, 1, 0, 0);
    graphics::Matrix4 rotation_y = graphics::Matrix4::Rotation(m_rotateInfo.y, 0, 1, 0);
    graphics::Matrix4 rotation_z = graphics::Matrix4::Rotation(m_rotateInfo.z, 0, 0, 1);

    graphics::Matrix4 rotateMatrix = rotation_x * rotation_y * rotation_z;

    graphics::Matrix4 perspectiveMatrix = graphics::Matrix4::PerspectiveProjection(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
    graphics::Matrix4 translationMatrix = graphics::Matrix4::Translation(m_worldPos.x, m_worldPos.y, m_worldPos.z);

    graphics::Matrix4 cameraMatrix = m_camera->GetViewMatrix();

    m_transformation = perspectiveMatrix * cameraMatrix * translationMatrix * rotateMatrix * scaleMatrix;

    return &m_transformation;
}

void Pipeline::SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
}

void Pipeline::SetCamera(const Camera& camera) {
    if(m_camera != nullptr) {
        delete m_camera;
    }
    m_camera = new Camera(camera);
}

Camera* Pipeline::GetCamera() {
    return m_camera;
}