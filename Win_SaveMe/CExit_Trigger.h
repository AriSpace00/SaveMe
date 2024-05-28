#pragma once
#include "CObject.h"

// 

class CExit_Trigger :
    public CObject
{
private:
    Vec2 vPos;
    SCENE_TYPE m_nextSceneType;
    double delay = 0.f;
    bool m_isCreated;
    bool m_fadeOut;

public:
    
    void SetNextScene(SCENE_TYPE _nextSceneType)
    {
        m_nextSceneType = _nextSceneType;
    }

    CExit_Trigger();
    ~CExit_Trigger();

    // Scene
    void SetScale(Vec2);

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    // Collider Manager 
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
};

