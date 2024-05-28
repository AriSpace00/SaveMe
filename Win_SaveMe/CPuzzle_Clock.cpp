#include "pch.h"
#include "CPuzzle_Clock.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTextBox.h"
#include "CKeyMgr.h"
#include "GameManager.h"

#include "SoundManager.h"
#include "CTimeMgr.h"

CPuzzle_Clock::CPuzzle_Clock()
{
	GameManager::GetInst()->SetMovable(false);

	m_pBGTex = CResMgr::GetInst()->LoadTexture(L"puzzle_Clock_BG", L"texture\\black_alpha channel.bmp");
	m_pDotTex = CResMgr::GetInst()->LoadTexture(L"puzzle_Clock_DOT", L"texture\\I_HATE_CLOCK\\num_sep.bmp");

	//m_pTex = CResMgr::GetInst()->LoadTexture(L"puzzle_Clock", L"texture\\test_puzzle_lobby.bmp");
	initCenterPos();

	m_isCorrect = false;
	
	// 시 인풋 초기화
	m_input[0] = 0;
	// 분 인풋 초기화
	m_input[1] = 0;
	// 버튼 클릭 여부 초기화
	button_state = 0;

	// 시계의 버튼 지정
	buttonTexKeyArr[0] = L"Clock_Button_Default";
	buttonTexKeyArr[1] = L"Clock_Button_Hour_Down";
	buttonTexKeyArr[2] = L"Clock_Button_Min_Down";

	buttonTextureArr[0] = L"texture\\I_HATE_CLOCK\\digitalclock_Default.bmp";
	buttonTextureArr[1] = L"texture\\I_HATE_CLOCK\\digitalclock_hour_Down.bmp";
	buttonTextureArr[2] = L"texture\\I_HATE_CLOCK\\digitalclock_min_Down.bmp";

	// 시계의 숫자 지정
	texKeyArr[0] = L"Clock_minute_0";
	texKeyArr[1] = L"Clock_minute_1";
	texKeyArr[2] = L"Clock_minute_2";
	texKeyArr[3] = L"Clock_minute_3";
	texKeyArr[4] = L"Clock_minute_4";
	texKeyArr[5] = L"Clock_minute_5";
	texKeyArr[6] = L"Clock_minute_6";
	texKeyArr[7] = L"Clock_minute_7";
	texKeyArr[8] = L"Clock_minute_8";
	texKeyArr[9] = L"Clock_minute_9";

	textureArr[0] = L"texture\\I_HATE_CLOCK\\num_0.bmp";
	textureArr[1] = L"texture\\I_HATE_CLOCK\\num_1.bmp";
	textureArr[2] = L"texture\\I_HATE_CLOCK\\num_2.bmp";
	textureArr[3] = L"texture\\I_HATE_CLOCK\\num_3.bmp";
	textureArr[4] = L"texture\\I_HATE_CLOCK\\num_4.bmp";
	textureArr[5] = L"texture\\I_HATE_CLOCK\\num_5.bmp";
	textureArr[6] = L"texture\\I_HATE_CLOCK\\num_6.bmp";
	textureArr[7] = L"texture\\I_HATE_CLOCK\\num_7.bmp";
	textureArr[8] = L"texture\\I_HATE_CLOCK\\num_8.bmp";
	textureArr[9] = L"texture\\I_HATE_CLOCK\\num_9.bmp";

	min_count = 0;
	hour_count = 0;

	min_count2 = 0;
	hour_count2 = 0;

	elapedTime = 0.f;
	delayTime = 0.f;

	isCorrect = false;
}

CPuzzle_Clock::~CPuzzle_Clock()
{
	GameManager::GetInst()->SetMovable(true);

}

