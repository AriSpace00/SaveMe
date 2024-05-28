#include "pch.h"
#include "CInteractive.h"

#include "CCollider.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTextBox.h"
#include "CPuzzle_DoorLock.h"
#include "GameManager.h"
#include "CPuzzle_Frame.h"
#include "CTextChoose.h"
#include "CPortrait.h"
#include "CPuzzle_Clock.h"
#include "CPuzzle_ABC.h"
#include "CQR.h"
#include "SoundManager.h"


CInteractive::CInteractive()
	: m_pTex(nullptr), m_txt{}, m_isChoose {}, m_framenum(), m_isCreated(), m_isFloating(), m_type(), m_textCount()
{
	CreateCollider();

	GetCollider()->SetScale(Vec2(200.f, 200.f));
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp");
	m_fTex = CResMgr::GetInst()->LoadTexture(L"FloatingTex", L"texture\\ui\\floating_UI.bmp");

}

CInteractive::~CInteractive()
{
}

void CInteractive::SetTexture(CTexture* _tex)
{
	// ������ ������ �� �̹��� �������ֱ�
	// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player\\sd_sprite_sheet.bmp"); -> �÷��̼� �ؽ��� ����
	m_pTex = _tex;
}

void CInteractive::SetType(INTERACTIVE_TYPE _type)
{
	m_type = _type;
}

void CInteractive::initCenterPos()
{
	// ȭ�� ũ�⸦ �������� ���� ��ġ�� �����־�� �Ѵ�

	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos�� ���÷��� ���� �߾����� ����
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}
void CInteractive::SetScale(Vec2 _scale)
{
	GetCollider()->SetScale(_scale);
}

void CInteractive::update()
{
	// ��ġ�� �ϴ��� �����̴ϱ� �� ������ ���� ��..?
	// �浹 ���� ������Ʈ�� ������ �ݸ��� �Ŵ������� �ϴ°���
	//Vec2 vPos = GetPos();
	//SetPos(vPos);
	//createFloatingUI();
	//createTextBox();
}

void CInteractive::render(HDC _dc)
{

	Vec2 vPos = GetPos();

	// floatingUI
	if (m_isFloating && GameManager::GetInst()->GetInteractionStatus(m_type))
	{
		/*BitBlt(_dc,
			(int)vPos.x - m_fTex->Width() / 2,
			(int)vPos.y - 120,
			m_fTex->Width(), m_fTex->Height(),
			m_fTex->GetDC(),
			0, 0,
			SRCCOPY);*/

		TransparentBlt(_dc,
			(int)vPos.x - m_fTex->Width() / 2,
			(int)vPos.y - 120,
			m_fTex->Width(), m_fTex->Height(),
			m_fTex->GetDC(),
			0, 0,
			m_fTex->Width(), m_fTex->Height(),
			RGB(106, 255, 0));
	}

	// collision
	component_render(_dc);
}

void CInteractive::OnCollisionEnter(CCollider* _pOther)
{
	m_isFloating = true;
	m_isCreated = false;
	
}

