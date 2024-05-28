#pragma once
#include "CObject.h"

class CTexture;

class CStaticObject :
    public CObject
{
private:
    CTexture* m_pTex;    
    Vec2 m_TexPosInfo;
    
    bool m_isVisible = true;

public:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetTexPos(Vec2 _TexPosInfo);
    void SetTexture(CTexture* _tex);
    void SetVisible(bool _isVisible) { m_isVisible = _isVisible; }



public:
    CStaticObject();
    ~CStaticObject();
};

