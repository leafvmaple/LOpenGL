//
//  L3DCamera.h
//  LEngine
//
//  Created by LeafMaple on 2018/07/10.
//  Copyright © 2018 LeafMaple. All rights reserved.
//
#pragma once

#include "glm/glm.hpp"

enum L3DCAMERA_MOVE
{
    L3DCAMERA_MOVE_FORWARD,
    L3DCAMERA_MOVE_BACK,
    L3DCAMERA_MOVE_LEFT,
    L3DCAMERA_MOVE_RIGHT,
};

class L3DCamera
{
public:
    L3DCamera();
    ~L3DCamera();
    
    bool Init(float fWidth, float fHeight);
    bool UpdateYawPitchRoll(float fYaw, float fPitch, float fRoll);
    bool UpdateSightDistance(float fSightDis);

    bool MoveCamera(L3DCAMERA_MOVE nMoveState, float fDeltaTime);

    bool SetTarget(glm::vec3 vTarget);
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjMatrix();
    
private:
    float m_fSightDis;
    float m_fYaw;
    float m_fPitch;
    float m_fRoll;
    float m_fWidth;
    float m_fHeight;
    float m_fCameraSpeed;
    
    glm::vec3 m_vPosition;
    glm::vec3 m_vTarget;
    glm::vec3 m_vUp;
    glm::vec3 m_vFront;
    
    glm::mat4 m_MatrixView;
    glm::mat4 m_MatrixProject;
private:
    bool ComputeViewMatrix();
    bool ComputePerspectiveMatrix();
};

