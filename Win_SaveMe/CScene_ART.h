#pragma once
#include "CScene.h"

class CBackground;
class CObject;
class CExit_Trigger;
class CInteractive;
class CWall;

class CStaticObject;

class CScene_ART :
    public CScene
{
public:
    CScene_ART();
    ~CScene_ART();
    virtual void Enter();
    virtual void Exit();
    void FirstEnter();
    void SecondEnter();
private:
    CWall* pWall_1;
    CWall* pWall_2;
    CWall* pWall_3;
    CWall* pWall_4;

    // 모둠 책상 1
    CWall* pWall_11;
    CWall* pWall_12;
    CWall* pWall_13;
    CWall* pWall_14;

    // 모둠 책상 2
    CWall* pWall_21;
    CWall* pWall_22;
    CWall* pWall_23;
    CWall* pWall_24;

    // 모니터
    CWall* pWall_31;
    CWall* pWall_32;
    CWall* pWall_33;
    CWall* pWall_34;

	// 양 사이드 학생 막기
	CWall* pWall_35;
	CWall* pWall_36;
	CWall* pWall_37;
	CWall* pWall_38;

    CBackground* pBackground;
    CObject* pPlayer;
    CExit_Trigger* pExit_LOBBY;
    CInteractive* frame_0;
    CInteractive* frame_1;
    CInteractive* frame_2;
    CInteractive* frame_3;
    CInteractive* frame_QR;
    CInteractive* QR;

    // 애니메이션 없는 오브젝트 배치용 클래스
    CStaticObject* pStaticObject_0;
    CStaticObject* pStaticObject_1;
    CStaticObject* pStaticObject_2;
    CStaticObject* pStaticObject_3;
    CStaticObject* pStaticObject_4;
    CStaticObject* pStaticObject_5;
    CStaticObject* pStaticObject_6;
    CStaticObject* pStaticObject_7;
    CStaticObject* pStaticObject_8;
    CStaticObject* pStaticObject_9;
    CStaticObject* pStaticObject_10;
    CStaticObject* pStaticObject_11;
    CStaticObject* pStaticObject_12;
    CStaticObject* pStaticObject_13;
    CStaticObject* pStaticObject_14;



    const wchar_t* pObjectKeyArr[15] = { nullptr };
    const wchar_t* pObjectTexArr[15] = { nullptr };
};

