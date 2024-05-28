#include "pch.h"
#include "Camera.h"

#include "CObject.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "SoundManager.h"
#include "GameManager.h"
#include "CBackground.h"
#include "CStaticObject.h"
#include "GameManager.h"

// for cheat
#include "CPuzzle_DoorLock.h"
#include "CPuzzle_Clock.h"
#include "CPuzzle_Frame.h"
#include "CPuzzle_ABC.h"
#include "CTextChoose.h"
#include "CStaticObject.h"

#include "CSceneMgr.h"


Camera::Camera()
	: m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fDuration(0.f)
	, m_fcurTime(0.f)
{
	m_contTex = CResMgr::GetInst()->LoadTexture(L"pause_contTex", L"texture\\ui\\pause_ui_continue.bmp");
	m_mainTex = CResMgr::GetInst()->LoadTexture(L"pause_mainTex", L"texture\\ui\\pause_ui_main.bmp");
	m_quitTex = CResMgr::GetInst()->LoadTexture(L"pause_quitTex", L"texture\\ui\\pause_ui_quit.bmp");
	m_layTex = CResMgr::GetInst()->LoadTexture(L"pause_layoutTex", L"texture\\ui\\pause_ui.bmp");
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();
	m_Continuebutton.left = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 60;
	m_Continuebutton.right = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 320;
	m_Continuebutton.top = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 342;
	m_Continuebutton.bottom = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 432;
	m_Mainbutton.left = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 348;
	m_Mainbutton.right = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 608;
	m_Mainbutton.top = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 342;
	m_Mainbutton.bottom = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 432;
	m_Quitbutton.left = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 632;
	m_Quitbutton.right = ScreenSize.x / 2 - (int)m_layTex->Width() / 2 + 896;
	m_Quitbutton.top = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 342;
	m_Quitbutton.bottom = ScreenSize.y / 2 - (int)m_layTex->Height() / 2 + 432;

	m_layTex = nullptr;

}

Camera::~Camera()
{
}


void Camera::init()
{
	m_vResolution = CCore::GetInst()->GetResolution();
	// 연출 효과를 위한 텍스쳐 생성
	//m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)m_vResolution.x, (UINT)m_vResolution.y);
	m_pVeilTex = CResMgr::GetInst()->LoadTexture(L"CameraVeil", L"texture\\black_alpha channel.bmp");
}

void Camera::update()
{
	// 개발자 치트
	if (KEY_TAP(KEY::V))
	{
		switch (GameManager::GetInst()->GetCurScene())
		{
			case SCENE_TYPE::ROOM:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::CHOOSE))
				{
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::CHOOSE, false);

					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);

					CBackground* pBackground = new CBackground;
					pBackground->SetPos(Vec2(960.f, 540.f));
					pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_RoomTex", L"texture\\MAP\\professor's_office\\ProfessorRoom_Background.bmp"));
					pBackground->initCenterPos();
					CreateObject(pBackground, GROUP_TYPE::BACKGROUND);

					CStaticObject* pStaticObject_1 = new CStaticObject;
					pStaticObject_1->SetTexture(CResMgr::GetInst()->LoadTexture(L"Room_CurtainOpenTex_1", L"texture\\MAP\\professor's_office\\Curtain_Open.bmp"));
					pStaticObject_1->SetTexPos(Vec2(536.f, 120.f));
					pStaticObject_1->initCenterPos();
					CreateObject(pStaticObject_1, GROUP_TYPE::INTERACTIVE);
				}
				else if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK))
				{
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, false);

					CPuzzle_DoorLock* pPuzzle_DoorLock = new CPuzzle_DoorLock;
					CreateObject(pPuzzle_DoorLock, GROUP_TYPE::TEXT);
				}
				else
				{
					GameManager::GetInst()->SetScene(SCENE_TYPE::LOBBY);
				}
				break;
			}
			case SCENE_TYPE::LOBBY:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS))
				{
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, false);

					CPuzzle_Clock* pPuzzle_Clock = new CPuzzle_Clock;
					CreateObject(pPuzzle_Clock, GROUP_TYPE::TEXT);
				}
				else
				{
					GameManager::GetInst()->SetScene(SCENE_TYPE::ART);
				}
				break;
			}
			case SCENE_TYPE::ART:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART))
				{
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART, false);

					CBackground* pBackground = new CBackground;
					pBackground->SetPos(Vec2(960.f, 540.f));
					pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_ART_CHANGE", L"texture\\hs_test.bmp"));
					pBackground->initCenterPos();
					CreateObject(pBackground, GROUP_TYPE::INTERACTIVE);
				}
				else
				{
					GameManager::GetInst()->SetScene(SCENE_TYPE::PM);
				}
				break;
			}
			case SCENE_TYPE::PM:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM))
				{
					CPuzzle_ABC* pPuzzle_PM = new CPuzzle_ABC;
					CreateObject(pPuzzle_PM, GROUP_TYPE::TEXT);
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM, false);

				}
				else
				{
					// 여기서 모니터 ai 말고 모니터 애니메이션으로
					// 모니터 애니메이션은 딜리트 되기 전에 아래 내용 호출
					GameManager::GetInst()->SetScene(SCENE_TYPE::ENDING);
				}
				break;
			}
		}
	}


	// debug
	if (KEY_TAP(KEY::CTRL))
	{
		GameManager::GetInst()->SetDebugMode();
	}
	if (KEY_TAP(KEY::ESC))
	{
		GameManager::GetInst()->SetMovable(false);
		m_layTex = CResMgr::GetInst()->LoadTexture(L"pause_layoutTex", L"texture\\ui\\pause_ui.bmp");
		m_curButtonTex = nullptr;

	}

	if (m_layTex !=nullptr &&KEY_TAP(KEY::LBTN))
	{
		m_vMousePos = CKeyMgr::GetInst()->GetMousePos();


		if (m_vMousePos.x < m_Continuebutton.right &&
			m_vMousePos.x > m_Continuebutton.left &&
			m_vMousePos.y < m_Continuebutton.bottom &&
			m_vMousePos.y > m_Continuebutton.top)
		{
			m_curButtonTex = m_contTex;
			m_layTex = nullptr;
			GameManager::GetInst()->SetMovable(true);
			
		}
		if (m_vMousePos.x < m_Mainbutton.right &&
			m_vMousePos.x > m_Mainbutton.left &&
			m_vMousePos.y < m_Mainbutton.bottom &&
			m_vMousePos.y > m_Mainbutton.top)
		{
			m_curButtonTex = m_mainTex;
			m_layTex = nullptr;
			MessageBox(NULL, L"다시 시작할 수 없습니다!", L"ERROR", MB_OK | MB_ICONINFORMATION);

			//FadeOut(2.f);
			//GameManager::GetInst()->initGame();
			//CSceneMgr::GetInst()->initScene();
		}
		if (m_vMousePos.x < m_Quitbutton.right &&
			m_vMousePos.x > m_Quitbutton.left &&
			m_vMousePos.y < m_Quitbutton.bottom &&
			m_vMousePos.y > m_Quitbutton.top)
		{
			m_curButtonTex = m_quitTex;
			FadeOut(2.f);
			GameManager::GetInst()->SetGameQuit();
		}
	}
}

