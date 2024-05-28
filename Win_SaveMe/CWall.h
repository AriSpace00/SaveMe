#pragma once
#include "CObject.h"


class CWall :
    public CObject
{
private:
    COLLIDER_DIR m_dir;
    Vec2 m_scale;
public:
    CWall();
    ~CWall();
    void SetType(COLLIDER_DIR _dir)
    {
        m_dir = _dir;
    }
    void SetScale(Vec2);
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

};

