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

	////Background �߰�
	//CBackground* pBackground = new CBackground;
	//pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BackgroundTex", L"texture\\Background.bmp"));
	//pBackground->SetPos(Vec2(960.f, 540.f));
	//AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	//// Object �߰�
	//CObject* pObj = new CPlayer;
	////pObj->SetPos(Vec2(640.f, 384.f));
	////pObj->SetScale(Vec2(100.f, 100.f));
	//AddObject(pObj, GROUP_TYPE::PLAYER);


	//// ��ȣ�ۿ� ��ü �߰� - �� ...  �ٵ� �굵 �׷�Ÿ�� ���� ��Ű�°���?
	//CExit_Trigger* pIntObj3 = new CExit_Trigger;
	//pIntObj3->SetPos(Vec2(600.f, 600.f));
	//pIntObj3->SetNextScene(SCENE_TYPE::LOBBY);
	//AddObject(pIntObj3, GROUP_TYPE::INTERACTIVE);

	//// ��ȣ�ۿ� ��ü �߰� - �����Է� ����
	//CInteractive* pIntObj = new CInteractive;
	//pIntObj->SetPos(Vec2(-100.f, 384.f));
	//pIntObj->SetScale(Vec2(100.f, 100.f));
	//pIntObj->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj->SetType(INTERACTIVE_TYPE::PUZZLE_DOORLOCK);
	//pIntObj->SetTextCount(2);
	//pIntObj->SetText(L"�̰��� ���ڿ� <1> ��° �Է°��Դϴ� ������ ���ڿ��� ���� ������ ���� �ѹ� ���ôٿ� ������������������", L"�̰��� ���ڿ� <2> ��° �Է°��Դϴ� ���� �Ѿ�� �ȳѾ�� ���ڿ��� ���� ������ ���� �ѹ� ���ôٿ� ������������������, ");
	//// �̰Ŵ� ó������ ��ȣ�ۿ��� ���ϴ� �ֵ�����
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);
	//AddObject(pIntObj, GROUP_TYPE::INTERACTIVE);

	//// ��ȣ�ۿ� ��ü �߰� - ��������
	//CInteractive* pIntObj2 = new CInteractive;
	//pIntObj2->SetPos(Vec2(500.f, 100.f));
	//pIntObj2->SetScale(Vec2(100.f, 100.f));
	//pIntObj2->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj2->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	//pIntObj2->SetFramenum(0);
	//AddObject(pIntObj2, GROUP_TYPE::INTERACTIVE);


	//// ��ȣ�ۿ� ��ü �߰� - ��������2
	//CInteractive* pIntObj4 = new CInteractive;
	//pIntObj4->SetPos(Vec2(500.f, -100.f));
	//pIntObj4->SetScale(Vec2(100.f, 100.f));
	//pIntObj4->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));
	//pIntObj4->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	//pIntObj4->SetFramenum(1);
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);
	//AddObject(pIntObj4, GROUP_TYPE::INTERACTIVE);

	//// ��ǻ�� ������Ʈ!
	//CComputer* pComputer = new CComputer;
	//pComputer->SetPos(Vec2(-400.f, -100.f));
	//pComputer->SetScale(Vec2(100.f, 100.f));
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::COMPUTER, true);
	//AddObject(pComputer, GROUP_TYPE::INTERACTIVE);

	//// ��ȣ�ۿ� ��ü �߰� - �κ� �ð� ����(��ȹ ���� ��ü)
	//CInteractive* pIntObj5 = new CInteractive;
	//pIntObj5->SetPos(Vec2(100.f, 100.f));
	//pIntObj5->SetScale(Vec2(100.f, 100.f));
	//pIntObj5->SetType(INTERACTIVE_TYPE::PUZZLE_DS);
	//AddObject(pIntObj5, GROUP_TYPE::INTERACTIVE);
	////GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, true);
	//pIntObj5->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));

	//// ���� ��ġ
	//int iMonsterCount = 2;
	//float fMoveDist = 25.f;
	//float fObjScale = 50.f;

	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonsterCount - 1);

	//CMonster* pMonsterObj = nullptr;

	//for (int i = 0; i < iMonsterCount; ++i)
	//{
	//	// Monster Object �߰�
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
	//	pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//	pMonsterObj->SetMoveDistance(fMoveDist);
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}

	//// �浹 ����
	//// Player �׷�� Monster �׷� ���� �浹üũ
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER); 
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

	//// ī�޶� FADE IN
	//Camera::GetInst()->FadeIn(3.f);

	//// ������� ���
	//SoundManager::GetInst()->playBGM(BGM::testBGM);

}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	SoundManager::GetInst()->stopBGM();

	// ī�޶� FADE OUT -> �ٵ� ���⼭ ȣ���ص� ������ �Ǵ��� �𸣰ڴ�
	// Exit �Ŀ��� ���� ������ ������ �ȵǴ� ����

	// ������� ���߱� (�����ϴ°� ������ ���� ������ �ٸ� ���� ����ϱ� ���� �ϴ°� ������)
}
