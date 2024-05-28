#pragma once
#include "CObject.h"
#include "CKeyMgr.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;
    CTexture* m_floatingTex; // 플로팅 UI 텍스쳐
    Vec2 m_PlayerInfo; // 플레이어 크기 정보
    
    double floatingStartTime; // 떠있을 시간
    double floatingEndTime; // 떠있을 시간

    float player_Speed;
    bool m_playSound;

public:
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    CPlayer();
    ~CPlayer();
};