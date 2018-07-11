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
#include "camera/L3DCamera.h"

void FrameBufferSizeFunc(GLFWwindow* pWindow, int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void ProcessInput(GLFWwindow *pWindow)
{
    if(glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, true);
}

L3DEngine::L3DEngine()
: m_bActive(false)
, m_pWindow(nullptr)
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
    
    do
    {
        m_WindowParam = WindowParam;

        BOOL_ERROR_BREAK(glfwInit());

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
        BOOL_ERROR_BREAK(m_pWindow);

		m_p3DCamera = new L3DCamera;
		BOOL_ERROR_BREAK(m_p3DCamera);

		bRetCode = m_p3DCamera->Init(WindowParam.Width, WindowParam.Height);
		BOOL_ERROR_BREAK(bRetCode);
        
        glfwMakeContextCurrent(m_pWindow);
        glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferSizeFunc);
        
        BOOL_ERROR_BREAK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
		glEnable(GL_DEPTH_TEST);

        m_bActive = true;
        
        bResult = true;
    } while(0);
    
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
    
    do
    {
        BOOL_ERROR_BREAK(m_pWindow);
        ProcessInput(m_pWindow);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        std::list<L3DModel*>::iterator itModel;
        for (itModel = m_ModelList.begin(); itModel != m_ModelList.end(); itModel++)
        {
            L3DModel* pObject = *itModel;
            BOOL_ERROR_CONTINUE(pObject);

            pObject->UpdateDisplay();
        }
        
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
        
        bResult = true;
    } while(0);
    
    return bResult;
}

bool L3DEngine::IsActive()
{
    return m_bActive && !glfwWindowShouldClose(m_pWindow);
}

bool L3DEngine::AttachObject(L3DModel* pAction)
{
    bool bResult = false;

    do 
    {
        BOOL_ERROR_BREAK(pAction);
        m_ModelList.push_back(pAction);

        bResult = true;
    } while (0);

    return bResult;
}
