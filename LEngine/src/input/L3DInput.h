#pragma once
#include "LInterface.h"

struct L3DMOUSE_SCROLL
{
    double x;
    double y;
};

class L3DInput
{
public:
    L3DInput();
    ~L3DInput();

    int Init(GLFWwindow* window);
    
public:
    static L3DMOUSE_SCROLL m_MouseScroll;

private:
    GLFWwindow* m_pWindow;
};