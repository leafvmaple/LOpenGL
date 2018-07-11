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
{
    
}

L3DCamera::~L3DCamera()
{
    
}

bool L3DCamera::Init(float fWidth, float fHeight)
{
    m_fSightDis  = 500.f;
    m_vUp        = glm::vec3(0.f, 1.f, 0.f);
    m_fWidth     = fWidth;
    m_fHeight    = fHeight;
    
    ComputeViewMatrix();
    ComputePerspectiveMatrix();
    
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

bool L3DCamera::UpdateYawPitchRoll(float fYaw, float fPitch, float fRoll)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        m_fYaw   += fYaw;
        m_fPitch += fPitch;
        m_fRoll  += fRoll;
        
        bRetCode = ComputeViewMatrix();
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DCamera::UpdateSightDistance(float fSightDis)
{
    m_fSightDis += fSightDis;
    m_fSightDis = glm::max(m_fSightDis, 3.f);
    
    ComputeViewMatrix();
    
    return true;
}

bool L3DCamera::ComputeViewMatrix()
{
    glm::vec3 vFont(0.f, 0.f, -m_fSightDis);
    
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
