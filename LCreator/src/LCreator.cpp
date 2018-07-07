//
//  LCreator.cpp
//  LCreator
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <stdio.h>
#include <cstring>
#include "LMeshCreator.h"

int main()
{
    LMeshCreator MeshCreator;
    MeshCreator.Init();
    
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    MeshCreator.AddVerties(reinterpret_cast<GLVec3*>(vertices), sizeof(vertices) / sizeof(GLVec3));
    MeshCreator.AddFaces(reinterpret_cast<GLFace3*>(indices), sizeof(indices) / sizeof(GLFace3));
    MeshCreator.Create("Rect.mesh");
}
