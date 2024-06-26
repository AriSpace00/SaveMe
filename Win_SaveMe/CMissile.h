#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fDir; // 위 아래 방향

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }

private:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMissile();
    ~CMissile();
};