void CPuzzle_Clock::initCenterPos()
{
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CPuzzle_Clock::update()
{
	if (KEY_TAP(KEY::ESC))
	{
		GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, true);

		DeleteObject(this);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if (hour_count2 == 0 && hour_count == 4 && min_count2 == 3 && min_count == 3)
		{
			isCorrect = true;
			GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::DS, true);

			GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, false);

			// 로비 퍼즐 -> 기획의 정수를 획득한다
			CTextBox* pTextBox = new CTextBox;
			LPCWSTR m_txt[2] = { L"기획의 정수를 획득하였다.",L"이건... 내 뇌야..."};
			PORTAIT_TYPE _type[2] = { PORTAIT_TYPE::DS_OBJ,PORTAIT_TYPE::PLAYER_PANIC };
			pTextBox->SetPortrait(_type, 2);
			pTextBox->SetTXTInfo(m_txt, 2);
			CreateObject(pTextBox, GROUP_TYPE::TEXT);
			DeleteObject(this);
		}
		else
		{
			hour_count2 = 0;
			hour_count = 0;
			min_count2 = 0;
			min_count = 0;

			button_state = 0;

			SoundManager::GetInst()->playSFX(SFX::warning_beep);

			isCorrect = false;
		}
	}

	if (KEY_NONE(KEY::LBTN))
	{
		elapedTime = 0.f;
		delayTime = 0.f;

		button_state = 0;
	}

	if (KEY_HOLD(KEY::LBTN))
	{
		elapedTime += DT;
		delayTime += DT;

		if (elapedTime >= 0.5f)
		{
			// 1번 버튼 클릭 시 시간의 수를 올린다
			if (m_vMousePos.x < m_button[0].right &&
				m_vMousePos.x > m_button[0].left &&
				m_vMousePos.y < m_button[0].bottom &&
				m_vMousePos.y > m_button[0].top)
			{
				SoundManager::GetInst()->playSFX(SFX::clock_click);

				// 시 버튼 눌린 상태
				button_state = 1;

				if (hour_count2 == 1 && hour_count == 2)
				{
					hour_count2 = 0;
					hour_count = 0;
				}
				else if (hour_count == 9)
				{
					hour_count = 0;
					hour_count2++;
				}
				else
				{	
					if (delayTime >= 0.1f)
					{
						hour_count++;
						delayTime = 0.f;
					}
				}
				
			}
			// 2번 버튼 클릭하면 분의 수를 올린다
			if (m_vMousePos.x < m_button[1].right &&
				m_vMousePos.x > m_button[1].left &&
				m_vMousePos.y < m_button[1].bottom &&
				m_vMousePos.y > m_button[1].top)
			{
				SoundManager::GetInst()->playSFX(SFX::clock_click);

				// 분 버튼 눌린 상태
				button_state = 2;

				if (min_count2 == 5 && min_count == 9)
				{
					min_count = 0;
					min_count2 = 0;
				}
				else if (min_count == 9)
				{
					min_count = 0;
					min_count2++;
				}
				else
				{
					if (delayTime >= 0.1f)
					{
						min_count++;
						delayTime = 0.f;
					}
				}
			}
		}
	}
	else if (KEY_TAP(KEY::LBTN))
	{
		//SoundManager::GetInst()->playSFX(SFX::testSFX);
		m_vMousePos = CKeyMgr::GetInst()->GetMousePos();

		// 1번 버튼 클릭 시 시간의 수를 올린다
		if (m_vMousePos.x < m_button[0].right &&
			m_vMousePos.x > m_button[0].left &&
			m_vMousePos.y < m_button[0].bottom &&
			m_vMousePos.y > m_button[0].top)
		{
			SoundManager::GetInst()->playSFX(SFX::clock_click);

			// 시 버튼 눌린 상태
			button_state = 1;

			if (hour_count2 == 1 && hour_count == 2)
			{
				hour_count2 = 0;
				hour_count = 0;
			}
			else if (hour_count == 9)
			{
				hour_count = 0;
				hour_count2++;
			}
			else
			{
				hour_count++;
			}
		}

		// 2번 버튼 클릭 시 분의 수를 올린다
		if (m_vMousePos.x < m_button[1].right &&
			m_vMousePos.x > m_button[1].left &&
			m_vMousePos.y < m_button[1].bottom &&
			m_vMousePos.y > m_button[1].top)
		{
			SoundManager::GetInst()->playSFX(SFX::clock_click);

			// 분 버튼 눌린 상태
			button_state = 2;

			if (min_count2 == 5 && min_count == 9)
			{
				min_count = 0;
				min_count2 = 0;
			}
			else if (min_count == 9)
			{
				min_count = 0;
				min_count2++;
			}
			else
			{
				min_count++;
			}
		}

	}
}

