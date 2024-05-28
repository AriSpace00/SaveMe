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

	// ���
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TextBox", L"texture\\text_box.bmp");
	m_curShowText = 0;
	m_textCount = 0;

	// �ʻ�ȭ
	m_pTexs[(int)PORTAIT_TYPE::DEFAULT] = nullptr;

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_BASIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// �÷��̾� �⺻

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_PANIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // �÷��̾� �д�

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// �÷��̾� �ɰ�

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// �÷��̾� ���

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// �÷��̾� ������

	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // ��ȹ ����
	
	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // ��Ʈ ����
	
	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // �ù� ����
	
	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst() ->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // ������ ����
	
	m_isCreated = false;

	// �ʻ�ȭ ī��Ʈ ���� �ʱ�ȭ
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
	// ���̾� ������ ������ �� (�ʻ�ȭ�� ���� ���߿� �ؾ��ϳ�?)

	// ��ȭâ
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
		// ��� �ʻ�ȭ�� ����� ��� ������Ʈ ����
		if (m_curShowText >= m_textCount)
		{
			//GameManager::GetInst()->SetMovable(true);
			//DeleteObject(this);
			return;
		}

		// vPos�� ���÷��� ���� �߾����� ����
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



	// ��ȭâ ���� �ؽ�Ʈ ����
	if (!TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::SUBS))
	{
		if (KEY_TAP(KEY::SPACE))
		{
			/*if (m_txt[m_curShowText] == L"���� �Խ��ǿ� ���� �����ִ� �� ����.")
			{*/


			if (m_txt[m_curShowText] == L"���������� ������ �����. �ǰ� ���� �帥��.")
			{
				SoundManager::GetInst()->playSFX(SFX::get_object);

			}
			if (m_txt[m_curShowText] == L"�̰�... �� ����...")
			{
				SoundManager::GetInst()->playSFX(SFX::shock);

			}
			
			/*if (m_txt[m_curShowText] == L"[HEART]�� ȹ���ߴ�.")
			{
				SoundManager::GetInst()->playSFX(SFX::warning_sound_1);
			}*/
			if (m_txt[m_curShowText] == L"������� ���� ������, �ǰ� �帣�� ������ �Ծ� ġ���.")
			{
				SoundManager::GetInst()->playSFX(SFX::monitor_eating);

			}
			TextManager::GetInst()->clearText();
			if (m_curShowText >= m_textCount - 1)
			{
				GameManager::GetInst()->SetTextEnd(true);
				if (m_txt[1] == L"������ ������ ȹ���Ͽ���." || m_txt[0] == L"���� ������ ȹ���Ͽ���." || m_txt[0] == L"��ȹ�� ������ ȹ���Ͽ���.")
				{
					SoundManager::GetInst()->playSFX(SFX::get_object);
				}
				if (m_txt[0] == L"���� ���ȴ�!")
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
