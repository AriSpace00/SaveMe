#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    CTexture* m_pTex;

public:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
    void SetTexture(CTexture* _tex);

public:
    CBackground();
    ~CBackground();

};

