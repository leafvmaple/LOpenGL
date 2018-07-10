//
//  L3DCamera.h
//  LEngine
//
//  Created by LeafMaple on 2018/07/10.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef L3DCamera_h
#define L3DCamera_h

#include "glm/glm.hpp"

class L3DCamera
{
public:
    L3DCamera();
    ~L3DCamera();
    
    bool Init(float fWidth, float fHeight);
    bool UpdateYawPitchRoll(float fYaw, float fPitch, float fRoll);
    bool UpdateSightDistance(float fSightDis);
    
    glm::vec3 SetTarget(glm::vec3);
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjMatrix();
    
private:
    float m_fSightDis;
    float m_fYaw;
    float m_fPitch;
    float m_fRoll;
    float m_fWidth;
    float m_fHeight;
    
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

#endif /* L3DCamera_h */
