#include "pch.h"
#include "CScene_ART.h"

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

#include "CStaticObject.h"

CScene_ART::CScene_ART()
	: pBackground{},pPlayer{},pExit_LOBBY{}
	, frame_0{},frame_1{},frame_2{},frame_3{}
	, pWall_1{}, pWall_2{}, pWall_3{}, pWall_4{}

{
	//아트반 상호작용 전 
	pObjectKeyArr[0] = L"ART_Desk1Tex";
	pObjectKeyArr[1] = L"ART_Desk2Tex";
	pObjectKeyArr[2] = L"ART_Npc1Tex";
	pObjectKeyArr[3] = L"ART_Npc2Tex";
	pObjectKeyArr[4] = L"ART_ImgLayoutTex";
	pObjectKeyArr[5] = L"ART_CImgTex";
	pObjectKeyArr[6] = L"ART_MImgTex";
	pObjectKeyArr[7] = L"ART_QRImgTex";
	pObjectKeyArr[8] = L"ART_YImgTex";
	pObjectKeyArr[9] = L"ART_KImgTex";
	
	pObjectTexArr[0] = L"texture\\MAP\\art_class\\Art_Prev\\Tables_L.bmp";
	pObjectTexArr[1] = L"texture\\MAP\\art_class\\Art_Prev\\Tables_R.bmp";
	pObjectTexArr[2] = L"texture\\MAP\\art_class\\Art_Prev\\npc1.bmp";
	pObjectTexArr[3] = L"texture\\MAP\\art_class\\Art_Prev\\npc2.bmp";
	pObjectTexArr[4] = L"texture\\MAP\\art_class\\Art_Prev\\TVs,Frames.bmp";
	pObjectTexArr[5] = L"texture\\MAP\\art_class\\Art_Prev\\K.bmp";
	pObjectTexArr[6] = L"texture\\MAP\\art_class\\Art_Prev\\K.bmp";
	pObjectTexArr[7] = L"texture\\MAP\\art_class\\Art_Prev\\QR.bmp";
	pObjectTexArr[8] = L"texture\\MAP\\art_class\\Art_Prev\\K.bmp";
	pObjectTexArr[9] = L"texture\\MAP\\art_class\\Art_Prev\\K.bmp";

	//아트반 상호작용 후
	pObjectKeyArr[10] = L"ART2_Desk1Tex";
	pObjectKeyArr[11] = L"ART2_Desk2Tex";
	pObjectKeyArr[12] = L"ART2_ImgLayoutTex";
	pObjectKeyArr[13] = L"ART2_ScreensTex";
	pObjectKeyArr[14] = L"ART2_BloodFilterTex";

	pObjectTexArr[10] = L"texture\\MAP\\art_class\\Art_Compelete\\Tables_L.bmp";
	pObjectTexArr[11] = L"texture\\MAP\\art_class\\Art_Compelete\\Tables_R.bmp";
	pObjectTexArr[12] = L"texture\\MAP\\art_class\\Art_Compelete\\Item.bmp";
	pObjectTexArr[13] = L"texture\\MAP\\art_class\\Art_Compelete\\Screens.bmp";
	pObjectTexArr[14] = L"texture\\MAP\\art_class\\Art_Compelete\\blood_Filter.bmp";
}

CScene_ART::~CScene_ART()
{
}

void CScene_ART::Enter()
{
	GameManager::GetInst()->SetMovable(true);
	GameManager::GetInst()->SetCurScene(SCENE_TYPE::ART);

	

	if (GameManager::GetInst()->GetSceneFirst(SCENE_TYPE::ART))
	{
		FirstEnter();
		return;
	}
	else
	{
		SecondEnter();
	}
}

void CScene_ART::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	GameManager::GetInst()->SetPreScene(SCENE_TYPE::ART);
}

