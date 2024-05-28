#include "pch.h"
#include "CPuzzle_Frame.h"
#include "CKeyMgr.h"
#include "GameManager.h"
#include "CCollider.h"
#include "CCore.h"
#include "CTextBox.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "SoundManager.h"
#include "CTimeMgr.h"
#include "CBackground.h"
#include "CStaticObject.h"



CPuzzle_Frame::CPuzzle_Frame()
	: m_framenum(), m_pColorTex{}
{
	texKeyArr[0] = L"ART_FRAME_C";
	texKeyArr[1] = L"ART_FRAME_M";
	texKeyArr[2] = L"ART_FRAME_Y";
	texKeyArr[3] = L"ART_FRAME_K";

	textureArr[0] = L"texture\\puzzle_ART\\C.bmp";
	textureArr[1] = L"texture\\puzzle_ART\\M.bmp";
	textureArr[2] = L"texture\\puzzle_ART\\Y.bmp";
	textureArr[3] = L"texture\\puzzle_ART\\K.bmp";

	// initCenterPos 는 생성되는 interective 에서 해줘야 함요
	isCreated = false;
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 230.f));

	// 정답 색은 네가지, 0(C) 1(M) 2(Y) 3(K) 으로 지정할 예정
	answerColorNum[0] = 0;
	answerColorNum[1] = 1;
	answerColorNum[2] = 2;
	answerColorNum[3] = 3;

	curColorNum = 0;
}

CPuzzle_Frame::~CPuzzle_Frame()
{
}

void CPuzzle_Frame::initCenterPos()
{
	// 찐 액자 위치랑 똑같은 값으로 지정해야함 
	// (근데 콜라이더는 오프셋으로 약간 조정해야할 듯)
	/*vPos_frame[0] = Vec2(282.f, -379.f);
	vPos_frame[1] = Vec2(142.f, -378.f);
	vPos_frame[2] = Vec2(-138.f, -379.f);
	vPos_frame[3] = Vec2(-278.f, -379.f);*/

	vPos_frame[0] = Vec2(-278.f, -379.f);
	vPos_frame[1] = Vec2(-138.f, -379.f);
	vPos_frame[2] = Vec2(142.f, -378.f);
	vPos_frame[3] = Vec2(282.f, -379.f);
	
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	vPos.x = ScreenSize.x / 2 + vPos_frame[m_framenum].x;
	vPos.y = ScreenSize.y / 2 + vPos_frame[m_framenum].y;

	SetPos(vPos);
}


void CPuzzle_Frame::update()
{
	
	
}


//void CPuzzle_Frame::render(HDC _dc)
//{
//	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();
//	int x = ScreenSize.x / 2 + vPos.x;
//	int y = ScreenSize.y / 2 + vPos.y;
//	Rectangle(_dc, vPos.x - 100, vPos.y - 100, vPos.x + 100, vPos.y + 100);
//	component_render(_dc);
//}
//
//void CPuzzle_Frame::OnCollision(CCollider* _pOther)
//{
//	if (KEY_TAP(KEY::SPACE))
//	{
//		// 스페이스바 누르면 int 하나씩 올라가서 정답 색 번호와 비교하자
//		curColorNum++;
//		curColorNum = curColorNum % 4; // 4 는 색깔 개수
//	}
//
//	GameManager::GetInst()->SetFrameAnswer(m_framenum, curColorNum == answerColorNum[m_framenum]);
//
//	if (GameManager::GetInst()->GetFrameAnswer())
//	{
//		// if(정답이면)
//		GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::ART, true);
//		// 정답 사운드!
//		GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);
//
//		// 대화창 중복 생성 방지
//		if (!isCreated)
//		{
//			isCreated = true;
//
//			CTextBox* pTextBox = new CTextBox;
//			LPCWSTR m_txt[3] = { L"아트의 정수를 획득하였다",L"",L"" };
//			pTextBox->SetTXTInfo(m_txt, 1);
//			PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::PLAYER_BASIC };
//			pTextBox->SetPortrait(_type, 1);
//			CreateObject(pTextBox, GROUP_TYPE::INTERACTIVE);
//		}
//	}
//}


