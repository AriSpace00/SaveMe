#include "pch.h"
#include "CTextBox.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"
#include "TextManager.h"
#include "CKeyMgr.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CQR.h"


CTextBox::CTextBox()
	:m_txt{}
	,arrPortait{}
{
	GameManager::GetInst()->SetMovable(false);

	// 대사
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TextBox", L"texture\\text_box.bmp");
	m_curShowText = 0;
	m_textCount = 0;

	// 초상화
	m_pTexs[(int)PORTAIT_TYPE::DEFAULT] = nullptr;

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_BASIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// 플레이어 기본

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_PANIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // 플레이어 패닉

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// 플레이어 쪼갬

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// 플레이어 놀람

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// 플레이어 생각중

	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // 기획 정수
	
	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // 아트 정수
	
	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // 플밍 정수
	
	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst() ->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // 교수님 심장
	
	m_isCreated = false;

	// 초상화 카운트 변수 초기화
	//m_totalShowPortrait = 0;
	//m_curShowPortrait = 0;

}

CTextBox::~CTextBox()
{
	GameManager::GetInst()->SetMovable(true);

}

void CTextBox::initCenterPos()
{
}

void CTextBox::update()
{
}

void CTextBox::render(HDC _dc)
{
	// 레이어 순으로 렌더할 것 (초상화를 가장 나중에 해야하나?)

	// 대화창
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	if (m_txt[m_curShowText] != L"")
	{
		TransparentBlt(_dc,
			vPos.x - iWidth / 2, vPos.y - iHeight / 2,
			iWidth, iHeight,
			m_pTex->GetDC(),
			0, 0,
			iWidth, iHeight,
			RGB(106, 255, 0));
	}


	if (m_pTexs[arrPortait[m_curShowText]] != nullptr)
	{
		// 모든 초상화를 출력한 경우 오브젝트 삭제
		if (m_curShowText >= m_textCount)
		{
			//GameManager::GetInst()->SetMovable(true);
			//DeleteObject(this);
			return;
		}

		// vPos를 디스플레이 기준 중앙으로 설정
		// Vec2 vPos = GetPos();
		vPos.x = ScreenSize.x / 2;
		vPos.y = ScreenSize.y / 2;
		SetPos(vPos);

		if (arrPortait[m_curShowText] == (int)PORTAIT_TYPE::DS_OBJ || arrPortait[m_curShowText] == (int)PORTAIT_TYPE::ART_OBJ || arrPortait[m_curShowText] == (int)PORTAIT_TYPE::PM_OBJ || arrPortait[m_curShowText] == (int)PORTAIT_TYPE::HEART)
		{
			iWidth = (int)m_pTexs[arrPortait[m_curShowText]]->Width();
			iHeight = (int)m_pTexs[arrPortait[m_curShowText]]->Height();

			TransparentBlt(_dc,
				(int)vPos.x - iWidth / 2 + 50,
				(int)vPos.y - iHeight / 2,
				iWidth, iHeight,
				m_pTexs[arrPortait[m_curShowText]]->GetDC(),
				0, 0,
				iWidth, iHeight,
				RGB(106, 255, 0));
		}
		else
		{
			iWidth = (int)m_pTexs[arrPortait[m_curShowText]]->Width();
			iHeight = (int)m_pTexs[arrPortait[m_curShowText]]->Height();

			TransparentBlt(_dc,
				(int)vPos.x - iWidth / 2,
				(int)vPos.y - iHeight / 2,
				iWidth, iHeight,
				m_pTexs[arrPortait[m_curShowText]]->GetDC(),
				0, 0,
				iWidth, iHeight,
				RGB(106, 255, 0));

		}

	}



	// 대화창 내에 텍스트 렌더
	if (!TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::SUBS))
	{
		if (KEY_TAP(KEY::SPACE))
		{
			/*if (m_txt[m_curShowText] == L"원내 게시판에 무언가 쓰여있는 것 같다.")
			{*/


			if (m_txt[m_curShowText] == L"오른손으로 심장을 빼든다. 피가 터져 흐른다.")
			{
				SoundManager::GetInst()->playSFX(SFX::get_object);

			}
			if (m_txt[m_curShowText] == L"이건... 내 뇌야...")
			{
				SoundManager::GetInst()->playSFX(SFX::shock);

			}
			
			/*if (m_txt[m_curShowText] == L"[HEART]를 획득했다.")
			{
				SoundManager::GetInst()->playSFX(SFX::warning_sound_1);
			}*/
			if (m_txt[m_curShowText] == L"모니터의 입이 열리고, 피가 흐르는 심장을 먹어 치운다.")
			{
				SoundManager::GetInst()->playSFX(SFX::monitor_eating);

			}
			TextManager::GetInst()->clearText();
			if (m_curShowText >= m_textCount - 1)
			{
				GameManager::GetInst()->SetTextEnd(true);
				if (m_txt[1] == L"예술의 정수를 획득하였다." || m_txt[0] == L"논리의 정수를 획득하였다." || m_txt[0] == L"기획의 정수를 획득하였다.")
				{
					SoundManager::GetInst()->playSFX(SFX::get_object);
				}
				if (m_txt[0] == L"문이 열렸다!")
				{
					GameManager::GetInst()->SetSceneAcsess(SCENE_TYPE::LOBBY, true);
					SoundManager::GetInst()->playSFX(SFX::door_open);

				}

				DeleteObject(this);
				return;
			}
			m_curShowText++;
		}
	}

}
