#pragma once
#include "CObject.h"

class CTexture;

class CComputer :
    public CObject
{
private:
    CTexture* m_pTex;           // �̹���
    CTexture* m_fTex;
  

    bool m_isFloating;
    bool m_isCreated;          // ��ȣ�ۿ� �̺�Ʈ �����Ǿ����� ���� (�ߺ� ���� ����)

    bool m_ComAnimPlay;

public:
    CComputer();
    ~CComputer();

    void SetScale(Vec2 _scale);

    // Scene ���� ȣ��
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    // Collider Manager ���� ȣ��
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    bool GetComAnim() { return m_ComAnimPlay; }
};

