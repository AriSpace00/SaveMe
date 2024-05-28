#include "pch.h"
#include "CTextChoose.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"
#include "TextManager.h"
#include "CKeyMgr.h"
#include "GameManager.h"
#include "CStaticObject.h"
#include "CBackground.h"
#include "CCom_Anim.h"
#include "CInteractive.h"
#include "SoundManager.h"
#include "AI_TextObj.h"
#include "CTimeMgr.h"


CTextChoose::CTextChoose()
	:isChooseText{}
	, arrPortait{}
	, m_txt{}
	, m_fontSize(30)
	, m_stringArr{}
{
	GameManager::GetInst()->SetMovable(false);

	m_pTex = CResMgr::GetInst()->LoadTexture(L"TextBox", L"texture\\text_box.bmp");
	m_curShowText = 0;
	m_textCount = 0; 
	m_chooseNum = 0;


	// �ʻ�ȭ �ؽ��� �ʱ�ȭ
	m_pTexs[(int)PORTAIT_TYPE::DEFAULT] = nullptr;

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_BASIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// �÷��̾� �⺻

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // �÷��̾� �д�

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// �÷��̾� �ɰ�

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// �÷��̾� ���

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// �÷��̾� ������

	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // ��ȹ ����

	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // ��Ʈ ����

	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // �ù� ����

	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst()->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // ������ ����



	// ��ȭ ������ ���� 3��.
	for (UINT i = 0; i < 3; i++)
	{
		AI_TextObj* textObj = new AI_TextObj;
		textObj->SetTextData(L"���Է� ����.", m_fontSize * 2, TEXT_TYPE::NORMAL);
		m_SelectTextVec.push_back(textObj);
		CreateObject(textObj, GROUP_TYPE::TEXT);
	}

	m_stringArr[0] = L"[HATER] : �� ȭ������.";
	m_stringArr[1] = L"[HATER] : �� ��� �߾�.";
	m_stringArr[2] = L"[HATER] : �׸���.";

	

	if (m_txt[0] == L"���� ������ ������?")
	{
		//m_pTexs[arrPortait[m_curShowText] = (UINT)PORTAIT_TYPE::PLAYER_PANIC;
	}
	if (m_txt[0] == L"������ ������ ������?")
	{
		//m_pTexs[arrPortait[m_curShowText] = (UINT)PORTAIT_TYPE::PLAYER_PANIC;
	}
	if (m_txt[0] == L"��ȹ�� ������ ������?")
	{
		//m_pTexs[arrPortait[m_curShowText] = (UINT)PORTAIT_TYPE::PLAYER_PANIC;
	}

	

}

CTextChoose::~CTextChoose()
{
	GameManager::GetInst()->SetMovable(true);
}

void CTextChoose::initCenterPos()
{
	
}

void CTextChoose::update()
{
	if (m_textCount == 1)
	{
		GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);
		DeleteObject(this);
	}
}

