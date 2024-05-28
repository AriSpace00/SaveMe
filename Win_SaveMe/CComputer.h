#pragma once
#include "CObject.h"

class CTexture;

class CComputer :
    public CObject
{
private:
    CTexture* m_pTex;           // 이미지
    CTexture* m_fTex;
  

    bool m_isFloating;
    bool m_isCreated;          // 상호작용 이벤트 생성되었는지 여부 (중복 생성 방지)

    bool m_ComAnimPlay;

public:
    CComputer();
    ~CComputer();

    void SetScale(Vec2 _scale);

    // Scene 에서 호출
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    // Collider Manager 에서 호출
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    bool GetComAnim() { return m_ComAnimPlay; }
};

