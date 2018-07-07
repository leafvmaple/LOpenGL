//
//  L3DMaterial.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include "L3DMaterial.h"
#include "L3DTexture.h"
#include "LInterface.h"
#include "io/LFileReader.h"

L3DSubsetMaterial::L3DSubsetMaterial()
: m_p3DTexture(nullptr)
{
    
}

bool L3DSubsetMaterial::LoadLSubsetMaterial(const char* pcszDirectory, BYTE*& pbyMaterial)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        m_p3DTexture = new L3DTexture;
        BOOL_ERROR_BREAK(m_p3DTexture);
        
        bRetCode = m_p3DTexture->LoadLTexture("res/model/texture/wall.jpg");
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DSubsetMaterial::LoadOption(BYTE*& pbyMaterial)
{
    return false;
}

bool L3DSubsetMaterial::UpdateSubsetMaterial()
{
    if (m_p3DTexture)
        m_p3DTexture->UpdateTexture();
    
    return true;
}

bool L3DMaterial::LoadLMaterial(const char *cszFileName)
{
    bool bResult = false;
    
    do
    {
        m_dwNumMaterials = 1;
        m_pMaterialSubset = new L3DSubsetMaterial[m_dwNumMaterials];
        
        BYTE* mtl = new BYTE[1];
        m_pMaterialSubset[0].LoadLSubsetMaterial(nullptr, mtl);
        
        /*BYTE* pbyMaterial = nullptr;
        size_t uMaterialLen = 0;
        LFileReader::Reader(cszFileName, &pbyMaterial, &uMaterialLen);
        
        DWORD dwMask = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwMask);
        BOOL_ERROR_BREAK(dwMask >= 0x4D41544C);//MATL对应的ASECC代码
        
        DWORD dwBlockLength = 0;
        pbyMaterial = LFileReader::Convert(pbyMaterial, dwBlockLength);
        pbyMaterial = LFileReader::Convert(pbyMaterial, m_dwNumMaterials);
        BOOL_ERROR_BREAK(m_dwNumMaterials <= MAX_SUBSET_COUNT);
        
        m_pMaterialSubset = new L3DSubsetMaterial[m_dwNumMaterials];
        BOOL_ERROR_BREAK(m_pMaterialSubset);
        
        char wcszDir[FILENAME_MAX];
        for (DWORD i = 0; i < m_dwNumMaterials; i++)
        {
            m_pMaterialSubset[i].LoadLSubsetMaterial(wcszDir, pbyMaterial);
            
            //m_bHasDetail = nHasDetail || m_bHasDetail;
            //m_bSortAsSFX = nIsSortAsSFX || m_bSortAsSFX;
        }*/
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMaterial::UpdateMaterial(DWORD dwSubMaterial)
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