void CScene_ART::FirstEnter()
{

	// camera
	Camera::GetInst()->FadeIn(3.f);

	SoundManager::GetInst()->stopBGM();
	SoundManager::GetInst()->playBGM(BGM::Kindergarden);
	
	pWall_1 = new CWall;
	pWall_1->SetPos(Vec2(0.f, -300.f));
	pWall_1->SetScale(Vec2(2000.f, 10.f));
	pWall_1->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_1, GROUP_TYPE::INTERACTIVE);

	pWall_2 = new CWall;
	pWall_2->SetPos(Vec2(0.f, 500.f));

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
	pWall_21->SetPos(Vec2(325.f, 300.f));
	pWall_21->SetScale(Vec2(570.f, 100.f));
	pWall_21->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_21, GROUP_TYPE::INTERACTIVE);

	pWall_22 = new CWall;
	pWall_22->SetPos(Vec2(345.f, -130.f));
	pWall_22->SetScale(Vec2(570.f, 100.f));
	pWall_22->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_22, GROUP_TYPE::INTERACTIVE);

	pWall_23 = new CWall;
	pWall_23->SetPos(Vec2(570.f, 100.f));
	pWall_23->SetScale(Vec2(100.f, 470.f));
	pWall_23->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_23, GROUP_TYPE::INTERACTIVE);

	pWall_24 = new CWall;
	pWall_24->SetPos(Vec2(100.f, 100.f));
	pWall_24->SetScale(Vec2(100.f, 470.f));
	pWall_24->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_24, GROUP_TYPE::INTERACTIVE);

	// 모둠책상 2
	pWall_11 = new CWall;
	pWall_11->SetPos(Vec2(-345.f, 300.f));
	pWall_11->SetScale(Vec2(570.f, 100.f));
	pWall_11->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_11, GROUP_TYPE::INTERACTIVE);

	pWall_12 = new CWall;
	pWall_12->SetPos(Vec2(-345.f, -130.f));
	pWall_12->SetScale(Vec2(570.f, 100.f));
	pWall_12->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_12, GROUP_TYPE::INTERACTIVE);

	pWall_13 = new CWall;
	pWall_13->SetPos(Vec2(-590.f, 100.f));
	pWall_13->SetScale(Vec2(100.f, 470.f));
	pWall_13->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_13, GROUP_TYPE::INTERACTIVE);

	pWall_14 = new CWall;
	pWall_14->SetPos(Vec2(-100.f, 100.f));
	pWall_14->SetScale(Vec2(100.f, 470.f));
	pWall_14->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_14, GROUP_TYPE::INTERACTIVE);

	// 모니터
	pWall_31 = new CWall;
	pWall_31->SetPos(Vec2(-405.f, -100.f));
	pWall_31->SetScale(Vec2(200.f, 50.f));
	pWall_31->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_31, GROUP_TYPE::INTERACTIVE);

	pWall_32 = new CWall;
	pWall_32->SetPos(Vec2(-405.f, -210.f));
	pWall_32->SetScale(Vec2(200.f, 50.f));
	pWall_32->SetType(COLLIDER_DIR::BOTTOM);
	AddObject(pWall_32, GROUP_TYPE::INTERACTIVE);

	pWall_33 = new CWall;
	pWall_33->SetPos(Vec2(-475.f, -120.f));
	pWall_33->SetScale(Vec2(50.f, 200.f));
	pWall_33->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_33, GROUP_TYPE::INTERACTIVE);

	pWall_34 = new CWall;
	pWall_34->SetPos(Vec2(-335.f, -120.f));
	pWall_34->SetScale(Vec2(50.f, 200.f));
	pWall_34->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_34, GROUP_TYPE::INTERACTIVE);

	// 양 사이드 학생 막기
	pWall_35 = new CWall;
	pWall_35->SetPos(Vec2(-620.f, -350.f));
	pWall_35->SetScale(Vec2(50.f, 200.f));
	pWall_35->SetType(COLLIDER_DIR::LEFT);
	AddObject(pWall_35, GROUP_TYPE::INTERACTIVE);

	pWall_36 = new CWall;
	pWall_36->SetPos(Vec2(635.f, -350.f));
	pWall_36->SetScale(Vec2(50.f, 200.f));
	pWall_36->SetType(COLLIDER_DIR::RIGHT);
	AddObject(pWall_36, GROUP_TYPE::INTERACTIVE);
	
	pWall_37 = new CWall;
	pWall_37->SetPos(Vec2(-635.f, -250.f));
	pWall_37->SetScale(Vec2(50.f, 100.f));
	pWall_37->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_37, GROUP_TYPE::INTERACTIVE);

	pWall_38 = new CWall;
	pWall_38->SetPos(Vec2(655.f, -250.f));
	pWall_38->SetScale(Vec2(50.f, 100.f));
	pWall_38->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_38, GROUP_TYPE::INTERACTIVE);

	pWall_38 = new CWall;
	pWall_38->SetPos(Vec2(655.f, -250.f));
	pWall_38->SetScale(Vec2(50.f, 100.f));
	pWall_38->SetType(COLLIDER_DIR::TOP);
	AddObject(pWall_38, GROUP_TYPE::INTERACTIVE);



	//background
	pBackground = new CBackground;
	pBackground->SetPos(Vec2(960.f, 540.f));
	pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_ArtTex", L"texture\\MAP\\art_class\\Art_Prev\\Art_Background_1.bmp"));
	AddObject(pBackground, GROUP_TYPE::BACKGROUND);

	
	//학생들 책상1 (좌)
	pStaticObject_0 = new CStaticObject;
	pStaticObject_0->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[0], pObjectTexArr[0]));
	pStaticObject_0->SetTexPos(Vec2(342.f, 310.f));
	AddObject(pStaticObject_0, GROUP_TYPE::BACKGROUND);

	//학생들 책상2 (우)
	pStaticObject_1 = new CStaticObject;
	pStaticObject_1->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[1], pObjectTexArr[1]));
	pStaticObject_1->SetTexPos(Vec2(1028.f, 380.f));
	AddObject(pStaticObject_1, GROUP_TYPE::BACKGROUND);

	//npc 1
	pStaticObject_2 = new CStaticObject;
	pStaticObject_2->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[2], pObjectTexArr[2]));
	pStaticObject_2->SetTexPos(Vec2(274.f, 148.f));
	AddObject(pStaticObject_2, GROUP_TYPE::BACKGROUND);

	//npc 2
	pStaticObject_3 = new CStaticObject;
	pStaticObject_3->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[3], pObjectTexArr[3]));
	pStaticObject_3->SetTexPos(Vec2(1580.f, 168.f));
	AddObject(pStaticObject_3, GROUP_TYPE::BACKGROUND);

	//액자 레이아웃
	pStaticObject_4 = new CStaticObject;
	pStaticObject_4->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[4], pObjectTexArr[4]));
	pStaticObject_4->SetTexPos(Vec2(402.f, 52.f));
	AddObject(pStaticObject_4, GROUP_TYPE::BACKGROUND);

	//C 액자
	pStaticObject_5 = new CStaticObject;
	pStaticObject_5->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[5], pObjectTexArr[5]));
	pStaticObject_5->SetTexPos(Vec2(790.f, 122.f));
	AddObject(pStaticObject_5, GROUP_TYPE::INTERACTIVE);

	//M 액자
	pStaticObject_6 = new CStaticObject;
	pStaticObject_6->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[6], pObjectTexArr[6]));
	pStaticObject_6->SetTexPos(Vec2(1070.f, 123.f));
	AddObject(pStaticObject_6, GROUP_TYPE::INTERACTIVE);

	//QR 액자
	pStaticObject_7 = new CStaticObject;
	pStaticObject_7->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[7], pObjectTexArr[7]));
	pStaticObject_7->SetTexPos(Vec2(930.f, 123.f));
	AddObject(pStaticObject_7, GROUP_TYPE::INTERACTIVE);

	//Y 액자
	pStaticObject_8 = new CStaticObject;
	pStaticObject_8->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[8], pObjectTexArr[8]));
	pStaticObject_8->SetTexPos(Vec2(1210.f, 122.f));
	AddObject(pStaticObject_8, GROUP_TYPE::INTERACTIVE);

	//K 액자
	pStaticObject_9 = new CStaticObject;
	pStaticObject_9->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[9], pObjectTexArr[9]));
	pStaticObject_9->SetTexPos(Vec2(650.f, 122.f));
	AddObject(pStaticObject_9, GROUP_TYPE::INTERACTIVE);

	pStaticObject_9 = new CStaticObject;
	pStaticObject_9->SetTexture(CResMgr::GetInst()->LoadTexture(pObjectKeyArr[9], pObjectTexArr[9]));
	pStaticObject_9->SetTexPos(Vec2(650.f, 122.f));
	AddObject(pStaticObject_9, GROUP_TYPE::INTERACTIVE);


	// player
	pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(650.f, -130.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// exit to lobby
	pExit_LOBBY = new CExit_Trigger;
	pExit_LOBBY->SetPos(Vec2(790.f, -80.f));
	pExit_LOBBY->SetScale(Vec2(200.f, 50.f));
	pExit_LOBBY->SetNextScene(SCENE_TYPE::LOBBY);
	AddObject(pExit_LOBBY, GROUP_TYPE::INTERACTIVE);


	/// 액자 번호 바뀜
	//interactive - puzzle frame
	frame_0 = new CInteractive;
	//frame_0->SetPos(Vec2(282.f, -379.f));
	frame_0->SetPos(Vec2(-278.f, -379.f));
	frame_0->SetScale(Vec2(100.f, 230.f));
	/*frame_0->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	frame_0->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	frame_0->SetFramenum(0);
	AddObject(frame_0, GROUP_TYPE::INTERACTIVE);

	frame_1 = new CInteractive;
	//frame_1->SetPos(Vec2(142.f, -379.f));
	frame_1->SetPos(Vec2(-138.f, -379.f));
	frame_1->SetScale(Vec2(100.f, 230.f));
	/*frame_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	frame_1->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	frame_1->SetFramenum(1);
	AddObject(frame_1, GROUP_TYPE::INTERACTIVE);

	frame_2 = new CInteractive;
	//frame_2->SetPos(Vec2(-138.f, -379.f));
	frame_2->SetPos(Vec2(142.f, -379.f));
	frame_2->SetScale(Vec2(100.f, 230.f));
	/*frame_2->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	frame_2->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	frame_2->SetFramenum(2);
	AddObject(frame_2, GROUP_TYPE::INTERACTIVE);

	frame_3 = new CInteractive;
	//frame_3->SetPos(Vec2(-278.f, -379.f));
	frame_3->SetPos(Vec2(282.f, -379.f));
	frame_3->SetScale(Vec2(100.f, 230.f));
	/*frame_3->SetTexture(CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp"));*/
	frame_3->SetType(INTERACTIVE_TYPE::PUZZLE_ART);
	frame_3->SetFramenum(3);
	AddObject(frame_3, GROUP_TYPE::INTERACTIVE);

	// interactive - QR
	QR = new CInteractive;
	QR->SetPos(Vec2(0.f, 0.f));
	QR->SetScale(Vec2(100.f, 100.f));
	QR->SetType(INTERACTIVE_TYPE::TEXTBOX);
	QR->SetTextCount(1);
	QR->SetText(L"액자가 보인다");
	AddObject(QR, GROUP_TYPE::INTERACTIVE);

	// QR 상호작용 액자
	frame_QR = new CInteractive;
	frame_QR->SetPos(Vec2(0.f, -379.f));
	frame_QR->SetScale(Vec2(100.f, 230.f));
	frame_QR->SetType(INTERACTIVE_TYPE::QR);
	frame_QR->SetQRnum(0);
	AddObject(frame_QR, GROUP_TYPE::INTERACTIVE);


	// collision
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

	// first == false
	GameManager::GetInst()->SetSceneFirst(SCENE_TYPE::ART, false);

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TEXT);

}

