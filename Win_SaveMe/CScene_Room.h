#pragma once
#include "CScene.h"

class CBackground;
class CObject;
class CExit_Trigger;
class CInteractive;
class CComputer;
class CWall;
class CStaticObject;
class CCom_Anim;


class CScene_Room :
    public CScene
{
public:
	virtual void Enter();
	virtual void Exit();
	CScene_Room();
	~CScene_Room();
	void FirstEnter();
	void SecondEnter();
private:
	CWall* pWall_1;
	CWall* pWall_2;
	CWall* pWall_3;
	CWall* pWall_4;

	// 교수 책상용
	CWall* pWall_5;
	CWall* pWall_30;
	CWall* pWall_31;


	CWall* pWall_6;
	CWall* pWall_7;
	CWall* pWall_8;
	CWall* pWall_9;
	CWall* pWall_10;
	CWall* pWall_11;
	CWall* pWall_12;
	CWall* pWall_13;

	CWall* pWall_21;
	CWall* pWall_22;
	CWall* pWall_23;
	CWall* pWall_24;
	CWall* pWall_25;
	CWall* pWall_26;
	CWall* pWall_27;
	CWall* pWall_28;
	CWall* pWall_29;

	

	CBackground* pBackground;
	CObject* pPlayer;
	CExit_Trigger* pExit_LOBBY;
	CInteractive* pWindow;
	CInteractive* pDoorLock;
	CComputer* pComputer;

	CCom_Anim* pCom_Anim;

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

	const wchar_t* pObjectKeyArr[9] = { nullptr };
	const wchar_t* pObjectTexArr[9] = { nullptr };


};