void CPuzzle_Frame::render(HDC _dc)
{
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//int x = ScreenSize.x / 2 + vPos.x;
	//int y = ScreenSize.y / 2 + vPos.y;
	//Rectangle(_dc, vPos.x - 100, vPos.y - 100, vPos.x + 100, vPos.y + 100);
	


	/// test pos !!!!!!!!!!!!!!!!!!!!!!!!!!!
	// vPos를 디스플레이 기준 중앙으로 설정
	//Vec2 vPos = GetPos();
	//vPos.x = ScreenSize.x / 2;
	//vPos.y = ScreenSize.y / 2;
	//SetPos(vPos);

	int x2 = ScreenSize.x / 2 - vResolution.x / 2 + vPos.x;
	int y2 = ScreenSize.y / 2 - vResolution.y / 2 + vPos.y;

	SetPos(vPos);
	component_render(_dc);

	/// 액자 렌더링 뷰뷴
	m_pColorTex[curColorNum] = CResMgr::GetInst()->LoadTexture(texKeyArr[curColorNum], textureArr[curColorNum]);

	// 텍스처 크기 정보
	int iWidth = (int)m_pColorTex[curColorNum]->Width();
	int iHeight = (int)m_pColorTex[curColorNum]->Height();

	// 디스플레이 중앙에 텍스처 그리기
	/*BitBlt(_dc,
		vPos.x - iWidth / 2,
		vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pColorTex[curColorNum]->GetDC(),
		0, 0,
		SRCCOPY);*/

	BitBlt(_dc,
		x2 - iWidth / 2,
		y2 - iHeight / 2,
		iWidth, iHeight,
		m_pColorTex[curColorNum]->GetDC(),
		0, 0,
		SRCCOPY);

}

void CPuzzle_Frame::OnCollision(CCollider* _pOther)
{
	if (KEY_TAP(KEY::SPACE) && GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART))
	{
		// 스페이스바 누르면 int 하나씩 올라가서 정답 색 번호와 비교하자
		curColorNum++;
		curColorNum = curColorNum % 4; // 4 는 색깔 개수

		SoundManager::GetInst()->playSFX(SFX::color_change);
	}

	GameManager::GetInst()->SetFrameAnswer(m_framenum, curColorNum == answerColorNum[m_framenum]);

	if (GameManager::GetInst()->GetFrameAnswer())
	{
		// if(정답이면)
		GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::ART, true);
		//SoundManager::GetInst()->playBGM(BGM::Kindergarden);
		// 정답 사운드!


		// 대화창 중복 생성 방지
		if (!isCreated && GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART))
		{
			isCreated = true;
			GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);

			SoundManager::GetInst()->playSFX(SFX::eyes_open);
			SoundManager::GetInst()->playSFX(SFX::frame_success);



			CTextBox* pTextBox = new CTextBox;
			LPCWSTR m_txt[3] = { L"",L"예술의 정수를 획득하였다.", L"이 느낌은 적응이 안 돼..."};
			pTextBox->SetTXTInfo(m_txt, 3);
			PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::ART_OBJ, PORTAIT_TYPE::PLAYER_PANIC};
			pTextBox->SetPortrait(_type, 3);
			CreateObject(pTextBox, GROUP_TYPE::TEXT);

			CBackground* pBackground = new CBackground;
			pBackground->SetPos(Vec2(960.f, 540.f));
			pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_ART_CHANGE", L"texture\\hs_test.bmp"));
			pBackground->initCenterPos();
			CreateObject(pBackground, GROUP_TYPE::BACKGROUND);


			CStaticObject* pFilter = new CStaticObject;
			pFilter->SetPos(Vec2(0.f,0.f));
			pFilter->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_ART_FILTER", L"texture\\MAP\\art_class\\Art_Compelete\\blood_Filter.bmp"));
			pFilter->initCenterPos();
			CreateObject(pFilter, GROUP_TYPE::BACKGROUND);
		}
	}
}


// 콜라이더는 SetPos 를 해주어야 확정위치로 알고 해당 위치로 이동한다
