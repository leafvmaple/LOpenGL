#include "L3DInput.h"

int g_MouseAction[GLFW_MOUSE_BUTTON_COUNT];

glm::vec2 g_CursorPos;
glm::vec2 g_MouseScroll;

void OnMouseButton(GLFWwindow* pWindow, int nKey, int nAction, int nMode)
{
    g_MouseAction[nKey] = nAction;
}

void OnCursorPos(GLFWwindow* pWindow, double lx, double ly)
{
    g_CursorPos = {lx, ly};
}

void OnScroll(GLFWwindow* pWindow, double lx, double ly)
{
    g_MouseScroll = {lx, ly};
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

    m_CursorPos = glm::vec2(0.f);
    m_MouseScroll = glm::vec2(0.f);

    memset(&m_MouseAction, 0, sizeof(m_MouseAction));
    memset(&m_DragPos, 0, sizeof(m_DragPos));

    m_pWindow = window;

    glfwSetMouseButtonCallback(window, OnMouseButton);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetScrollCallback(window, OnScroll);

    bResult = true;
Exit0:
    return bResult;
}

int L3DInput::Update(float fDelta)
{
    for (int i = 0; i < GLFW_MOUSE_BUTTON_COUNT; i++)
    {
        if (g_MouseAction[i] == GLFW_PRESS && m_MouseAction[i] == GLFW_PRESS)
        {
            m_DragPos[i] = m_CursorPos - g_CursorPos;
        }
        else if (g_MouseAction[i] == GLFW_RELEASE)
        {
            memset(&m_DragPos[i], 0, sizeof(m_DragPos[i]));
        }
    }

    memcpy(m_MouseAction, g_MouseAction, sizeof(m_MouseAction));
    m_CursorPos = g_CursorPos;
    m_MouseScroll = g_MouseScroll;

    g_MouseScroll = glm::vec2(0.f);

    return true;
}

bool L3DInput::IsKeyDown(int nKey)
{
    return glfwGetKey(m_pWindow, nKey) == GLFW_PRESS;
}

bool L3DInput::IsMouseButtonDown(int nKey)
{
    return g_MouseAction[nKey] == GLFW_PRESS;
}

float L3DInput::MouseDragX(int nKey)
{
    return m_DragPos[nKey].x;
}

float L3DInput::MouseDragY(int nKey)
{
    return m_DragPos[nKey].y;
}

float L3DInput::MouseScrollX()
{
    return m_MouseScroll.x;
}

float L3DInput::MouseScrollY()
{
    return m_MouseScroll.y;
}

