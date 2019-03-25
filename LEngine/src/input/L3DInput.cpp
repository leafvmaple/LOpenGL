#include "L3DInput.h"

L3DMOUSE_SCROLL L3DInput::m_MouseScroll;

void OnMouseButton(GLFWwindow* pWindow, int nButton, int nAction, int nMode)
{

}

void OnCursorPos(GLFWwindow* pWindow, double lx, double ly)
{

}

void OnScroll(GLFWwindow* pWindow, double xPos, double yPos)
{
    L3DInput::m_MouseScroll.x = xPos;
    L3DInput::m_MouseScroll.y = yPos;
}

L3DInput::L3DInput() :
    m_pWindow(nullptr)
{

}

L3DInput::~L3DInput()
{

}

int L3DInput::Init(GLFWwindow* window)
{
    int bResult = false;

    BOOL_ERROR_EXIT(window);

    m_pWindow = window;

    glfwSetMouseButtonCallback(window, OnMouseButton);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetScrollCallback(window, OnScroll);

    bResult = true;
Exit0:
    return bResult;
}