void CScene_ART::SecondEnter()
{
	pWall_1->SetPos(Vec2(0.f, -300.f));
	pWall_2->SetPos(Vec2(0.f, 500.f));
	pWall_3->SetPos(Vec2(-700.f, 0.f));
	pWall_4->SetPos(Vec2(700.f, 0.f));
	pWall_21->SetPos(Vec2(325.f, 300.f));
	pWall_22->SetPos(Vec2(345.f, -130.f));
	pWall_23->SetPos(Vec2(570.f, 100.f));
	pWall_24->SetPos(Vec2(100.f, 100.f));
	pWall_11->SetPos(Vec2(-345.f, 300.f));
	pWall_12->SetPos(Vec2(-345.f, -130.f));
	pWall_13->SetPos(Vec2(-590.f, 100.f));
	pWall_14->SetPos(Vec2(-100.f, 100.f));
	pWall_31->SetPos(Vec2(-405.f, -100.f));
	pWall_32->SetPos(Vec2(-405.f, -210.f));
	pWall_33->SetPos(Vec2(-475.f, -120.f));
	pWall_34->SetPos(Vec2(-335.f, -120.f));
	pWall_35->SetPos(Vec2(-620.f, -350.f));
	pWall_36->SetPos(Vec2(635.f, -350.f));
	pWall_37->SetPos(Vec2(-635.f, -250.f));
	pWall_38->SetPos(Vec2(655.f, -250.f));
	pWall_38->SetPos(Vec2(655.f, -250.f));


	pBackground->SetPos(Vec2(960.f, 540.f));
	/*pPlayer->SetPos(Vec2(600.f, 384.f));
	pExit_LOBBY->SetPos(Vec2(750.f, 380.f));
	frame_0->SetPos(Vec2(640.f, -300.f));
	frame_1->SetPos(Vec2(320.f, -300.f));
	frame_2->SetPos(Vec2(0.f, -300.f));
	frame_3->SetPos(Vec2(-320.f, -300.f));*/


	pPlayer->SetPos(Vec2(650.f, -130.f));

	pExit_LOBBY->SetPos(Vec2(790.f, -80.f));
	frame_0->SetPos(Vec2(-278.f, -379.f));
	frame_1->SetPos(Vec2(-138.f, -379.f));
	frame_2->SetPos(Vec2(142.f, -379.f));
	frame_3->SetPos(Vec2(282.f, -379.f));

	// interactive - QR
	QR->SetPos(Vec2(0.f, 0.f));

	// QR 상호작용 액자
	frame_QR->SetPos(Vec2(0.f, -379.f));


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::INTERACTIVE);

}
