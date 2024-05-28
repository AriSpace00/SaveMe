#pragma once
#include "CObject.h"
#include "CKeyMgr.h"

class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture* m_pTex;
    CTexture* m_floatingTex; // �÷��� UI �ؽ���
    Vec2 m_PlayerInfo; // �÷��̾� ũ�� ����
    
    double floatingStartTime; // ������ �ð�
    double floatingEndTime; // ������ �ð�

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