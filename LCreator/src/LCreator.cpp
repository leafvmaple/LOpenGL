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
#include "LMaterialCreator.h"

int main()
{
    LMeshCreator MeshCreator;
    
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
        //0, 3, 4
    };
    
    MeshCreator.AddDiffuseVerties(reinterpret_cast<GL_VERTEX*>(vertices), sizeof(vertices) / sizeof(GL_VERTEX));
    MeshCreator.AddFaces(reinterpret_cast<GLInt3*>(indices), sizeof(indices) / sizeof(GLInt3));
    MeshCreator.Create("../LClient/res/model/Rect.mesh");

    LMaterialCreator MaterialCreator;

    LTextureCreator TextureCreator;
    TextureCreator.SetImagePath("wall.jpg");

    MaterialCreator.AddTexture(TextureCreator);
    MaterialCreator.Create("../LClient/res/model/Rect.mtl");
}
