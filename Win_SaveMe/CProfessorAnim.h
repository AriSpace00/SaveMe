#pragma once
#include "CObject.h"

class CTexture;

class CProfessorAnim :
    public CObject
{
private:
    CTexture* m_pTex;
    Vec2 m_SceneInfo;
    Vec2 m_TexPosInfo;

public:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    void SetTexPos(Vec2 _TexPosInfo);

public:
    CProfessorAnim();
    ~CProfessorAnim();
};

