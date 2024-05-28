#include "pch.h"
#include "CScene_Start.h"

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
#include "CComputer.h"




CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	
	// player
	CObject* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(200.f, -100.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// computer
	CComputer* pComputer = new CComputer;
	pComputer->SetPos(Vec2(-200.f, 0.f));
	pComputer->SetScale(Vec2(400.f, 200.f));
	AddObject(pComputer, GROUP_TYPE::INTERACTIVE);
	GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::PM, true);

	////Background 추가
	//CBackground* pBackground = new CBackground;
	//pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BackgroundTex", L"texture\\Background.bmp"));
	//pBackground->SetPos(Vec2(960.f, 540.f));
	//AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//// Object 추가
	//CObject* pObj = new CPlayer;
	////pObj->SetPos(Vec2(640.f, 384.f));
	////pObj->SetScale(Vec2(100.f, 100.f));
	//AddObject(pObj, GROUP_TYPE::PLAYER);


	//// 상호작용 물체 추가 - 문 ...  근데 얘도 그룹타입 통일 시키는건지?
	//CExit_Trigger* pIntObj3 = new CExit_Trigger;
	//pIntObj3->SetPos(Vec2(600.f, 600.f));
	//pIntObj3->SetNextScene(SCENE_TYPE::LOBBY);
	//AddObject(pIntObj3, GROUP_TYPE::INTERACTIVE);

	//// 상호작용 물체 추가 - 숫자입력 퍼즐
	//CInteractive* pIntObj = new CInteractive;
	//pIntObj->SetPos(Vec2(-100.f, 384.f));
	//pIntObj->SetScale(Vec2(100.f, 100.f));
	//pIntObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj->SetType(INTERACTIVE_TYPE::PUZZLE_DOORLOCK);
	//pIntObj->SetTextCount(2);
	//pIntObj->SetText(L"이것은 문자열 <1> 번째 입력값입니다 마지막 문자열의 끝이 어디까지 가나 한번 봅시다요 하하하하하하하하하", L"이것은 문자열 <2> 번째 입력값입니다 과연 넘어가나 안넘어가나 문자열의 끝이 어디까지 가나 한번 봅시다요 하하하하하하하하하, ");
	//// 이거는 처음부터 상호작용은 못하는 애들한테
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);
	//AddObject(pIntObj, GROUP_TYPE::INTERACTIVE);

	//// 상호작용 물체 추가 - 액자퍼즐
	//CInteractive* pIntObj2 = new CInteractive;
	//pIntObj2->SetPos(Vec2(500.f, 100.f));
	//pIntObj2->SetScale(Vec2(100.f, 100.f));
	//pIntObj2->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj2->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	//pIntObj2->SetFramenum(0);
	//AddObject(pIntObj2, GROUP_TYPE::INTERACTIVE);


	//// 상호작용 물체 추가 - 액자퍼즐2
	//CInteractive* pIntObj4 = new CInteractive;
	//pIntObj4->SetPos(Vec2(500.f, -100.f));
	//pIntObj4->SetScale(Vec2(100.f, 100.f));
	//pIntObj4->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj4->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	//pIntObj4->SetFramenum(1);
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);
	//AddObject(pIntObj4, GROUP_TYPE::INTERACTIVE);

	//// 컴퓨터 오브젝트!
	//CComputer* pComputer = new CComputer;
	//pComputer->SetPos(Vec2(-400.f, -100.f));
	//pComputer->SetScale(Vec2(100.f, 100.f));
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::COMPUTER, true);
	//AddObject(pComputer, GROUP_TYPE::INTERACTIVE);

	//// 상호작용 물체 추가 - 로비 시계 퍼즐(기획 퍼즐 대체)
	//CInteractive* pIntObj5 = new CInteractive;
	//pIntObj5->SetPos(Vec2(100.f, 100.f));
	//pIntObj5->SetScale(Vec2(100.f, 100.f));
	//pIntObj5->SetType(INTERACTIVE_TYPE::PUZZLE_DS);
	//AddObject(pIntObj5, GROUP_TYPE::INTERACTIVE);
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, true);
	//pIntObj5->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));

	//// 몬스터 배치
	//int iMonsterCount = 2;
	//float fMoveDist = 25.f;
	//float fObjScale = 50.f;

	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonsterCount - 1);

	//CMonster* pMonsterObj = nullptr;

	//for (int i = 0; i < iMonsterCount; ++i)
	//{
	//	// Monster Object 추가
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
	//	pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//	pMonsterObj->SetMoveDistance(fMoveDist);
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}

	//// 충돌 지정
	//// Player 그룹과 Monster 그룹 간의 충돌체크
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER); 
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

	//// 카메라 FADE IN
	//Camera::GetInst()->FadeIn(3.f);

	//// 배경음악 재생
	//SoundManager::GetInst()->playBGM(BGM::testBGM);

}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	SoundManager::GetInst()->stopBGM();

	// 카메라 FADE OUT -> 근데 여기서 호출해도 렌더가 되는지 모르겠다
	// Exit 후에는 씬의 업뎃과 렌더가 안되는 상태

	// 배경음악 멈추기 (여기하는게 좋을지 다음 씬에서 다른 음악 재생하기 전에 하는게 좋을지)
}