void CInteractive::OnCollision(CCollider* _pOther)
{
	// oncollision ���� ��ȣ�ۿ� �� ��� â ����
	// oncollision ���� �÷��� UI ����
	// ���� ���� ��, �ݶ��̴� �Ŵ������� ����� -> �� ������ ������Ʈ
	if (KEY_TAP(KEY::SPACE))
	{
		m_isFloating = false;

		switch (m_type)
		{
			case INTERACTIVE_TYPE::PUZZLE_DOORLOCK:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK)&&!GameManager::GetInst()->GetSceneAcsess(SCENE_TYPE::LOBBY))
				{
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, false);
				
					CPuzzle_DoorLock* pPuzzle_DoorLock = new CPuzzle_DoorLock;
					CreateObject(pPuzzle_DoorLock, GROUP_TYPE::TEXT);
				}
				break;
			}
			case INTERACTIVE_TYPE::PUZZLE_PM:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM))
				{
					CPuzzle_ABC* pPuzzle_PM = new CPuzzle_ABC;
					CreateObject(pPuzzle_PM, GROUP_TYPE::TEXT);
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM, false);


				}
				
			}
			break;
			case INTERACTIVE_TYPE::PUZZLE_DS:
			{
				//if(���ӸŴ������� Ŭ����� �޾��)
				// �ֳĸ�? ���� ������Ʈ�� �ѹ��� �����ϱ� ����
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS))
				{
					SoundManager::GetInst()->playSFX(SFX::laptop);

					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DS, false);

					CPuzzle_Clock* pPuzzle_Clock = new CPuzzle_Clock;
					CreateObject(pPuzzle_Clock, GROUP_TYPE::TEXT);
				}
				break;
			}
			case INTERACTIVE_TYPE::PUZZLE_ART:
			{
				if (!mm_isCreated && GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_ART))
				{
					mm_isCreated = true;

					SoundManager::GetInst()->playSFX(SFX::color_change);

					CPuzzle_Frame* pPuzzle_Frame = new CPuzzle_Frame;
					pPuzzle_Frame->SetFramenum(m_framenum);
					pPuzzle_Frame->initCenterPos();
					CreateObject(pPuzzle_Frame, GROUP_TYPE::INTERACTIVE);
				}
				break;
			}
			case INTERACTIVE_TYPE::CHOOSE:
			{
				
				if (!m_isCreated && GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::CHOOSE))
				{
					m_isCreated = true;

					CTextChoose* pTextChoose = new CTextChoose;
					pTextChoose->SetTXTInfo(m_txt, m_textCount, m_isChoose);
					CreateObject(pTextChoose, GROUP_TYPE::TEXT);
				}
					break;
			}
			case INTERACTIVE_TYPE::TEXTBOX:
			{
				if (!m_isCreated)
				{
					m_isCreated = true;

					CTextBox* pTextBox = new CTextBox;
					pTextBox->SetTXTInfo(m_txt, m_textCount);
					PORTAIT_TYPE portype[1];
					
					if (m_txt[0] == L"���� �Խ��ǿ� ���� �����ִ� �� ����.")
					{
						SoundManager::GetInst()->playSFX(SFX::notice);
						portype[0] = PORTAIT_TYPE::PLAYER_BASIC;

						CQR* pQR = new CQR;
						pQR->SetQrNum(1);
						CreateObject(pQR, GROUP_TYPE::TEXT);
						SoundManager::GetInst()->playSFX(SFX::notice);
					}
					if (m_txt[0] == L"�ƹ� ������ ����.")
					{
						SoundManager::GetInst()->playSFX(SFX::notice);
						portype[0] = PORTAIT_TYPE::PLAYER_BASIC;
					}
					if (m_txt[0] == L"00010101010010101110101000.....%$%^\n$%$#%^........001011110111011")
					{
						SoundManager::GetInst()->playSFX(SFX::zero_one_1);
						portype[0] = PORTAIT_TYPE::PLAYER_SURPRISE;

					}
					if (m_txt[0] == L"10010110010111010101010101010101001")
					{
						SoundManager::GetInst()->playSFX(SFX::zero_one_2);
						portype[0] = PORTAIT_TYPE::PLAYER_PANIC;

					}
					if (m_txt[0] == L"000101010100.....%$%^\n$%$#%^........001011110111011")
					{
						SoundManager::GetInst()->playSFX(SFX::zero_one_1);
						portype[0] = PORTAIT_TYPE::PLAYER_SURPRISE;

					}

					pTextBox->SetPortrait(portype, 1);
					CreateObject(pTextBox, GROUP_TYPE::TEXT);

					
				}
				break;
			}
			case INTERACTIVE_TYPE::QR:
			{
				if (!m_isCreated)
				{
					m_isCreated = true;

					CQR* pQR = new CQR;
					pQR->SetQrNum(m_QR_Texnum);
					CreateObject(pQR, GROUP_TYPE::TEXT);
					SoundManager::GetInst()->playSFX(SFX::notice);

					

				}
				break;
			}
			default:
				break;
		}
	}
}

void CInteractive::OnCollisionExit(CCollider* _pOther)
{
	m_isFloating = false;
}


