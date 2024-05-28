#include "pch.h"
#include "CScene_PM.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CCollisionMgr.h"

#include "CBackground.h"

#include "Camera.h"
#include "SoundManager.h"

#include "CInteractive.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "GameManager.h"

#include "CExit_Trigger.h"
#include "CWall.h"
#include "CComputer.h"

#include "CStaticObject.h"

#include "CProgrammingNPC.h"
#include "CAnimator.h"


CScene_PM::CScene_PM()
	:pBackground{}, pPlayer{}, pExit_LOBBY{}, pPuzzle{}
	, pWall_1{}, pWall_2{}, pWall_3{}, pWall_4{}
	, m_pProgrammingNPC(nullptr)
{
	// 애니메이션 없는 오브젝트 키 값 & 경로
	pObjectKeyArr[0] = L"PM_TablesTex";
	pObjectKeyArr[1] = L"PM_Npc1Tex";
	pObjectKeyArr[2] = L"PM_Npc2Tex";
	pObjectKeyArr[3] = L"PM_Npc3Tex";
	pObjectKeyArr[4] = L"PM_ProfessorTableTex";

	pObjectTexArr[0] = L"texture\\MAP\\programming_class\\Tables.bmp";
	pObjectTexArr[1] = L"texture\\MAP\\programming_class\\npc1.bmp";
	pObjectTexArr[2] = L"texture\\MAP\\programming_class\\npc2.bmp";
	pObjectTexArr[3] = L"texture\\MAP\\programming_class\\npc3.bmp";
	pObjectTexArr[4] = L"texture\\MAP\\programming_class\\ProfessorTable.bmp";

	m_pProgrammingNPC = new CProgrammingNPC;
	AddObject(m_pProgrammingNPC, GROUP_TYPE::INTERACTIVE);
}

CScene_PM::~CScene_PM()
{
}

void CScene_PM::Enter()
{
	GameManager::GetInst()->SetMovable(true);
	GameManager::GetInst()->SetCurScene(SCENE_TYPE::PM);



	if (GameManager::GetInst()->GetSceneFirst(SCENE_TYPE::PM))
	{
		FirstEnter();
		return;
	}
	else
	{
		SecondEnter();
	}
}

void CScene_PM::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	GameManager::GetInst()->SetPreScene(SCENE_TYPE::PM);
}

