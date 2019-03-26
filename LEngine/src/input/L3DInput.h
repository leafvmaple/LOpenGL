#pragma once
#include "LInterface.h"

#define GLFW_MOUSE_BUTTON_COUNT (GLFW_MOUSE_BUTTON_LAST + 1)

class L3DInput
{
public:
    L3DInput();
    ~L3DInput();

    int Init(GLFWwindow* window);
    int Update(float fDelta);

    bool IsKeyDown(int nKey);
    bool IsMouseButtonDown(int nButton);
    float MouseDragX(int nButton);
    float MouseDragY(int nButton);
    float MouseScrollX();
    float MouseScrollY();

private:

    int m_MouseAction[GLFW_MOUSE_BUTTON_COUNT];
    glm::vec2 m_CursorPos;
    glm::vec2 m_MouseScroll;
    glm::vec2 m_DragPos[GLFW_MOUSE_BUTTON_COUNT];

    GLFWwindow* m_pWindow;
};