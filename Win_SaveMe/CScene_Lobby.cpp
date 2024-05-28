#include "pch.h"
#include "CScene_Lobby.h"

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
#include "CWall.h"
#include "CComputer.h"

#include "CStaticObject.h"

CScene_Lobby::CScene_Lobby()
	: pPlayer(), pBackground(), 
	pExit_Art(), pExit_PM(), pExit_ROOM(), 
	pInfinite(), pPuzzle_Clock{},
	pWall_1{}, pWall_2{}, pWall_3{}, pWall_4{}
{
	// 애니메이션 없는 오브젝트 키 값 & 경로
	pObjectKeyArr[0] = L"LB_ArcadeGameTex";
	pObjectKeyArr[1] = L"LB_LaptopTex";
	pObjectKeyArr[2] = L"LB_NoticeBoardTex";
	pObjectKeyArr[3] = L"LB_PillarTex";
	pObjectKeyArr[4] = L"LB_Pot1Tex";
	pObjectKeyArr[5] = L"LB_Pot2Tex";
	pObjectKeyArr[6] = L"LB_PurifierTex";
	pObjectKeyArr[7] = L"LB_Sign_artTex";
	pObjectKeyArr[8] = L"LB_Sign_proTex";
	pObjectKeyArr[9] = L"LB_TableTex";
	pObjectKeyArr[10] = L"LB_TrashcanTex";

	pObjectTexArr[0] = L"texture\\MAP\\lobby\\arcadegame.bmp";
	pObjectTexArr[1] = L"texture\\MAP\\lobby\\labtop.bmp";
	pObjectTexArr[2] = L"texture\\MAP\\lobby\\noticeboard.bmp";
	pObjectTexArr[3] = L"texture\\MAP\\lobby\\pillar.bmp";
	pObjectTexArr[4] = L"texture\\MAP\\lobby\\pot1.bmp";
	pObjectTexArr[5] = L"texture\\MAP\\lobby\\pot2.bmp";
	pObjectTexArr[6] = L"texture\\MAP\\lobby\\purifier.bmp";
	pObjectTexArr[7] = L"texture\\MAP\\lobby\\sign_art.bmp";
	pObjectTexArr[8] = L"texture\\MAP\\lobby\\sign_pro.bmp";
	pObjectTexArr[9] = L"texture\\MAP\\lobby\\table.bmp";
	pObjectTexArr[10] = L"texture\\MAP\\lobby\\trashcan.bmp";
}

CScene_Lobby::~CScene_Lobby()
{
}

