#pragma once
#include "CScene.h"

class CObject;
class CBackground;
class CExit_Trigger;
class CInteractive;
class CWall;

class CStaticobject;

class CScene_Lobby :
    public CScene
{
public:
    CScene_Lobby();
    ~CScene_Lobby();
    virtual void Enter();
    virtual void Exit();
    void FirstEnter();
    void SecondEnter();

public:
    CWall* pWall_1;
    CWall* pWall_2;
    CWall* pWall_3;
    CWall* pWall_4;

	
	CWall* pWall_11;
	CWall* pWall_12;
	CWall* pWall_13;
	CWall* pWall_14;

	
	CWall* pWall_21;
	CWall* pWall_22;
	CWall* pWall_23;
	CWall* pWall_24;

	
	CWall* pWall_31;
	CWall* pWall_32;
	CWall* pWall_33;
	CWall* pWall_34;

	CWall* pWall_41;
	CWall* pWall_42;
	CWall* pWall_43;
    CWall* pWall_44;
    CWall* pWall_45;
    //CWall* pWall_45;


    CObject* pPlayer;
    CBackground* pBackground;
    CExit_Trigger* pExit_Art;
    CExit_Trigger* pExit_PM;
    CExit_Trigger* pExit_ROOM;
	CInteractive* pInfinite;    // 원내 게시판
	CInteractive* pInfinite1;   // 무한대 기호
    CInteractive* pPuzzle_Clock;

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

    const wchar_t* pObjectKeyArr[11] = { nullptr };
    const wchar_t* pObjectTexArr[11] = { nullptr };

};

