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

	// initCenterPos �� �����Ǵ� interective ���� ����� �Կ�
	isCreated = false;
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 230.f));

	// ���� ���� �װ���, 0(C) 1(M) 2(Y) 3(K) ���� ������ ����
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
	// �� ���� ��ġ�� �Ȱ��� ������ �����ؾ��� 
	// (�ٵ� �ݶ��̴��� ���������� �ణ �����ؾ��� ��)
	/*vPos_frame[0] = Vec2(282.f, -379.f);
	vPos_frame[1] = Vec2(142.f, -378.f);
	vPos_frame[2] = Vec2(-138.f, -379.f);
	vPos_frame[3] = Vec2(-278.f, -379.f);*/

	vPos_frame[0] = Vec2(-278.f, -379.f);
	vPos_frame[1] = Vec2(-138.f, -379.f);
	vPos_frame[2] = Vec2(142.f, -378.f);
	vPos_frame[3] = Vec2(282.f, -379.f);
	
	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos�� ���÷��� ���� �߾����� ����
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
//		// �����̽��� ������ int �ϳ��� �ö󰡼� ���� �� ��ȣ�� ������
//		curColorNum++;
//		curColorNum = curColorNum % 4; // 4 �� ���� ����
//	}
//
//	GameManager::GetInst()->SetFrameAnswer(m_framenum, curColorNum == answerColorNum[m_framenum]);
//
//	if (GameManager::GetInst()->GetFrameAnswer())
//	{
//		// if(�����̸�)
//		GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::ART, true);
//		// ���� ����!
//		GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);
//
//		// ��ȭâ �ߺ� ���� ����
//		if (!isCreated)
//		{
//			isCreated = true;
//
//			CTextBox* pTextBox = new CTextBox;
//			LPCWSTR m_txt[3] = { L"��Ʈ�� ������ ȹ���Ͽ���",L"",L"" };
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
	// vPos�� ���÷��� ���� �߾����� ����
	//Vec2 vPos = GetPos();
	//vPos.x = ScreenSize.x / 2;
	//vPos.y = ScreenSize.y / 2;
	//SetPos(vPos);

	int x2 = ScreenSize.x / 2 - vResolution.x / 2 + vPos.x;
	int y2 = ScreenSize.y / 2 - vResolution.y / 2 + vPos.y;

	SetPos(vPos);
	component_render(_dc);

	/// ���� ������ ���
	m_pColorTex[curColorNum] = CResMgr::GetInst()->LoadTexture(texKeyArr[curColorNum], textureArr[curColorNum]);

	// �ؽ�ó ũ�� ����
	int iWidth = (int)m_pColorTex[curColorNum]->Width();
	int iHeight = (int)m_pColorTex[curColorNum]->Height();

	// ���÷��� �߾ӿ� �ؽ�ó �׸���
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
		// �����̽��� ������ int �ϳ��� �ö󰡼� ���� �� ��ȣ�� ������
		curColorNum++;
		curColorNum = curColorNum % 4; // 4 �� ���� ����

		SoundManager::GetInst()->playSFX(SFX::color_change);
	}

	GameManager::GetInst()->SetFrameAnswer(m_framenum, curColorNum == answerColorNum[m_framenum]);

	if (GameManager::GetInst()->GetFrameAnswer())
	{
		// if(�����̸�)
		GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::ART, true);
		//SoundManager::GetInst()->playBGM(BGM::Kindergarden);
		// ���� ����!


		// ��ȭâ �ߺ� ���� ����
		if (!isCreated && GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART))
		{
			isCreated = true;
			GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);

			SoundManager::GetInst()->playSFX(SFX::eyes_open);
			SoundManager::GetInst()->playSFX(SFX::frame_success);



			CTextBox* pTextBox = new CTextBox;
			LPCWSTR m_txt[3] = { L"",L"������ ������ ȹ���Ͽ���.", L"�� ������ ������ �� ��..."};
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


// �ݶ��̴��� SetPos �� ���־�� Ȯ����ġ�� �˰� �ش� ��ġ�� �̵��Ѵ�
