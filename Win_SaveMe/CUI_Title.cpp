#include "pch.h"
#include "CUI_Title.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTextBox.h"
#include "CKeyMgr.h"
#include "GameManager.h"

#include "SoundManager.h"
#include "CTimeMgr.h"
#include "Camera.h"

#include "CSceneMgr.h"

CUI_Title::CUI_Title()
{
	m_pBGTex= CResMgr::GetInst()->LoadTexture(L"Title_BG", L"texture\\Title\\main_scene.bmp");

	button_state = -1;

	yesTexKeyArr[0] = L"Title_YES";
	yesTexKeyArr[1] = L"Title_YES_Pressed";
	yesTexKeyArr[2] = L"Title_YES";

	yesTextureArr[0] = L"texture\\Title\\main_scene_ui_yes.bmp";
	yesTextureArr[1] = L"texture\\Title\\main_scene_ui_press_yes.bmp";
	yesTextureArr[2] = L"texture\\Title\\main_scene_ui_yes.bmp";

	noTexKeyArr[0] = L"Title_NO";
	noTexKeyArr[1] = L"Title_NO";
	noTexKeyArr[2] = L"Title_NO_Pressed";

	noTextureArr[0] = L"texture\\Title\\main_scene_ui_no.bmp";
	noTextureArr[1] = L"texture\\Title\\main_scene_ui_no.bmp";
	noTextureArr[2] = L"texture\\Title\\main_scene_ui_press_no.bmp";

	initCenterPos();
	// 0 버튼 YES 1버튼 NO

	m_fadeOut = false;
}

CUI_Title::~CUI_Title()
{
}

void CUI_Title::initCenterPos()
{
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CUI_Title::update()
{
	if (button_state == 1)
	{
		// YES
		//Camera::GetInst()->FadeOut(3.f);
		{
			if (!m_fadeOut)
			{
				GameManager::GetInst()->SetMovable(false);
				Camera::GetInst()->FadeOut(2.f);
				SoundManager::GetInst()->playSFX(SFX::fade_out);

				m_fadeOut = true;
			}

			delay += DT;

			if (delay >= 2.f)
			{
				GameManager::GetInst()->SetScene(SCENE_TYPE::OPENING); // 추후 Monitor AI 로 변경 부탁
				delay = 0;
				m_fadeOut = false;
			}
		}
	}

	if (button_state == 2)
	{
		// NO
		/*if (!m_fadeOut)
		{
			GameManager::GetInst()->SetMovable(false);
			Camera::GetInst()->FadeOut(2.f);
			m_fadeOut = true;
		}*/
	}

	if (KEY_NONE(KEY::LBTN))
	{
		//button_state = -1;
	}

	if (KEY_TAP(KEY::LBTN))
	{

		m_vMousePos = CKeyMgr::GetInst()->GetMousePos();

		// 아래 반복문의 i 는 버튼의 넘버  i 가 0 YES 1 이면 NO
		for (int i = 0; i < 2; ++i)
		{
			if (m_vMousePos.x < m_button[i].right &&
				m_vMousePos.x > m_button[i].left &&
				m_vMousePos.y < m_button[i].bottom &&
				m_vMousePos.y > m_button[i].top)
			{
				button_state = i + 1;
			}
		}
	}
}

void CUI_Title::render(HDC _dc)
{
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);

	/// 메인 화면 바탕
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


	/// 메인 화면 버튼
	
	if (button_state == -1)
	{
		m_pYesTex = CResMgr::GetInst()->LoadTexture(yesTexKeyArr[0], yesTextureArr[0]);
	}
	else
	{
		m_pYesTex = CResMgr::GetInst()->LoadTexture(yesTexKeyArr[button_state], yesTextureArr[button_state]);
	}


	iWidth = (int)m_pYesTex->Width();
	iHeight = (int)m_pYesTex->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pYesTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	if (button_state == -1)
	{
		m_pNoTex = CResMgr::GetInst()->LoadTexture(noTexKeyArr[0], noTextureArr[0]);
	}
	else
	{
		m_pNoTex = CResMgr::GetInst()->LoadTexture(noTexKeyArr[button_state], noTextureArr[button_state]);
	}

	//m_pNoTex = CResMgr::GetInst()->LoadTexture(noTexKeyArr[button_state], noTextureArr[button_state]);

	iWidth = (int)m_pNoTex->Width();
	iHeight = (int)m_pNoTex->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pNoTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	m_button[0] = { (long)vPos.x -930, (long)vPos.y+160, (long)vPos.x - 730, (long)vPos.y + 290 };
	m_button[1] = { (long)vPos.x - 700, (long)vPos.y + 70, (long)vPos.x - 530, (long)vPos.y + 200 };
	/*Rectangle(_dc, m_button[0].left, m_button[0].top, m_button[0].right, m_button[0].bottom);
	Rectangle(_dc, m_button[1].left, m_button[1].top, m_button[1].right, m_button[1].bottom);*/
}
