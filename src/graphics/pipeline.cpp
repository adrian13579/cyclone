#include "../include/graphics/pipeline.h"


void Pipeline::Scale(float ScaleX, float ScaleY, float ScaleZ) {
    m_scale.x = ScaleX;
    m_scale.y = ScaleY;
    m_scale.z = ScaleZ;
}

void Pipeline::WorldPos(float x, float y, float z) {
    m_worldPos.x = x;
    m_worldPos.y = y;
    m_worldPos.z = z;
}


void Pipeline::Rotate(float RotateX, float RotateY, float RotateZ) {
    m_rotateInfo.x = RotateX;
    m_rotateInfo.y = RotateY;
    m_rotateInfo.z = RotateZ;
}

const graphics::Matrix4* Pipeline::GetTrans() {
    graphics::Matrix4 scaleMatrix = graphics::Matrix4::Scale(m_scale.x, m_scale.y, m_scale.z);

    graphics::Matrix4 rotation_x = graphics::Matrix4::Rotation(m_rotateInfo.x, 1, 0, 0);
    graphics::Matrix4 rotation_y = graphics::Matrix4::Rotation(m_rotateInfo.y, 0, 1, 0);
    graphics::Matrix4 rotation_z = graphics::Matrix4::Rotation(m_rotateInfo.z, 0, 0, 1);

    graphics::Matrix4 rotateMatrix = rotation_x * rotation_y * rotation_z;
    graphics::Matrix4 translationMatrix = graphics::Matrix4::Translation(m_worldPos.x, m_worldPos.y, m_worldPos.z);

    m_transformation = translationMatrix * rotateMatrix * scaleMatrix;

    return &m_transformation;
}