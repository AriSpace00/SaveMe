#pragma once
#include "CObject.h"

class CTexture;

class CAnagram :
    public CObject
{
private:
    CTexture* m_pTex;
    Vec2 m_SceneInfo;

public:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

public:
    CAnagram();
    ~CAnagram();
};