void CTextChoose::render(HDC _dc)
{
	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos�� ���÷��� ���� �߾����� ����
	Vec2 vPos = GetPos();
	vPos.x = (int)ScreenSize.x / 2;
	vPos.y = (int)ScreenSize.y / 2;
	SetPos(vPos);

	// ��ȭâ ����
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	// �ʻ�ȭ�� DEFAULT �� ��� �ƹ��͵� �������� �ʴ´�
	if (m_pTexs[arrPortait[m_curShowText]] != nullptr)
	{
		// ��� �ʻ�ȭ�� ����� ��� ������Ʈ ����
		if (m_curShowText >= m_textCount)
		{
			//GameManager::GetInst()->SetMovable(true);
			//DeleteObject(this);
			return;
		}

		// �ʻ�ȭ ����
		vPos.x = ScreenSize.x / 2;
		vPos.y = ScreenSize.y / 2;
		SetPos(vPos);

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



	Vec2 vResolution = CCore::GetInst()->GetResolution();
	for (UINT i = 0; i < m_noCount; i++)
	{
		m_SelectTextVec[i]->SetTextData(m_stringArr[i], m_fontSize);
		m_SelectTextVec[i]->SetTextPos(Vec2((int)vResolution.x / 2 - 430,
			(int)vResolution.y / 2 - (200 - i * m_fontSize)));
		m_SelectTextVec[i]->SetVisible(true);
	}
	


	// ����� ������ �������� ���
	if (isChooseText[m_curShowText])
	{

		if (KEY_TAP(KEY::W))
		{
			m_chooseNum = 1;
			
		}
		else if (KEY_TAP(KEY::S))
		{
			m_chooseNum = 2;
		}
		else if (KEY_TAP(KEY::SPACE))
		{
			if (m_chooseNum == 1)
			{
				if (m_txt[3] == L"���� ���� �����ִ�.")
				{
					SoundManager::GetInst()->playSFX(SFX::curtain_sound);

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

					/*CStaticObject* pFilter = new CStaticObject;
					pFilter->SetPos(Vec2(0.f, 0.f));
					pFilter->SetTexture(CResMgr::GetInst()->LoadTexture(L"BG_ROOM_FILTER", L"texture\\MAP\\professor's_office\\ToneDownFilter.bmp"));
					pFilter->initCenterPos();
					CreateObject(pFilter, GROUP_TYPE::BACKGROUND);*/
				}

				TextManager::GetInst()->clearText();
				//GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::CHOOSE, false);
				GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);

				// getstatus �� Ŀư ������Ʈ���� �ۿ� �� �Ἥ ����
				GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::CHOOSE, false);


				GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::DS, false);
				GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::ART, false);
				GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::PM, false);

				if (m_curShowText >= m_textCount - 1)
				{
					DeleteObject(this);
					return;
				}
				m_curShowText += 2;
			}
			if (m_chooseNum == 2)
			{
				if (m_txt[0] == L"���� ������ ������?")
				{
					m_noCount++;
					m_curShowText = 0;
					m_chooseNum = 0;
					if (m_noCount == 4)
					{
						// ���� ���� �ڵ�
						MessageBox(NULL, L"����", L"�� ������", MB_OK | MB_ICONINFORMATION);
						GameManager::GetInst()->SetGameQuit();
					}
				}
				else
				{
					if (m_txt[3] != L"���� ���� �����ִ�.")
					{
						SoundManager::GetInst()->playSFX(SFX::warning_beep);

					}
					m_txt[m_textCount - 1] = L"�ƹ� �ϵ� �Ͼ�� �ʾҴ�.";

					m_curShowText = m_textCount - 1;
					TextManager::GetInst()->clearText();
				}
		
			}

		}


		if (m_chooseNum == 0)
		{

			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::TOP);
			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText + 1], TTYPE::MIDDLE);
		}
		if (m_chooseNum == 1)
		{
			
			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::AC_TOP);
			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText + 1], TTYPE::MIDDLE);
		}
		if (m_chooseNum == 2)
		{
			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::TOP);
			TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText + 1], TTYPE::AC_MIDDLE);
		}

	}
	// ��µ� ������ �ܼ� ����� ���
	else
	{
		// ��� ��µ� ���
		if (!TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::SUBS))
		{
			if (KEY_TAP(KEY::SPACE))
			{
				TextManager::GetInst()->clearText();

				// �غ�� �ؽ�Ʈ�� �� ��µǾ��� ����

				if (m_curShowText >= m_textCount - 1)
				{
					// GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::CHOOSE, true);
					if (m_textCount == 4)
					{
						// ���⼭ ����� ai ���� ����� �ִϸ��̼�����
					// ����� �ִϸ��̼��� ����Ʈ �Ǳ� ���� �Ʒ� ���� ȣ��
						if (m_txt[3] == L"���� ���� �����ִ�.")
						{
							

						}
						else if(m_txt[0] == L"���� ������ ������?")

						{
							/// Ȯ�� �ʿ�! ///
							/// ��ǻ�� ��ƿ�� ������ �Ѱܾ���
							/// ��ƿ���� ������ �պκп��� ����ϱ��...
							SoundManager::GetInst()->playSFX(SFX::monitor_eating);
							GameManager::GetInst()->SetScene(SCENE_TYPE::ENDING);


						}
					}
			
					DeleteObject(this);
					return;
				}
				m_curShowText++;
				if (m_txt[3] != L"���� ���� �����ִ�." && m_curShowText == 1)
				{
					SoundManager::GetInst()->playSFX(SFX::message_tone);
				}
				if (m_txt[3] != L"���� ���� �����ִ�." && m_curShowText == 4)
				{
					SoundManager::GetInst()->playSFX(SFX::monitor_eating);
				}
			}
		}
	}
}

	
