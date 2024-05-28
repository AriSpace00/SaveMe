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


	// 초상화 텍스쳐 초기화
	m_pTexs[(int)PORTAIT_TYPE::DEFAULT] = nullptr;

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_BASIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// 플레이어 기본

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // 플레이어 패닉

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// 플레이어 쪼갬

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// 플레이어 놀람

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// 플레이어 생각중

	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // 기획 정수

	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // 아트 정수

	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // 플밍 정수

	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst()->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // 교수님 심장



	// 대화 선택지 제작 3개.
	for (UINT i = 0; i < 3; i++)
	{
		AI_TextObj* textObj = new AI_TextObj;
		textObj->SetTextData(L"미입력 상태.", m_fontSize * 2, TEXT_TYPE::NORMAL);
		m_SelectTextVec.push_back(textObj);
		CreateObject(textObj, GROUP_TYPE::TEXT);
	}

	m_stringArr[0] = L"[HATER] : 나 화낼꺼야.";
	m_stringArr[1] = L"[HATER] : 나 경고 했어.";
	m_stringArr[2] = L"[HATER] : 그만해.";

	

	if (m_txt[0] == L"논리의 정수를 넣을까?")
	{
		//m_pTexs[arrPortait[m_curShowText] = (UINT)PORTAIT_TYPE::PLAYER_PANIC;
	}
	if (m_txt[0] == L"예술의 정수를 넣을까?")
	{
		//m_pTexs[arrPortait[m_curShowText] = (UINT)PORTAIT_TYPE::PLAYER_PANIC;
	}
	if (m_txt[0] == L"기획의 정수를 넣을까?")
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
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = (int)ScreenSize.x / 2;
	vPos.y = (int)ScreenSize.y / 2;
	SetPos(vPos);

	// 대화창 렌더
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

	// 초상화가 DEFAULT 인 경우 아무것도 렌더하지 않는다
	if (m_pTexs[arrPortait[m_curShowText]] != nullptr)
	{
		// 모든 초상화를 출력한 경우 오브젝트 삭제
		if (m_curShowText >= m_textCount)
		{
			//GameManager::GetInst()->SetMovable(true);
			//DeleteObject(this);
			return;
		}

		// 초상화 렌더
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
	


	// 출력할 내용이 선택지일 경우
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
				if (m_txt[3] == L"벽에 무언가 적혀있다.")
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

				// getstatus 를 커튼 오브젝트에서 밖에 안 써서 ㄱㅊ
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
				if (m_txt[0] == L"논리의 정수를 넣을까?")
				{
					m_noCount++;
					m_curShowText = 0;
					m_chooseNum = 0;
					if (m_noCount == 4)
					{
						// 강제 종료 코드
						MessageBox(NULL, L"꺼져", L"너 누구야", MB_OK | MB_ICONINFORMATION);
						GameManager::GetInst()->SetGameQuit();
					}
				}
				else
				{
					if (m_txt[3] != L"벽에 무언가 적혀있다.")
					{
						SoundManager::GetInst()->playSFX(SFX::warning_beep);

					}
					m_txt[m_textCount - 1] = L"아무 일도 일어나지 않았다.";

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
	// 출력될 내용이 단순 대사인 경우
	else
	{
		// 모두 출력된 경우
		if (!TextManager::GetInst()->printSTDTXT(m_txt[m_curShowText], TTYPE::SUBS))
		{
			if (KEY_TAP(KEY::SPACE))
			{
				TextManager::GetInst()->clearText();

				// 준비된 텍스트가 다 출력되었을 굥우

				if (m_curShowText >= m_textCount - 1)
				{
					// GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::CHOOSE, true);
					if (m_textCount == 4)
					{
						// 여기서 모니터 ai 말고 모니터 애니메이션으로
					// 모니터 애니메이션은 딜리트 되기 전에 아래 내용 호출
						if (m_txt[3] == L"벽에 무언가 적혀있다.")
						{
							

						}
						else if(m_txt[0] == L"논리의 정수를 넣을까?")

						{
							/// 확인 필요! ///
							/// 컴퓨터 우걱우걱 씬으로 넘겨야함
							/// 우걱우걱은 엔딩씬 앞부분에서 재생하기로...
							SoundManager::GetInst()->playSFX(SFX::monitor_eating);
							GameManager::GetInst()->SetScene(SCENE_TYPE::ENDING);


						}
					}
			
					DeleteObject(this);
					return;
				}
				m_curShowText++;
				if (m_txt[3] != L"벽에 무언가 적혀있다." && m_curShowText == 1)
				{
					SoundManager::GetInst()->playSFX(SFX::message_tone);
				}
				if (m_txt[3] != L"벽에 무언가 적혀있다." && m_curShowText == 4)
				{
					SoundManager::GetInst()->playSFX(SFX::monitor_eating);
				}
			}
		}
	}
}

	
