#include "pch.h"
#include "CScene_Room.h"

#include "CCore.h"
#include "CCollisionMgr.h"
#include "Camera.h"
#include "SoundManager.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "GameManager.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CBackground.h"
#include "CInteractive.h"
#include "CExit_Trigger.h"
#include "CComputer.h"
#include "CWall.h"

#include "CStaticObject.h"

#include "CCom_Anim.h"



CScene_Room::CScene_Room()
	:pBackground{}, pPlayer{}, pExit_LOBBY{}
	, pWindow{}, pDoorLock{}, pComputer{}
	, pWall_1{}, pWall_2{}, pWall_3{}, pWall_4{}
	, pCom_Anim(nullptr)
{
	pObjectKeyArr[0] = L"Room_CurtainCloseTex";
	pObjectKeyArr[1] = L"Room_CurtainOpenTex";
	pObjectKeyArr[2] = L"Room_ProfessorChairTex";
	pObjectKeyArr[3] = L"Room_ProfessorDeskTex";
	pObjectKeyArr[4] = L"Room_NormalChairTex";
	pObjectKeyArr[5] = L"Room_RoomItem1Tex";
	pObjectKeyArr[6] = L"Room_RoomItem2Tex";
	pObjectKeyArr[7] = L"Room_RoomItem3Tex";
	pObjectKeyArr[8] = L"Room_TonedownFilterTex";

	pObjectTexArr[0] = L"texture\\MAP\\professor's_office\\Curtain_close.bmp";
	pObjectTexArr[1] = L"texture\\MAP\\professor's_office\\Curtain_open.bmp";
	pObjectTexArr[2] = L"texture\\MAP\\professor's_office\\ProfessorChair.bmp";
	pObjectTexArr[3] = L"texture\\MAP\\professor's_office\\ProfessorTable.bmp";
	pObjectTexArr[4] = L"texture\\MAP\\professor's_office\\Chair.bmp";
	pObjectTexArr[5] = L"texture\\MAP\\professor's_office\\Fridges.bmp";
	pObjectTexArr[6] = L"texture\\MAP\\professor's_office\\Lockers.bmp";
	pObjectTexArr[7] = L"texture\\MAP\\professor's_office\\RoundTable.bmp";
	pObjectTexArr[8] = L"texture\\MAP\\professor's_office\\ToneDownFilter.bmp";

	pCom_Anim = new CCom_Anim;
	AddObject(pCom_Anim, GROUP_TYPE::INTERACTIVE);
}

CScene_Room::~CScene_Room()
{
}

