#pragma once
#include "CObject.h"

class CTexture;

class CPuzzle_Frame :
    public CObject
{
public:
    CPuzzle_Frame();
    ~CPuzzle_Frame();

private:
    CTexture* m_pColorTex[4];

	const wchar_t* texKeyArr[10] = {};
	const wchar_t* textureArr[10] = {};

    // 정답 색깔, 위치
    // 얘한테 네가지 액자 정보 다 넣어주기
    // 생성할때는 인덱스만 받아오면 되게
    int m_framenum;
    //Vec2 vPos[4] = { Vec2(500.f, 100.f) ,Vec2(50.f,50.f), Vec2(500.f, -100.f), Vec2(500.f, -100.f) };
    Vec2 vPos_frame[4];
    Vec2 vPos;

    bool isCreated;
    int curColorNum;
    int answerColorNum[4];

public:
    //void SetPos

    void SetFramenum(int _framenum) { m_framenum = _framenum; }

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollision(CCollider* _pOther);

};