void CScene_Lobby::FirstEnter()
{
	// camera
	Camera::GetInst()->FadeIn(3.f);

	// sound
	//SoundManager::GetInst()->playBGM(BGM::testBGM);

	pWall_1 = new CWall;
	pWall_1->SetPos(Vec2(0.f, -270.f));
	pWall_1->SetScale(Vec2(2000.f, 10.f));
	pWall_1->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_1, GROUP_TYPE::INTERACTIVE);

	pWall_2 = new CWall;
	pWall_2->SetPos(Vec2(0.f, 500.f));

	pWall_2->SetScale(Vec2(2000.f, 10.f));
	pWall_2->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_2, GROUP_TYPE::INTERACTIVE);

	/// 가장 좌측 큰 벽
	pWall_3 = new CWall;
	pWall_3->SetPos(Vec2(-670.f, -180.f));
	pWall_3->SetScale(Vec2(10.f, 500.f));
	pWall_3->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_3, GROUP_TYPE::INTERACTIVE);

	pWall_4 = new CWall;
	pWall_4->SetPos(Vec2(580.f, 70.f));
	pWall_4->SetScale(Vec2(50.f, 420.f));
	pWall_4->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_4, GROUP_TYPE::INTERACTIVE);

	/// 콜라이더 렌더 확인용 - 기능 없음
	pWall_44 = new CWall;
	pWall_44->SetPos(Vec2(-730.f, 50.f));
	pWall_44->SetScale(Vec2(150.f, 30.f));
	pWall_44->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_44, GROUP_TYPE::INTERACTIVE);

	pWall_45 = new CWall;
	pWall_45->SetPos(Vec2(-750.f, 30.f));
	pWall_45->SetScale(Vec2(10.f, 500.f));
	pWall_45->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_45, GROUP_TYPE::INTERACTIVE);


	/// 오른쪽 벽들

	/// 완 엘베 앞
	pWall_11 = new CWall;
	pWall_11->SetPos(Vec2(770.f, 280.f));
	pWall_11->SetScale(Vec2(400.f, 10.f));
	pWall_11->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_11, GROUP_TYPE::INTERACTIVE);

	/// 완
	pWall_12 = new CWall;
	pWall_12->SetPos(Vec2(650.f, -150.f));
	pWall_12->SetScale(Vec2(200.f, 10.f));
	pWall_12->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_12, GROUP_TYPE::INTERACTIVE);

	/// 완 최 우측 엘베 앞 벽
	pWall_13 = new CWall;
	pWall_13->SetPos(Vec2(830.f, 0.f));
	pWall_13->SetScale(Vec2(10.f, 1000.f));
	pWall_13->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_13, GROUP_TYPE::INTERACTIVE);
	
	/// 완
	pWall_14 = new CWall;
	pWall_14->SetPos(Vec2(620.f, -50.f));
	pWall_14->SetScale(Vec2(10.f, 700.f));
	pWall_14->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_14, GROUP_TYPE::INTERACTIVE);


	/// 게시판
	pWall_21 = new CWall;
	pWall_21->SetPos(Vec2(-380.f, -230.f));
	pWall_21->SetScale(Vec2(1300.f, 10.f));
	pWall_21->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_21, GROUP_TYPE::INTERACTIVE);

	/// 게시판 우측 벽
	pWall_22 = new CWall;
	pWall_22->SetPos(Vec2(280.f, -320.f));
	pWall_22->SetScale(Vec2(10.f, 200.f));
	pWall_22->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_22, GROUP_TYPE::INTERACTIVE);


	///  중앙 ㅎ단 기둥?
	pWall_23 = new CWall;
	pWall_23->SetPos(Vec2(20.f, 220.f));
	pWall_23->SetScale(Vec2(650.f, 10.f));
	pWall_23->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_23, GROUP_TYPE::INTERACTIVE);


	/// end중앙 ㅎ단 기둥?
	pWall_24 = new CWall;
	pWall_24->SetPos(Vec2(300.f, 470.f));
	pWall_24->SetScale(Vec2(100.f, 500.f));
	pWall_24->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_24, GROUP_TYPE::INTERACTIVE);


	/// 중앙 ㅎ단 기둥?
	pWall_31 = new CWall;
	pWall_31->SetPos(Vec2(-260.f, 470.f));
	pWall_31->SetScale(Vec2(100.f, 500.f));
	pWall_31->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_31, GROUP_TYPE::INTERACTIVE);

	/// 탁자
	pWall_32 = new CWall;
	pWall_32->SetPos(Vec2(30.f, 0.f));
	pWall_32->SetScale(Vec2(600.f, 10.f));
	pWall_32->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_32, GROUP_TYPE::INTERACTIVE);

	/// 탁자
	pWall_33 = new CWall;
	pWall_33->SetPos(Vec2(30.f, 200.f));
	pWall_33->SetScale(Vec2(700.f, 10.f));
	pWall_33->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_33, GROUP_TYPE::INTERACTIVE);

	/// 탁자
	pWall_34 = new CWall;
	pWall_34->SetPos(Vec2(-270.f, 105.f));
	pWall_34->SetScale(Vec2(10.f, 200.f));
	pWall_34->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_34, GROUP_TYPE::INTERACTIVE);

	/// 탁자
	pWall_41 = new CWall;
	pWall_41->SetPos(Vec2(370.f, 215.f));
	pWall_41->SetScale(Vec2(50.f, 700.f));
	pWall_41->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_41, GROUP_TYPE::INTERACTIVE);

	/// 탁자 기둥
	pWall_42 = new CWall;
	pWall_42->SetPos(Vec2(310.f, -130.f));
	pWall_42->SetScale(Vec2(170.f, 20.f));
	pWall_42->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_42, GROUP_TYPE::INTERACTIVE);


	/// xkrwkrlend
	pWall_43 = new CWall;
	pWall_43->SetPos(Vec2(230.f, -30.f));
	pWall_43->SetScale(Vec2(30.f, 200.f));
	pWall_43->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_43, GROUP_TYPE::INTERACTIVE);


	


	// player
	pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(480.f, -200.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	//background
	pBackground = new CBackground;
	pBackground->SetPos(Vec2(960.f, 540.f));
	pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_LobbyTex", L"texture\\MAP\\lobby\\Background.bmp"));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//아케이드 게임
	pStaticObject_0 = new CStaticObject;
	pStaticObject_0->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[0], pObjectTexArr[0]));
	pStaticObject_0->SetTexPos(Vec2(80.f, 278.f));
	AddObject(pStaticObject_0, GROUP_TYPE::BACKGROUND);

	//랩탑
	pStaticObject_1 = new CStaticObject;
	pStaticObject_1->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[1], pObjectTexArr[1]));
	pStaticObject_1->SetTexPos(Vec2(786.f, 590.f));
	AddObject(pStaticObject_1, GROUP_TYPE::BACKGROUND);
	
	//원내게시판
	pStaticObject_2 = new CStaticObject;
	pStaticObject_2->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[2], pObjectTexArr[2]));
	pStaticObject_2->SetTexPos(Vec2(870.f, 150.f));
	AddObject(pStaticObject_2, GROUP_TYPE::INTERACTIVE);
	 
	//기둥
	pStaticObject_3 = new CStaticObject;
	pStaticObject_3->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[3], pObjectTexArr[3]));
	pStaticObject_3->SetTexPos(Vec2(1188.f, 408.f));
	AddObject(pStaticObject_3, GROUP_TYPE::BACKGROUND);
	 
	//화분1
	pStaticObject_4 = new CStaticObject;
	pStaticObject_4->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[4], pObjectTexArr[4]));
	pStaticObject_4->SetTexPos(Vec2(1246.f, 182.f));
	AddObject(pStaticObject_4, GROUP_TYPE::BACKGROUND);
	 
	//화분2
	pStaticObject_5 = new CStaticObject;
	pStaticObject_5->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[5], pObjectTexArr[5]));
	pStaticObject_5->SetTexPos(Vec2(548.f, 250.f));
	AddObject(pStaticObject_5, GROUP_TYPE::BACKGROUND);
	 
	//정수기
	pStaticObject_6 = new CStaticObject;
	pStaticObject_6->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[6], pObjectTexArr[6]));
	pStaticObject_6->SetTexPos(Vec2(660.f, 850.f));
	AddObject(pStaticObject_6, GROUP_TYPE::BACKGROUND);
	 
	//아트
	pStaticObject_7 = new CStaticObject;
	pStaticObject_7->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[7], pObjectTexArr[7]));
	pStaticObject_7->SetTexPos(Vec2(144.f, 768.f));
	AddObject(pStaticObject_7, GROUP_TYPE::INTERACTIVE);
	 
	//플밍
	pStaticObject_8 = new CStaticObject;
	pStaticObject_8->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[8], pObjectTexArr[8]));
	pStaticObject_8->SetTexPos(Vec2(488.f, 284.f));
	AddObject(pStaticObject_8, GROUP_TYPE::INTERACTIVE);
	 
	//테이블
	pStaticObject_9 = new CStaticObject;
	pStaticObject_9->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[9], pObjectTexArr[9]));
	pStaticObject_9->SetTexPos(Vec2(706.f, 550.f));
	AddObject(pStaticObject_9, GROUP_TYPE::BACKGROUND);

	//쓰레기통
	pStaticObject_10 = new CStaticObject;
	pStaticObject_10->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[10], pObjectTexArr[10]));
	pStaticObject_10->SetTexPos(Vec2(1332.f, 232.f));
	AddObject(pStaticObject_10, GROUP_TYPE::BACKGROUND);





	// exit to art
	pExit_Art = new CExit_Trigger;
	pExit_Art->SetPos(Vec2(-750.f, 380.f));
	pExit_Art->SetNextScene(SCENE_TYPE::ART); // SCENE_TYPE::ART
	AddObject(pExit_Art, GROUP_TYPE::INTERACTIVE);

	// exit to pm
	pExit_PM = new CExit_Trigger;
	//pExit_PM->SetPos(Vec2(-520.f, -280.f));
	pExit_PM->SetPos(Vec2(-550.f, -290.f));
	pExit_PM->SetNextScene(SCENE_TYPE::PM); // SCENE_TYPE::PM
	AddObject(pExit_PM, GROUP_TYPE::INTERACTIVE);

	// exit to room
	pExit_ROOM = new CExit_Trigger;
	pExit_ROOM->SetPos(Vec2(520.f, -350.f));
	pExit_ROOM->SetNextScene(SCENE_TYPE::ROOM); // SCENE_TYPE::ELEV
	AddObject(pExit_ROOM, GROUP_TYPE::INTERACTIVE);

	// exit to elev
	// CExit_Trigger* pExit_ELEV = new CExit_Trigger;
	// pExit_ELEV->SetPos(Vec2(320.f, 600.f));
	// pExit_ELEV->SetNextScene(SCENE_TYPE::ENDING); // SCENE_TYPE::ELEV
	// AddObject(pExit_ELEV, GROUP_TYPE::INTERACTIVE);

	// puzzle - clock
	pPuzzle_Clock = new CInteractive;
	pPuzzle_Clock->SetPos(Vec2(-130.f, 80.f));
	pPuzzle_Clock->SetScale(Vec2(150.f, 200.f));
	/*pPuzzle_Clock->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	pPuzzle_Clock->SetType(INTERACTIVE_TYPE::PUZZLE_DS);
	AddObject(pPuzzle_Clock, GROUP_TYPE::INTERACTIVE);
	
	// interactive - infinite
	pInfinite1 = new CInteractive;
	pInfinite1->SetPos(Vec2(-300.f, -200.f));
	pInfinite1->SetScale(Vec2(100.f, 100.f));
	pInfinite1->SetType(INTERACTIVE_TYPE::TEXTBOX);
	pInfinite1->SetTextCount(1);
	pInfinite1->SetText(L"아무 반응이 없다.");
	AddObject(pInfinite1, GROUP_TYPE::INTERACTIVE);

	// 원내 게시판
	pInfinite = new CInteractive;
	pInfinite->SetPos(Vec2(100.f, -200.f));
	pInfinite->SetScale(Vec2(100.f, 100.f));
	pInfinite->SetType(INTERACTIVE_TYPE::TEXTBOX);
	pInfinite->SetTextCount(1);
	//pInfinite->Set
	pInfinite->SetText(L"원내 게시판에 무언가 쓰여있는 것 같다.");
	AddObject(pInfinite, GROUP_TYPE::INTERACTIVE);

	// collision
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

	// first == false
	GameManager::GetInst()->SetSceneFirst(SCENE_TYPE::LOBBY, false);
}

void CScene_Lobby::SecondEnter()
{
	Camera::GetInst()->FadeIn(3.f);
	
	switch (GameManager::GetInst()->GetPreScene())
	{
		case SCENE_TYPE::ROOM:
		{
			pPlayer->SetPos(Vec2(480.f, -200.f));
			break;
		}
		case SCENE_TYPE::ART:
		{
			pPlayer->SetPos(Vec2(-600.f, 380.f));
			
			break;
		}
		case SCENE_TYPE::PM:
		{
			pPlayer->SetPos(Vec2(-320.f, -200.f));
			
			SoundManager::GetInst()->stopBGM();

			SoundManager::GetInst()->playBGM(BGM::SheDiedUp);

			break;
		}
	}

	
	pWall_1->SetPos(Vec2(0.f, -270.f));
	pWall_2->SetPos(Vec2(0.f, 500.f));
	/// 가장 좌측 큰 벽
	pWall_3->SetPos(Vec2(-670.f, -180.f));

	pWall_4->SetPos(Vec2(580.f, 70.f));
	pWall_44->SetPos(Vec2(-730.f, 50.f));

	/// 오른쪽 벽들

	/// 완 엘베 앞
	pWall_11->SetPos(Vec2(770.f, 280.f));

	/// 완
	pWall_12->SetPos(Vec2(650.f, -150.f));

	/// 완 최 우측 엘베 앞 벽
	pWall_13->SetPos(Vec2(830.f, 0.f));

	/// 완
	pWall_14->SetPos(Vec2(620.f, -50.f));


	/// 게시판
	pWall_21->SetPos(Vec2(-380.f, -230.f));

	/// 게시판 우측 벽
	pWall_22->SetPos(Vec2(280.f, -320.f));


	///  중앙 ㅎ단 기둥?
	pWall_23->SetPos(Vec2(20.f, 220.f));


	/// end중앙 ㅎ단 기둥?
	pWall_24->SetPos(Vec2(300.f, 470.f));


	/// 중앙 ㅎ단 기둥?
	pWall_31->SetPos(Vec2(-260.f, 470.f));

	/// 탁자
	pWall_32->SetPos(Vec2(30.f, 0.f));

	/// 탁자
	pWall_33->SetPos(Vec2(30.f, 200.f));

	/// 탁자
	pWall_34->SetPos(Vec2(-320.f, 105.f));

	/// 탁자
	pWall_41->SetPos(Vec2(370.f, 215.f));

	/// 탁자 기둥
	pWall_42->SetPos(Vec2(310.f, -130.f));


	/// xkrwkrlend
	pWall_43->SetPos(Vec2(230.f, -30.f));


	/// 콜라이더 렌더 확인용 - 기능 없음
	//pWall_43->SetPos(Vec2(230.f, -30.f));

	pExit_Art->SetPos(Vec2(-750.f, 380.f));


	pExit_PM->SetPos(Vec2(-550.f, -290.f));
	pExit_ROOM->SetPos(Vec2(520.f, -350.f));
	pPuzzle_Clock->SetPos(Vec2(-130.f, 80.f));
	pInfinite1->SetPos(Vec2(-300.f, -200.f));
	pInfinite->SetPos(Vec2(100.f, -200.f));
	pBackground->SetPos(Vec2(960.f, 540.f));


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);
}

void CScene_Lobby::Enter()
{
	GameManager::GetInst()->SetMovable(true);
	GameManager::GetInst()->SetCurScene(SCENE_TYPE::LOBBY);

	if (GameManager::GetInst()->GetSceneFirst(SCENE_TYPE::LOBBY))
	{
		FirstEnter();
		return;
	}
	else
	{
		SecondEnter();
	}

}

void CScene_Lobby::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	GameManager::GetInst()->SetPreScene(SCENE_TYPE::LOBBY);
}