void CScene_Room::FirstEnter()
{
	// camera
	Camera::GetInst()->FadeIn(3.f);

	// sound
	SoundManager::GetInst()->playBGM(BGM::HostilePlanet);

	pWall_1 = new CWall;
	pWall_1->SetPos(Vec2(0.f, -200.f));
	pWall_1->SetScale(Vec2(1600.f, 10.f));
	pWall_1->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_1, GROUP_TYPE::INTERACTIVE);

	pWall_2 = new CWall;
	pWall_2->SetPos(Vec2(0.f, 400.f));
	pWall_2->SetScale(Vec2(1600.f, 10.f));
	pWall_2->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_2, GROUP_TYPE::INTERACTIVE);

	pWall_3 = new CWall;
	pWall_3->SetPos(Vec2(-380.f, 0.f));
	pWall_3->SetScale(Vec2(10.f, 800.f));
	pWall_3->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_3, GROUP_TYPE::INTERACTIVE);

	pWall_4 = new CWall;
	pWall_4->SetPos(Vec2(380.f, 0.f));
	pWall_4->SetScale(Vec2(10.f, 800.f));
	pWall_4->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_4, GROUP_TYPE::INTERACTIVE);

	// 교수 책상 접근 범위
	pWall_5 = new CWall;
	pWall_5->SetPos(Vec2(-250.f, -70.f));
	pWall_5->SetScale(Vec2(400.f, 100.f));
	pWall_5->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_5, GROUP_TYPE::INTERACTIVE);

	pWall_30 = new CWall;
	pWall_30->SetPos(Vec2(-55.f, 55.f));
	pWall_30->SetScale(Vec2(10.f, 300.f));
	pWall_30->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_30, GROUP_TYPE::INTERACTIVE);

	pWall_31 = new CWall;
	pWall_31->SetPos(Vec2(-35.f, 55.f));
	pWall_31->SetScale(Vec2(10.f, 300.f));
	pWall_31->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_31, GROUP_TYPE::INTERACTIVE);




	//콜라이더.입니다.
	pWall_6 = new CWall;
	pWall_6->SetPos(Vec2(-50.f, 250.f));
	pWall_6->SetScale(Vec2(300.f, 130.f));
	pWall_6->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_6, GROUP_TYPE::INTERACTIVE);

	pWall_8 = new CWall;
	pWall_8->SetPos(Vec2(350.f, 100.f));
	pWall_8->SetScale(Vec2(40.f, 10.f));
	pWall_8->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_8, GROUP_TYPE::INTERACTIVE);

	pWall_9 = new CWall;
	pWall_9->SetPos(Vec2(-50.f, 100.f));
	pWall_9->SetScale(Vec2(250.f, 10.f));
	pWall_9->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_9, GROUP_TYPE::INTERACTIVE);

	pWall_10 = new CWall;
	pWall_10->SetPos(Vec2(50.f, 330.f));
	pWall_10->SetScale(Vec2(120.f, 10.f));
	pWall_10->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_10, GROUP_TYPE::INTERACTIVE);

	pWall_11 = new CWall;
	pWall_11->SetPos(Vec2(-380.f, 0.f));
	pWall_11->SetScale(Vec2(10.f, 800.f));
	pWall_11->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_11, GROUP_TYPE::INTERACTIVE);

	pWall_12 = new CWall;
	pWall_12->SetPos(Vec2(-380.f, 0.f));
	pWall_12->SetScale(Vec2(10.f, 800.f));
	pWall_12->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_12, GROUP_TYPE::INTERACTIVE);

	pWall_13 = new CWall;
	pWall_13->SetPos(Vec2(-380.f, 0.f));
	pWall_13->SetScale(Vec2(10.f, 800.f));
	pWall_13->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_13, GROUP_TYPE::INTERACTIVE);

	// 교수 원형 책상
	pWall_21 = new CWall;
	pWall_21->SetPos(Vec2(20.f, 300.f));
	pWall_21->SetScale(Vec2(100.f, 500.f));
	pWall_21->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_21, GROUP_TYPE::INTERACTIVE);

	// 교수실 사물함
	pWall_22 = new CWall;
	pWall_22->SetPos(Vec2(370.f, -100.f));
	pWall_22->SetScale(Vec2(100.f, 500.f));
	pWall_22->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_22, GROUP_TYPE::INTERACTIVE);

	//background
	pBackground = new CBackground;
	pBackground->SetPos(Vec2(960.f, 540.f));
	pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_RoomTex", L"texture\\MAP\\professor's_office\\Background.bmp"));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//닫힌 커튼
	pStaticObject_0 = new CStaticObject;
	pStaticObject_0->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[0], pObjectTexArr[0]));
	pStaticObject_0->SetTexPos(Vec2(536.f, 120.f));
	AddObject(pStaticObject_0, GROUP_TYPE::BACKGROUND);

	//열린 커튼
	/*pStaticObject_1 = new CStaticObject;
	pStaticObject_1->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[1], pObjectTexArr[1]));
	pStaticObject_1->SetTexPos(Vec2(536.f, 120.f));
	AddObject(pStaticObject_1, GROUP_TYPE::BACKGROUND);*/

	//교수님 의자
	pStaticObject_2 = new CStaticObject;
	pStaticObject_2->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[2], pObjectTexArr[2]));
	pStaticObject_2->SetTexPos(Vec2(712.f, 419.f));
	AddObject(pStaticObject_2, GROUP_TYPE::INTERACTIVE);

	//교수님 책상
	pStaticObject_3 = new CStaticObject;
	pStaticObject_3->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[3], pObjectTexArr[3]));
	pStaticObject_3->SetTexPos(Vec2(576.f, 377.f));
	AddObject(pStaticObject_3, GROUP_TYPE::INTERACTIVE);

	//그냥 의자
	pStaticObject_4 = new CStaticObject;
	pStaticObject_4->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[4], pObjectTexArr[4]));
	pStaticObject_4->SetTexPos(Vec2(1045.f, 310.f));
	AddObject(pStaticObject_4, GROUP_TYPE::INTERACTIVE);

	//냉장고
	pStaticObject_5 = new CStaticObject;
	pStaticObject_5->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[5], pObjectTexArr[5]));
	pStaticObject_5->SetTexPos(Vec2(946.f, 866.f));
	AddObject(pStaticObject_5, GROUP_TYPE::INTERACTIVE);

	//사물함
	pStaticObject_6 = new CStaticObject;
	pStaticObject_6->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[6], pObjectTexArr[6]));
	pStaticObject_6->SetTexPos(Vec2(1278.f, 216.f));
	AddObject(pStaticObject_6, GROUP_TYPE::INTERACTIVE);

	//원형테이블
	pStaticObject_7 = new CStaticObject;
	pStaticObject_7->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[7], pObjectTexArr[7]));
	pStaticObject_7->SetTexPos(Vec2(732.f, 630.f));
	AddObject(pStaticObject_7, GROUP_TYPE::INTERACTIVE);

	//톤다운 필터
	pStaticObject_8 = new CStaticObject;
	pStaticObject_8->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[8], pObjectTexArr[8]));
	pStaticObject_8->SetTexPos(Vec2(0.f, 0.f));
	//AddObject(pStaticObject_8, GROUP_TYPE::INTERACTIVE);

	// player
	pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(200.f,-100.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// exit to lobby 
	pExit_LOBBY = new CExit_Trigger;
	pExit_LOBBY->SetPos(Vec2(250.f, 400.f));
	pExit_LOBBY->SetScale(Vec2(200.f, 100.f));
	pExit_LOBBY->SetNextScene(SCENE_TYPE::LOBBY);
	AddObject(pExit_LOBBY, GROUP_TYPE::INTERACTIVE);

	// interactive - curtain
	pWindow = new CInteractive;
	pWindow->SetPos(Vec2(-100.f, -200.f));
	pWindow->SetScale(Vec2(400.f, 50.f));
	pWindow->SetType(INTERACTIVE_TYPE::CHOOSE);
	pWindow->SetTextCount(4);
	pWindow->SetText(L"커튼을 걷을까?", L"> 걷는다       ", L"> 걷지 않는다 ", L"벽에 무언가 적혀있다.");
	pWindow->SetisChoose(false, true, true, false);
	AddObject(pWindow, GROUP_TYPE::INTERACTIVE);

	// interactive - doorlock (exit <-> doorlock)
	pDoorLock = new CInteractive;
	pDoorLock->SetPos(Vec2(200.f, 400.f));
	pDoorLock->SetScale(Vec2(300.f, 200.f));
	/*pDoorLock->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	pDoorLock->SetType(INTERACTIVE_TYPE::PUZZLE_DOORLOCK);
	//pDoorLock->SetTextCount(2);
	//pDoorLock->SetText(L"문을 여는데 성공했다!");
	//GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, false);
	AddObject(pDoorLock, GROUP_TYPE::INTERACTIVE);

	// computer
	pComputer = new CComputer;
	pComputer->SetPos(Vec2(-200.f, 20.f));
	pComputer->SetScale(Vec2(200.f, 300.f));
	AddObject(pComputer, GROUP_TYPE::INTERACTIVE);

	// collision
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TEXT);


	// first == false
	GameManager::GetInst()->SetSceneFirst(SCENE_TYPE::ROOM, false);
}

void CScene_Room::SecondEnter()
{
	pWall_1->SetPos(Vec2(0.f, -200.f));

	pWall_2->SetPos(Vec2(0.f, 400.f));

	pWall_3->SetPos(Vec2(-380.f, 0.f));

	pWall_4->SetPos(Vec2(380.f, 0.f));

	// 교수 책상 접근 범위
	pWall_5->SetPos(Vec2(-250.f, -70.f));

	pWall_30->SetPos(Vec2(-55.f, 55.f));

	pWall_31->SetPos(Vec2(-35.f, 55.f));

	//콜라이더.입니다.
	pWall_6->SetPos(Vec2(-50.f, 250.f));

	pWall_8->SetPos(Vec2(350.f, 100.f));
	pWall_9->SetPos(Vec2(-50.f, 100.f));

	pWall_10->SetPos(Vec2(50.f, 330.f));

	pWall_11->SetPos(Vec2(-380.f, 0.f));

	pWall_12->SetPos(Vec2(-380.f, 0.f));

	pWall_13->SetPos(Vec2(-380.f, 0.f));

	// 교수 원형 책상
	pWall_21->SetPos(Vec2(20.f, 300.f));

	// 교수실 사물함
	pWall_22->SetPos(Vec2(370.f, -100.f));


	pBackground->SetPos(Vec2(960.f, 540.f));
	pPlayer->SetPos(Vec2(250.f, 230.f));
	
	pExit_LOBBY->SetPos(Vec2(250.f, 400.f));
	pDoorLock->SetPos(Vec2(5000.f,5000.f));
	pWindow->SetPos(Vec2(-100.f, -200.f));

	//pDoorLock->SetPos(Vec2(2000.f, 1000.f));
	//pWindow->SetPos(Vec2(400.f, -300.f));
	//pComputer->SetPos(Vec2(0.f, 0.f));
	pComputer->SetPos(Vec2(-200.f, 20.f));

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

}

void CScene_Room::Enter()
{
	GameManager::GetInst()->SetMovable(true);
	GameManager::GetInst()->SetCurScene(SCENE_TYPE::ROOM);


	if (GameManager::GetInst()->GetSceneFirst(SCENE_TYPE::ROOM))
	{
		FirstEnter();
		return;
	}
	else
	{
		SecondEnter();
	}
}

void CScene_Room::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	GameManager::GetInst()->SetPreScene(SCENE_TYPE::ROOM);

}

