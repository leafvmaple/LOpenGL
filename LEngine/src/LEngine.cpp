//
//  LEngine.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <iostream>
#include "LEngine.h"
#include "LAssert.h"

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
, m_pWindow(NULL)
{
    memset(&m_WindowParam, 0, sizeof(m_WindowParam));
}

L3DEngine::~L3DEngine()
{
    
}

bool L3DEngine::Init(L3DWINDOWPARAM& WindowParam)
{
    bool bResult = false;
    
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
        
        glfwMakeContextCurrent(m_pWindow);
        glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferSizeFunc);
        
        BOOL_ERROR_BREAK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
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
        glClear(GL_COLOR_BUFFER_BIT);
        
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
