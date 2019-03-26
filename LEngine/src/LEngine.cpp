//
//  LEngine.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "LEngine.h"
#include "LAssert.h"
#include "model/L3DModel.h"
#include "input/L3DInput.h"
#include "camera/L3DCamera.h"

void FrameBufferSizeFunc(GLFWwindow* pWindow, int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

L3DEngine::L3DEngine()
: m_bActive(false)
, m_pWindow(nullptr)
, m_p3DInput(nullptr)
, m_p3DCamera(nullptr)
{
    memset(&m_WindowParam, 0, sizeof(m_WindowParam));
}

L3DEngine::~L3DEngine()
{
    
}

bool L3DEngine::Init(L3DWINDOWPARAM& WindowParam)
{
    bool bResult = false;
	bool bRetCode = false;
    
    m_WindowParam = WindowParam;

    BOOL_ERROR_EXIT(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_pWindow = glfwCreateWindow(WindowParam.Width,
                                    WindowParam.Height,
                                    WindowParam.lpszWindowName,
                                    NULL, NULL);
    BOOL_ERROR_EXIT(m_pWindow);

    m_p3DInput = new L3DInput;
    BOOL_ERROR_EXIT(m_p3DInput);

    bRetCode = m_p3DInput->Init(m_pWindow);
    BOOL_ERROR_EXIT(bRetCode);

	m_p3DCamera = new L3DCamera;
    BOOL_ERROR_EXIT(m_p3DCamera);

	bRetCode = m_p3DCamera->Init(WindowParam.Width, WindowParam.Height);
    BOOL_ERROR_EXIT(bRetCode);
        
    glfwMakeContextCurrent(m_pWindow);
    glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferSizeFunc);
        
    BOOL_ERROR_EXIT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glEnable(GL_DEPTH_TEST);

    m_bActive = true;
        
    bResult = true;
Exit0:
    if (!bResult)
    {
        glfwTerminate();
    }
    return bResult;
}

void L3DEngine::Uninit()
{
    glfwTerminate();
}

bool L3DEngine::Update(float fDeltaTime)
{
    bool bResult = false;
    bool bRetCode = false;

    BOOL_ERROR_EXIT(m_pWindow);

    bRetCode = UpdateInput(fDeltaTime);
    BOOL_ERROR_EXIT(bRetCode);

    bRetCode = UpdateCamera(fDeltaTime);
    BOOL_ERROR_EXIT(bRetCode);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto itModel = m_ModelList.begin(); itModel != m_ModelList.end(); itModel++)
    {
        L3DModel* pObject = *itModel;
        BOOL_ERROR_CONTINUE(pObject);

        pObject->UpdateDisplay();
        pObject->UpdatePosition(m_p3DCamera);
    }

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();

    bResult = true;
Exit0:
    return bResult;
}

bool L3DEngine::IsActive()
{
    return m_bActive && !glfwWindowShouldClose(m_pWindow);
}

bool L3DEngine::AttachObject(L3DModel* pAction)
{
    bool bResult = false;

    BOOL_ERROR_EXIT(pAction)
    m_ModelList.push_back(pAction);

    bResult = true;
Exit0:
    return bResult;
}


bool L3DEngine::UpdateInput(float fDeltaTime)
{
    int bResult = false;

    BOOL_ERROR_EXIT(m_p3DInput);
    BOOL_ERROR_EXIT(m_pWindow);

    //if (m_p3DInput->IsKeyDown(GLFW_KEY_ESCAPE));
    //    glfwSetWindowShouldClose(m_pWindow, true);

    m_p3DInput->Update(fDeltaTime);

    bResult = true;
Exit0:
    return bResult;
}

bool L3DEngine::UpdateCamera(float fDeltaTime)
{
    int bResult = false;
    float fYaw = 0.f;
    float fPitch = 0.f;
    float fRoll = 0.f;
    float fSightDis = 0.f;

    BOOL_ERROR_EXIT(m_p3DInput);
    BOOL_ERROR_EXIT(m_p3DCamera);

    fYaw -= (m_p3DInput->MouseDragX(GLFW_MOUSE_BUTTON_LEFT))*  10.0f * fDeltaTime;
    fPitch -= (m_p3DInput->MouseDragY(GLFW_MOUSE_BUTTON_LEFT)) * 10.0f * fDeltaTime;
    fSightDis -= (m_p3DInput->MouseScrollY()) * 10.f * fDeltaTime;

    if (fYaw || fPitch || fRoll)
        m_p3DCamera->UpdateYawPitchRoll(fYaw, fPitch, fRoll);
    if (fSightDis)
        m_p3DCamera->UpdateSightDistance(fSightDis);

    if (m_p3DInput->IsKeyDown(GLFW_KEY_W))
        m_p3DCamera->MoveCamera(L3DCAMERA_MOVE_FORWARD, fDeltaTime);
    if (m_p3DInput->IsKeyDown(GLFW_KEY_S))
        m_p3DCamera->MoveCamera(L3DCAMERA_MOVE_BACK, fDeltaTime);
    if (m_p3DInput->IsKeyDown(GLFW_KEY_A))
        m_p3DCamera->MoveCamera(L3DCAMERA_MOVE_LEFT, fDeltaTime);
    if (m_p3DInput->IsKeyDown(GLFW_KEY_D))
        m_p3DCamera->MoveCamera(L3DCAMERA_MOVE_RIGHT, fDeltaTime);

    bResult = true;
Exit0:
    return bResult;
}