// 카메라의 렌더는 가장 윗 레이어에서 처리해야 한다
void Camera::render(HDC _dc)
{
	//Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos;
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	//SetPos(vPos);

	if (m_layTex != nullptr)
	{
		int iWidth = (int)m_layTex->Width();
		int iHeight = (int)m_layTex->Height();

		BitBlt(_dc,
			vPos.x - (int)m_layTex->Width() / 2,
			vPos.y - (int)m_layTex->Height() / 2,
			iWidth, iHeight,
			m_layTex->GetDC(),
			0, 0,
			SRCCOPY);
		if (m_curButtonTex == m_contTex)
		{
			BitBlt(_dc,
				ScreenSize.x / 2 - iWidth / 2 + 60,
				ScreenSize.y / 2 - iHeight / 2 + 342,
				iWidth, iHeight,
				m_curButtonTex->GetDC(),
				0, 0,
				SRCCOPY);
		}
		if (m_curButtonTex == m_mainTex)
		{
			BitBlt(_dc,
				ScreenSize.x / 2 - iWidth / 2 + 348,
				ScreenSize.y / 2 - iHeight / 2 + 342,
				iWidth, iHeight,
				m_curButtonTex->GetDC(),
				0, 0,
				SRCCOPY);
		}
		if (m_curButtonTex == m_quitTex)
		{
			BitBlt(_dc,
				ScreenSize.x / 2 - iWidth / 2 + 636,
				ScreenSize.y / 2 - iHeight / 2 + 342,
				iWidth, iHeight,
				m_curButtonTex->GetDC(),
				0, 0,
				SRCCOPY);
		}
		//if (m_mainTex != nullptr)
		//{
		//	BitBlt(_dc,
		//		ScreenSize.x / 2 - iWidth / 2 + 348,
		//		ScreenSize.y / 2 - iHeight / 2 + 342,
		//		iWidth, iHeight,
		//		m_mainTex->GetDC(),
		//		0, 0,
		//		SRCCOPY);
		//}

		//if (m_quitTex != nullptr)
		//{
		//	BitBlt(_dc,
		//		ScreenSize.x / 2 - iWidth / 2 + 636,
		//		ScreenSize.y / 2 - iHeight / 2 + 342,
		//		iWidth, iHeight,
		//		m_quitTex->GetDC(),
		//		0, 0,
		//		SRCCOPY);
		//}
	}


	


	float fRatio = 0.f;	// 이펙트 진행 비율 -> 시간에 따른 알파 채널의 값이 된다

	// 카메라 효과 없음 -> 알파값 0
	if (CAM_EFFECT::NONE == m_eEffect)
		return;
	// FADE IN 효과
	if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		m_fcurTime += fDT;

		if (m_fDuration < m_fcurTime)
		{
			m_eEffect = CAM_EFFECT::NONE;
			m_fcurTime = 0;
			fRatio = 0.f;
			return;
		}

		fRatio = (1.f - m_fcurTime / (m_fDuration));
	}


	// FADE OUT 효과
	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		SoundManager::GetInst()->playSFX(SFX::fade_out);
		// 델타 타임을 더해 현재 시간(누적 시간)을 구한다
		m_fcurTime += fDT;
		// 이펙트 설정 시간보다 현재 시간(누적 시간)이 클 경우
		if (m_fDuration < m_fcurTime)
		{
			m_eEffect = CAM_EFFECT::NONE;
			m_fcurTime = 0;
			fRatio = 0.f;
			return;
		}

		fRatio = m_fcurTime / (m_fDuration);
	}

	
	int iAlpha = (int)(255.f * fRatio);

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	// Vec2 구조체 수정함
	//Vec2 vPos;
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	AlphaBlend(_dc
		, vPos.x - (int)m_pVeilTex->Width() / 2
		, vPos.y - (int)m_pVeilTex->Height() / 2
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height(), bf);
}
