//
//  L3DCamera.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/10.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

#include "LAssert.h"
#include "L3DCamera.h"

L3DCamera::L3DCamera()
: m_fSightDis(0.f)
, m_fYaw(0.f)
, m_fPitch(0.f)
, m_fRoll(0.f)
, m_fCameraSpeed(0.f)
{
    
}

L3DCamera::~L3DCamera()
{
    
}

bool L3DCamera::Init(float fWidth, float fHeight)
{
    m_fSightDis  = 5.f;
    m_vTarget    = glm::vec3(0.f, 0.f, 0.f);
    m_vUp        = glm::vec3(0.f, 1.f, 0.f);
    m_fWidth     = fWidth;
    m_fHeight    = fHeight;
    m_fCameraSpeed = 5.f;
    
    ComputeViewMatrix();
    ComputePerspectiveMatrix();
    
    return true;
}

bool L3DCamera::UpdateYawPitchRoll(float fYaw, float fPitch, float fRoll)
{
    m_fYaw += fYaw;
    m_fPitch += fPitch;
    m_fRoll += fRoll;

    ComputeViewMatrix();

    return true;
}

bool L3DCamera::UpdateSightDistance(float fSightDis)
{
    bool bResult = false;
    bool bRetCode = false;

    m_fSightDis += fSightDis;
    m_fSightDis = glm::max(m_fSightDis, 3.f);
    
    ComputeViewMatrix();

    return true;
}


bool L3DCamera::MoveCamera(L3DCAMERA_MOVE nMoveState, float fDeltaTime)
{
    bool bResult = false;
    bool bRetCode = false;

    switch (nMoveState)
    {
    case L3DCAMERA_MOVE_FORWARD:
        m_vTarget -= m_fCameraSpeed * m_vFront * fDeltaTime;
        break;
    case L3DCAMERA_MOVE_BACK:
        m_vTarget += m_fCameraSpeed * m_vFront * fDeltaTime;
        break;
    case L3DCAMERA_MOVE_LEFT:
        m_vTarget += glm::normalize(glm::cross(m_vFront, m_vUp)) * m_fCameraSpeed * fDeltaTime;
        break;
    case L3DCAMERA_MOVE_RIGHT:
        m_vTarget -= glm::normalize(glm::cross(m_vFront, m_vUp)) * m_fCameraSpeed * fDeltaTime;
        break;
    default:
        break;
    }

    ComputeViewMatrix();
    
    return true;
}

bool L3DCamera::SetTarget(glm::vec3 vTarget)
{
    m_vTarget = vTarget;
    return true;
}

glm::mat4 L3DCamera::GetViewMatrix()
{
    return m_MatrixView;
}

glm::mat4 L3DCamera::GetProjMatrix()
{
    return m_MatrixProject;
}

bool L3DCamera::ComputeViewMatrix()
{
    m_vFront.x = cos(glm::radians(m_fPitch)) * cos(glm::radians(m_fYaw)) * m_fSightDis;
    m_vFront.y = sin(glm::radians(m_fPitch)) * m_fSightDis;
    m_vFront.z = cos(glm::radians(m_fPitch)) * sin(glm::radians(m_fYaw)) * m_fSightDis;
    m_vPosition = m_vTarget + m_vFront;
    
    m_MatrixView = glm::lookAt(m_vPosition, m_vTarget, m_vUp);
    return true;
}

bool L3DCamera::ComputePerspectiveMatrix()
{
    m_MatrixProject = glm::perspective(glm::radians(45.0f), m_fWidth / m_fHeight, 0.1f, 100.0f);
	return true;
}
