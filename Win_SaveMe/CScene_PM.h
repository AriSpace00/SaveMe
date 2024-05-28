#pragma once
#include "CScene.h"

class CBackground;
class CObject;
class CExit_Trigger;
class CInteractive;

class CWall;

class CStaticObject;

class CProgrammingNPC;

class CScene_PM :
    public CScene
{
public:
    CScene_PM();
    ~CScene_PM();
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

    // 상호작용 퍼즐 모니터
    CWall* pWall_31;
    CWall* pWall_32;
    CWall* pWall_33;
    CWall* pWall_34;

    CBackground* pBackground;
    CObject* pPlayer;
    CExit_Trigger* pExit_LOBBY;
    CInteractive* pPuzzle;
    CInteractive* pStudent_0;
    CInteractive* pStudent_1;
	CInteractive* pStudent_2;

    // 애니메이션 없는 오브젝트 배치용 클래스
    CStaticObject* pStaticObject_0;
    CStaticObject* pStaticObject_1;
    CStaticObject* pStaticObject_2;
    CStaticObject* pStaticObject_3;
    CStaticObject* pStaticObject_4;

    const wchar_t* pObjectKeyArr[5] = { nullptr };
    const wchar_t* pObjectTexArr[5] = { nullptr };

    // Programming NPC Animation
    CProgrammingNPC* m_pProgrammingNPC;
};