void CPuzzle_Clock::render(HDC _dc)
{
	/// 배경 (테스트 이미지 검정 -> 추후 노트북 등으로 변경)
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);
	// 텍스처 크기 정보
	int iWidth = (int)m_pBGTex->Width();
	int iHeight = (int)m_pBGTex->Height();

	// 디스플레이 중앙에 텍스처 그리기
	BitBlt(_dc,
		vPos.x - iWidth / 2,
		vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pBGTex->GetDC(),
		0, 0,
		SRCCOPY);


	/// 시계 틀 렌더
	m_pTex[button_state] = CResMgr::GetInst()->LoadTexture(buttonTexKeyArr[button_state], buttonTextureArr[button_state]);

	iWidth = (int)m_pTex[button_state]->Width();
	iHeight = (int)m_pTex[button_state]->Height();
	BitBlt(_dc,
		vPos.x - iWidth / 2,
		vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex[button_state]->GetDC(),
		0, 0,
		SRCCOPY);




	/// 시계 내부 숫자(추후 아래서 렌더)
	// 시(일의 자리)
	m_pHourTex[0] = CResMgr::GetInst()->LoadTexture(texKeyArr[hour_count], textureArr[hour_count]);
	
	iWidth = (int)m_pHourTex[0]->Width();
	iHeight = (int)m_pHourTex[0]->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2 - iWidth + 20,
		(int)vPos.y - iHeight / 2 + 60,
		iWidth, iHeight,
		m_pHourTex[0]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	// 시(십의 자리)
	m_pHourTex[1] = CResMgr::GetInst()->LoadTexture(texKeyArr[hour_count2], textureArr[hour_count2]);

	iWidth = (int)m_pHourTex[1]->Width();
	iHeight = (int)m_pHourTex[1]->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2 - iWidth - iWidth + 20,
		(int)vPos.y - iHeight / 2 + 60,
		iWidth, iHeight,
		m_pHourTex[1]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	// 분(일의 자리)
	m_pMinTex[0] = CResMgr::GetInst()->LoadTexture(texKeyArr[min_count], textureArr[min_count]);
	
	iWidth = (int)m_pMinTex[0]->Width();
	iHeight = (int)m_pMinTex[0]->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2 + iWidth + iWidth + 20,
		(int)vPos.y - iHeight / 2 + 60,
		iWidth, iHeight,
		m_pMinTex[0]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	// 분(십의 자리)
	m_pMinTex[1] = CResMgr::GetInst()->LoadTexture(texKeyArr[min_count2], textureArr[min_count2]);

	iWidth = (int)m_pMinTex[1]->Width();
	iHeight = (int)m_pMinTex[1]->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2 + iWidth + 20,
		(int)vPos.y - iHeight / 2 + 60,
		iWidth, iHeight,
		m_pMinTex[1]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	// DOT
	/*iWidth = (int)m_pDotTex->Width();
	iHeight = (int)m_pDotTex->Height();

	Vec2 vPos2;

	vPos2.x = ScreenSize.x / 2;
	vPos2.y = ScreenSize.y / 2;

	TransparentBlt(_dc,
		(int)vPos2.x - iWidth / 2 - 230,
		(int)vPos2.y - iHeight / 2 - 300,
		iWidth, iHeight,
		m_pDotTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));*/

	//m_pDotTex



	/// 버튼 부분 좌표 지정
	 m_button[0] = { (long)vPos.x - 250,(long)vPos.y - 200,(long)vPos.x -50,(long)vPos.y -150};
    m_button[1] = { (long)vPos.x + 50,(long)vPos.y - 200,(long)vPos.x + 250,(long)vPos.y -150};
	// 버튼 테스트 렌더 사각형
    /*Rectangle(_dc, m_button[0].left, m_button[0].top, m_button[0].right, m_button[0].bottom);
    Rectangle(_dc, m_button[1].left, m_button[1].top, m_button[1].right, m_button[1].bottom);*/
}