void CScene_PM::FirstEnter()
{
	// camera
	Camera::GetInst()->FadeIn(3.f);

	// sound
	SoundManager::GetInst()->stopBGM();
	SoundManager::GetInst()->playBGM(BGM::GaiaInFog);

	pWall_1 = new CWall;
	pWall_1->SetPos(Vec2(0.f, -300.f));
	pWall_1->SetScale(Vec2(2000.f, 10.f));
	pWall_1->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_1, GROUP_TYPE::INTERACTIVE);

	pWall_2 = new CWall;
	pWall_2->SetPos(Vec2(0.f, 480.f));

	pWall_2->SetScale(Vec2(2000.f, 10.f));
	pWall_2->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_2, GROUP_TYPE::INTERACTIVE);

	pWall_3 = new CWall;
	pWall_3->SetPos(Vec2(-700.f, 0.f));
	pWall_3->SetScale(Vec2(10.f, 1000.f));
	pWall_3->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_3, GROUP_TYPE::INTERACTIVE);

	pWall_4 = new CWall;
	pWall_4->SetPos(Vec2(700.f, 0.f));
	pWall_4->SetScale(Vec2(10.f, 1000.f));
	pWall_4->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_4, GROUP_TYPE::INTERACTIVE);

	// 모둠책상 1
	pWall_21 = new CWall;
	pWall_21->SetPos(Vec2(345.f, 150.f));
	pWall_21->SetScale(Vec2(570.f, 100.f));
	pWall_21->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_21, GROUP_TYPE::INTERACTIVE);

	pWall_22 = new CWall;
	pWall_22->SetPos(Vec2(345.f, -200.f));
	pWall_22->SetScale(Vec2(570.f, 100.f));
	pWall_22->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_22, GROUP_TYPE::INTERACTIVE);

	pWall_23 = new CWall;
	pWall_23->SetPos(Vec2(590.f, -140.f));
	pWall_23->SetScale(Vec2(100.f, 670.f));
	pWall_23->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_23, GROUP_TYPE::INTERACTIVE);

	pWall_24 = new CWall;
	pWall_24->SetPos(Vec2(100.f, -140.f));
	pWall_24->SetScale(Vec2(100.f, 670.f));
	pWall_24->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_24, GROUP_TYPE::INTERACTIVE);

	// 모둠책상 2
	pWall_11 = new CWall;
	pWall_11->SetPos(Vec2(-345.f, 150.f));
	pWall_11->SetScale(Vec2(570.f, 100.f));
	pWall_11->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_11, GROUP_TYPE::INTERACTIVE);

	pWall_12 = new CWall;
	pWall_12->SetPos(Vec2(-345.f, -200.f));
	pWall_12->SetScale(Vec2(570.f, 100.f));
	pWall_12->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_12, GROUP_TYPE::INTERACTIVE);

	pWall_13 = new CWall;
	pWall_13->SetPos(Vec2(-590.f, -140.f));
	pWall_13->SetScale(Vec2(100.f, 670.f));
	pWall_13->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_13, GROUP_TYPE::INTERACTIVE);

	pWall_14 = new CWall;
	pWall_14->SetPos(Vec2(-100.f, -140.f));
	pWall_14->SetScale(Vec2(100.f, 670.f));
	pWall_14->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_14, GROUP_TYPE::INTERACTIVE);


	// 상호작용 모니터 용 (레이어 상 아래서만 상호작용 가능)
	pWall_31 = new CWall;
	pWall_31->SetPos(Vec2(-345.f, 395.f));
	pWall_31->SetScale(Vec2(200.f, 50.f));
	pWall_31->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_31, GROUP_TYPE::INTERACTIVE);

	pWall_32 = new CWall;
	pWall_32->SetPos(Vec2(-345.f, 310.f));
	pWall_32->SetScale(Vec2(200.f, 50.f));
	pWall_32->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_32, GROUP_TYPE::INTERACTIVE);

	pWall_33 = new CWall;
	pWall_33->SetPos(Vec2(-265.f, 340.f));
	pWall_33->SetScale(Vec2(50.f, 100.f));
	pWall_33->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_33, GROUP_TYPE::INTERACTIVE);

	pWall_34 = new CWall;
	pWall_34->SetPos(Vec2(-425.f, 340.f));
	pWall_34->SetScale(Vec2(50.f, 100.f));
	pWall_34->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_34, GROUP_TYPE::INTERACTIVE);


	//background
	pBackground = new CBackground;
	pBackground->SetPos(Vec2(960.f, 540.f));
	pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_PMTex", L"texture\\MAP\\programming_class\\Programming_Background.bmp"));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//학생들 책상
	pStaticObject_0 = new CStaticObject;
	pStaticObject_0->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[0], pObjectTexArr[0]));
	pStaticObject_0->SetTexPos(Vec2(342.f, 214.f));
	AddObject(pStaticObject_0, GROUP_TYPE::BACKGROUND);

	//npc1
	pStaticObject_1 = new CStaticObject;
	pStaticObject_1->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[1], pObjectTexArr[1]));
	pStaticObject_1->SetTexPos(Vec2(1284.f, 170.f));
	AddObject(pStaticObject_1, GROUP_TYPE::BACKGROUND);

	//npc2
	pStaticObject_2 = new CStaticObject;
	pStaticObject_2->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[2], pObjectTexArr[2]));
	pStaticObject_2->SetTexPos(Vec2(722.f, 214.f));
	AddObject(pStaticObject_2, GROUP_TYPE::BACKGROUND);

	//npc3
	pStaticObject_3 = new CStaticObject;
	pStaticObject_3->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[3], pObjectTexArr[3]));
	pStaticObject_3->SetTexPos(Vec2(384.f, 160.f));
	AddObject(pStaticObject_3, GROUP_TYPE::BACKGROUND);

	//교수님 책상
	pStaticObject_4 = new CStaticObject;
	pStaticObject_4->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[4], pObjectTexArr[4]));
	pStaticObject_4->SetTexPos(Vec2(530.f, 834.f));
	AddObject(pStaticObject_4, GROUP_TYPE::BACKGROUND);


	// Programming NPC 출력
	// 하...왜안되죠? 전 최선을 다했습니다진짜 ㄴ미ㅏㅓㅎ냉ㅁ핸머ㅑㄴ애ㅏ
	m_pProgrammingNPC->GetAnimator()->Play(L"ProgrammingNPC", false);
	m_pProgrammingNPC->SetTexPos(Vec2(804.f, 476.f));


	// player
	pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(-620.f, 350.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// exit to lobby
	pExit_LOBBY = new CExit_Trigger;
	pExit_LOBBY->SetPos(Vec2(-565.f, 565.f));
	pExit_LOBBY->SetNextScene(SCENE_TYPE::LOBBY);
	AddObject(pExit_LOBBY, GROUP_TYPE::INTERACTIVE);

	// interactive - puzzle
	pPuzzle = new CInteractive;
	pPuzzle->SetPos(Vec2(-344.f, 380.f));
	pPuzzle->SetScale(Vec2(400.f, 200.f));
	/*pPuzzle->SetTexture(CResMgr::GetInst()->LoadTexture(L"PuzzleABCTex", L"texture\\penguin.bmp"));*/
	pPuzzle->SetType(INTERACTIVE_TYPE::PUZZLE_PM);
	AddObject(pPuzzle, GROUP_TYPE::INTERACTIVE);

	// interactive - student
	pStudent_0 = new CInteractive;
	pStudent_0->SetPos(Vec2(-330.f, 170.f));
	pStudent_0->SetScale(Vec2(300.f, 100.f));
	pStudent_0->SetType(INTERACTIVE_TYPE::TEXTBOX);
	pStudent_0->SetTextCount(1);
	pStudent_0->SetText(L"00010101010010101110101000.....%$%^\n$%$#%^........001011110111011");
	AddObject(pStudent_0, GROUP_TYPE::INTERACTIVE);

	pStudent_1 = new CInteractive;
	pStudent_1->SetPos(Vec2(-180.f, 0.f));
	pStudent_1->SetScale(Vec2(300.f, 100.f));
	pStudent_1->SetType(INTERACTIVE_TYPE::TEXTBOX);
	pStudent_1->SetTextCount(1);
	pStudent_1->SetText(L"10010110010111010101010101010101001");
	AddObject(pStudent_1, GROUP_TYPE::INTERACTIVE);

	pStudent_2 = new CInteractive;
	pStudent_2->SetPos(Vec2(370.f, 130.f));
	pStudent_2->SetScale(Vec2(100.f, 200.f));
	pStudent_2->SetType(INTERACTIVE_TYPE::TEXTBOX);
	pStudent_2->SetTextCount(1);
	pStudent_2->SetText(L"000101010100.....%$%^\n$%$#%^........001011110111011");
	AddObject(pStudent_2, GROUP_TYPE::INTERACTIVE);

	// collision
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

	// first == false
	GameManager::GetInst()->SetSceneFirst(SCENE_TYPE::PM, false);
}

