//
//  L3DMaterial.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <glm/gtc/matrix_transform.hpp>

#include "L3DMaterial.h"
#include "L3DTexture.h"
#include "LInterface.h"
#include "io/LFileReader.h"
#include "shader/L3DShader.h"
#include "camera/L3DCamera.h"

L3DSubsetMaterial::L3DSubsetMaterial()
: m_dwOption(0)
, m_p3DShader(nullptr)
{
    m_vecTexture.clear();
}

L3DSubsetMaterial::~L3DSubsetMaterial()
{
    if (m_p3DShader)
    {
        SAFE_DELETE(m_p3DShader);
    }
}

bool L3DSubsetMaterial::LoadLSubsetMaterial(const char* pcszDirectory, GLubyte*& pbyMaterial)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        m_p3DShader = new L3DShader;
        BOOL_ERROR_BREAK(m_p3DShader);
        
        bRetCode = m_p3DShader->LoadShader("res/shader/default.vs", "res/shader/default.fs");
        BOOL_ERROR_BREAK(bRetCode);
        
        bRetCode = m_p3DShader->UpdateShader(); // Important！！！
        BOOL_ERROR_BREAK(bRetCode);
        
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_Material.Ambient);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_Material.Diffuse);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_Material.Specular);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_Material.Emissive);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_Material.Power);
        NORMALIZE_MAT_POWER(m_Material.Power);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_dwOption);
        
        GLuint dwMaterialOptionCount = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwMaterialOptionCount);
        
        for (GLuint j = 0; j < dwMaterialOptionCount; j++)
        {
            bRetCode = LoadOption(pbyMaterial);
            BOOL_ERROR_BREAK(bRetCode);
        }

        GLuint dwNumUsedTexture = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwNumUsedTexture);

        for (GLuint dwTextIndex = 0; dwTextIndex < dwNumUsedTexture; dwTextIndex++)
        {
            L3DTexture::_TEXTURE* pTextureInfo = NULL;
            pbyMaterial = LFileReader::Convert(pbyMaterial, pTextureInfo);

            char szTextureName[FILENAME_MAX];
            sprintf(szTextureName, "%s%s", pcszDirectory, pTextureInfo->szTextureFileName);
            while(char* pszIndex = strchr(szTextureName, '\\'))
                *pszIndex = '/';

            L3DTexture* p3DTexture = new L3DTexture;
            BOOL_ERROR_BREAK(p3DTexture);

            bRetCode = p3DTexture->LoadTexture(szTextureName, pTextureInfo, pbyMaterial);
            BOOL_ERROR_BREAK(bRetCode);
            
            char szSLTexture[FILENAME_MAX];
            sprintf(szSLTexture, "%s%02d", "slTexture", dwTextIndex + 1);
            m_p3DShader->SetInt(szSLTexture, dwTextIndex);

			glm::mat4 matView = glm::translate(matView, glm::vec3(0.0f, 0.0f, -3.0f));
			m_p3DShader->SetMatrix("slViewMatrix", matView);

			glm::mat4 matProj = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
			m_p3DShader->SetMatrix("slProjMatrix", matProj);

			glm::mat4 matModel = glm::rotate(matModel, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            m_p3DShader->SetMatrix("slModelMatrix", matModel);

            m_vecTexture.push_back(p3DTexture);
        }
        
        if (m_dwOption & MATERIAL_OPTION_VERSION_2)
        {
            if (m_dwOption & MATERIAL_OPTION_INCLUDEALLDEFAULTCOLORCAST)
            {
                pbyMaterial = LFileReader::Copy<LCOLOR_RGBA_FLOAT, L3DSubsetMaterial::cNumColorCast>(pbyMaterial, m_ColorCast);
            }
            else
            {
                pbyMaterial = LFileReader::Convert(pbyMaterial, m_ColorCast[0]);
                m_dwOption |= MATERIAL_OPTION_INCLUDEALLDEFAULTCOLORCAST;
            }
            
            pbyMaterial = LFileReader::Convert(pbyMaterial, m_fSpecPower);
            pbyMaterial = LFileReader::Convert(pbyMaterial, m_fEmssPower);
        }
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DSubsetMaterial::LoadOption(GLubyte*& pbyMaterial)
{
    return false;
}

bool L3DSubsetMaterial::UpdateSubsetMaterial()
{
    for (int i = 0; i < m_vecTexture.size(); i++)
    {
        m_vecTexture[i]->UpdateTexture(i);
    }
    
    if (m_p3DShader)
        m_p3DShader->UpdateShader();
    
    return true;
}

bool L3DSubsetMaterial::UpdatePosition(L3DCamera *p3DCamera)
{
    if (m_p3DShader)
    {
        m_p3DShader->SetMatrix("slViewMatrix", p3DCamera->GetViewMatrix());
        m_p3DShader->SetMatrix("slProjMatrix", p3DCamera->GetProjMatrix());
    }
    return true;
}

bool L3DMaterial::LoadLMaterial(const char *cszFileName)
{
    bool bResult = false;
    
    do
    {
        GLubyte* pbyMaterial = nullptr;
        size_t uMaterialLen = 0;
        LFileReader::Reader(cszFileName, &pbyMaterial, &uMaterialLen);
        
        GLuint dwMask = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwMask);
        BOOL_ERROR_BREAK(dwMask >= 0x4D41544C);//MATL对应的ASECC代码
        
        GLuint dwBlockLength = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwBlockLength);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_dwNumMaterials);
        BOOL_ERROR_BREAK(m_dwNumMaterials <= MAX_SUBSET_COUNT);
        
        m_pMaterialSubset = new L3DSubsetMaterial[m_dwNumMaterials];
        BOOL_ERROR_BREAK(m_pMaterialSubset);
        
        char szDir[FILENAME_MAX];
        strcpy(szDir, cszFileName);
        
        char* pszDot = strchr(szDir, '/');
        while (pszDot && strchr(pszDot + 1, '/'))
            pszDot = strchr(pszDot + 1, '/');
        if (pszDot)
            pszDot[1] = '\0';
        else
            szDir[0] = '\0';
        
        for (GLuint i = 0; i < m_dwNumMaterials; i++)
        {
            m_pMaterialSubset[i].LoadLSubsetMaterial(szDir, pbyMaterial);
            
            //m_bHasDetail = nHasDetail || m_bHasDetail;
            //m_bSortAsSFX = nIsSortAsSFX || m_bSortAsSFX;
        }
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMaterial::UpdateMaterial(GLuint dwSubMaterial)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        bRetCode = m_pMaterialSubset[dwSubMaterial].UpdateSubsetMaterial();
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMaterial::UpdatePosition(L3DCamera *p3DCamera)
{
    for (GLuint i = 0; i < m_dwNumMaterials; i++)
    {
        m_pMaterialSubset[i].UpdatePosition(p3DCamera);
        
        //m_bHasDetail = nHasDetail || m_bHasDetail;
        //m_bSortAsSFX = nIsSortAsSFX || m_bSortAsSFX;
    }
    return true;
}
