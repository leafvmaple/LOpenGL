//
//  LDefine.h
//  
//
//  Created by LeafMaple on 2018/07/05.
//

#ifndef LDefine_h
#define LDefine_h

#ifdef __APPLE__
typedef unsigned int DWORD;
typedef unsigned char BYTE;
#elif _WIN32
#include <wtypes.h>
#endif

struct LCOLOR_RGBA_FLOAT
{
    float r;
    float g;
    float b;
    float a;
    LCOLOR_RGBA_FLOAT() {};
    LCOLOR_RGBA_FLOAT(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
};

#define L3DCOLOR_ARGB(a,r,g,b) \
    ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define L3DCOLOR_RGBA(r,g,b,a) L3DCOLOR_ARGB(a,r,g,b)

#define L3DCOLOR_COLORVALUE(r,g,b,a) \
    L3DCOLOR_RGBA((DWORD)((r)*255.f), (DWORD)((g)*255.f), (DWORD)((b)*255.f), (DWORD)((a)*255.f))

#define L3DCOLOR_COLORFLOAT(r,g,b,a) \
    (LCOLOR_RGBA_FLOAT((r)/255.f,(g)/255.f,(b)/255.f,(a)/255.f))

#define L3DARGB_COLOR(color) \
    L3DCOLOR_COLORFLOAT(((color)>>16)&0xff,((color)>>8)&0xff,(color)&0xff,(color)>>24)

#endif /* LDefine_h */