void CScene_PM::SecondEnter()
{
	pWall_1->SetPos(Vec2(0.f, -300.f));
	pWall_2->SetPos(Vec2(0.f, 480.f));
	pWall_3->SetPos(Vec2(-700.f, 0.f));
	pWall_4->SetPos(Vec2(700.f, 0.f));
	pWall_21->SetPos(Vec2(345.f, 150.f));

	pWall_22->SetPos(Vec2(345.f, -200.f));
	pWall_23->SetPos(Vec2(590.f, -140.f));
	pWall_24->SetPos(Vec2(100.f, -140.f));
	pWall_11->SetPos(Vec2(-345.f, 150.f));
	pWall_12->SetPos(Vec2(-345.f, -200.f));
	pWall_13->SetPos(Vec2(-590.f, -140.f));
	pWall_14->SetPos(Vec2(-100.f, -140.f));


	// 상호작용 모니터 용 (레이어 상 아래서만 상호작용 가능)
	pWall_31->SetPos(Vec2(-345.f, 395.f));
	pWall_32->SetPos(Vec2(-345.f, 310.f));
	pWall_33->SetPos(Vec2(-265.f, 340.f));
	pWall_34->SetPos(Vec2(-425.f, 340.f));

	pBackground->SetPos(Vec2(960.f, 540.f));
	pPlayer->SetPos(Vec2(640.f, 400.f));
	pExit_LOBBY->SetPos(Vec2(600.f, 550.f));
	pPuzzle->SetPos(Vec2(-400.f, 250.f));

	m_pProgrammingNPC->GetAnimator()->Play(L"ProgrammingNPC", false);
	m_pProgrammingNPC->SetTexPos(Vec2(804.f, 476.f));

	//m_pProgrammingNPC->GetAnimator()->Play(L"ProgrammingNPC", false);
	//m_pProgrammingNPC->SetTexPos(Vec2(804.f, 476.f));

	// player
	pPlayer->SetPos(Vec2(-620.f, 350.f));
	// exit to lobby
	pExit_LOBBY->SetPos(Vec2(-565.f, 565.f));

	// interactive - puzzle
	pPuzzle->SetPos(Vec2(-344.f, 370.f));
	pStudent_0->SetPos(Vec2(180.f, 0.f));
	pStudent_1->SetPos(Vec2(-180.f, 0.f));
	pStudent_2->SetPos(Vec2(370.f, 130.f));



	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

}
