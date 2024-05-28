#include "pch.h"
#include "CComputer.h"

#include "CCollider.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTextBox.h"

#include "GameManager.h"
#include "CTextChoose.h"
#include "CPortrait.h"

#include "SoundManager.h"
#include "CBackground.h"

CComputer::CComputer()
	:m_isCreated(),m_isFloating()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f, 200.f));
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ComputerTex", L"texture\\computer_object_test.bmp");
	m_fTex = CResMgr::GetInst()->LoadTexture(L"FloatingTex", L"texture\\ui\\floating_UI.bmp");
}

CComputer::~CComputer()
{
}

void CComputer::SetScale(Vec2 _scale)
{
	GetCollider()->SetScale(_scale);
}
void CComputer::initCenterPos()
{
	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos�� ���÷��� ���� �߾����� ����
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CComputer::update()
{
}

void CComputer::render(HDC _dc)
{

	Vec2 vPos = GetPos();

	// floatingUI
	if (m_isFloating)
	{
		TransparentBlt(_dc,
			(int)vPos.x - m_fTex->Width() / 2,
			(int)vPos.y - 180,
			m_fTex->Width(), m_fTex->Height(),
			m_fTex->GetDC(),
			0, 0,
			m_fTex->Width(), m_fTex->Height(),
			RGB(106, 255, 0));
	}

	// collider
	component_render(_dc);
}

void CComputer::OnCollisionEnter(CCollider* _pOther)
{
	m_isFloating = true;
	m_isCreated = false;
}

void CComputer::OnCollision(CCollider* _pOther)
{
	if (KEY_TAP(KEY::SPACE))
	{
		m_isFloating = false;
		// �ƹ��͵� ���� -> ���� ã�ƺ��� �� �� ����
		// ���� ���� �� ����
		// �� �־��� ������
		// 
		// �������� ��� ������Ʈ���� ������ ���� �����?
		if (GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::PM))
		{
			if (!m_isCreated)
			{
				m_isCreated = true;

				SoundManager::GetInst()->playSFX(SFX::monitor_login);

				CBackground* pBackground = new CBackground;
				pBackground->SetPos(Vec2(960.f, 540.f));
				pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(L"Monitor_Tex", L"texture\\AI_monitor.bmp"));
				pBackground->initCenterPos();
				CreateObject(pBackground, GROUP_TYPE::TEXT);


				CTextChoose* pTextChoose = new CTextChoose;
				LPCWSTR m_txt[4] = 
				{L"���� ������ ������?", 
					L"> �ִ´�     ",
					L"> ���� �ʴ´� ", 
					L"......................"};
				bool isChooseText[4] = { false, true, true, false };
				pTextChoose->SetTXTInfo(m_txt, 4, isChooseText);
				PORTAIT_TYPE _type[4] = { PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::DEFAULT };
				pTextChoose->SetPortrait(_type, 4);
				CreateObject(pTextChoose, GROUP_TYPE::TEXT);

				///////
				
			}
		}
		else if (GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::ART))
		{
			if (!m_isCreated)
			{
				m_isCreated = true;

				SoundManager::GetInst()->playSFX(SFX::monitor_login);

				GameManager::GetInst()->SetSceneAcsess(SCENE_TYPE::PM, true); 

				CTextChoose* pTextChoose = new CTextChoose;
				LPCWSTR m_txt[5] =
				{ L"������ ������ ������?",
					L"> �ִ´�     ",
					L"> ���� �ʴ´� ",
					L"������� ���� ������, �������� ���� �Ծ�ġ���.\n[�ͱ��� �ͱ��ۡ� ����-]",
					L"[MASTER] ������ 66% �ϼ��Ǿ���." };
				bool isChooseText[5] = { false, true, true, false, false }; // ���� ���ڿ� �� �������� �� �κ�... �Ф�
				pTextChoose->SetTXTInfo(m_txt, 5, isChooseText);
				PORTAIT_TYPE _type[5] = { PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::PLAYER_SMILE };
				pTextChoose->SetPortrait(_type, 5);
				CreateObject(pTextChoose, GROUP_TYPE::INTERACTIVE);
			}
		}
		else if (GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::DS))
		{
			if (!m_isCreated)
			{
				m_isCreated = true;
				
				SoundManager::GetInst()->playSFX(SFX::monitor_login);

				GameManager::GetInst()->SetSceneAcsess(SCENE_TYPE::ART, true);
				CTextChoose* pTextChoose = new CTextChoose;
				LPCWSTR m_txt[5] =
				{ L"��ȹ�� ������ ������?",
					L"> �ִ´�     ",
					L"> ���� �ʴ´� ",
					L"������� ���� ������,\n�������� ���� �Ծ�ġ���.\n[�ͱ��� �ͱ��ۡ� ����-]",
					L"[MASTER] ������ 33% �ϼ��Ǿ���." };
				bool isChooseText[5] = { false, true, true, false, false };
				PORTAIT_TYPE _type[5] = { PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::PLAYER_BASIC,PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::DEFAULT,PORTAIT_TYPE::PLAYER_SMILE };
				pTextChoose->SetPortrait(_type, 5);
				CreateObject(pTextChoose, GROUP_TYPE::INTERACTIVE);
				pTextChoose->SetTXTInfo(m_txt, 5, isChooseText);
				CreateObject(pTextChoose, GROUP_TYPE::INTERACTIVE);
			}
		}
		else
		{
			if (!m_isCreated)
			{
				m_isCreated = true;

				SoundManager::GetInst()->playSFX(SFX::monitor_login);

				CTextBox* pTextBox = new CTextBox;
				LPCWSTR m_txt[1] = { L"������ ã�ƾ� �� �� ����. \n�ֺ��� �ѷ�����"};
				pTextBox->SetTXTInfo(m_txt, 1);
				PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::PLAYER_BASIC };
				pTextBox->SetPortrait(_type, 1);
				CreateObject(pTextBox, GROUP_TYPE::INTERACTIVE);

			}
		}
	}
}

void CComputer::OnCollisionExit(CCollider* _pOther)
{
	m_isFloating = false;
}
