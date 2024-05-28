#include "pch.h"
#include "CScene_Opening.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CCollisionMgr.h"

#include "CBackground.h"

#include "Camera.h"
#include "SoundManager.h"

#include "CInteractive.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "GameManager.h"

#include "CKeyMgr.h"
#include "CObject.h"
#include "CAnagram.h"
#include "CAnimator.h"
#include "CTextBox.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CStaticObject.h"
#include "CProfessorAnim.h"
#include "CProfessorAnim_1.h"

#include "SoundManager.h"


CScene_Opening::CScene_Opening()
	: m_pBackground(nullptr)
	, m_SceneCount(0)
	, m_TextBoxCount(0)
	, m_pAnagram(nullptr)
	, m_pTextBox(nullptr)
	, m_CreateTextBox(false)
	, m_IsEnter(false)
	, m_Timer(0.f)
	, m_pTextBox2(nullptr)
	, m_pLogo(nullptr)
	//, m_pFloatingTex(nullptr)
	//, m_isFloating(false)
	, m_pProfessorAnim_0(nullptr)
	, m_pProfessorAnim_1(nullptr)
{
	m_skipTime = 1.f;
	m_Time = 1.f;
	m_IsExitScene = false;
}

CScene_Opening::~CScene_Opening()
{
}

void CScene_Opening::Enter()
{
	SoundManager::GetInst()->playBGM(BGM::StillNoOpen_A);
	SoundManager::GetInst()->playSFX(SFX::keyboard_typing);


	Camera::GetInst()->FadeIn(2.f);

	// �� ���� �ؽ�ó �迭���� �޾���
	op_SceneArr[0] = L"BGOS_Monitor_professer_clock";
	op_SceneArr[1] = L"BGOS_Clock_10_59PM";
	op_SceneArr[2] = L"BGOS_Clock_11_00PM";
	op_SceneArr[3] = L"BGOS_MoniterMail";
	op_SceneArr[4] = L"BGOS_MoniterMail_MouseUp";
	op_SceneArr[5] = L"BGOS_Mail1";
	op_SceneArr[6] = L"BGOS_Mail2";
	op_SceneArr[7] = L"BGOS_BlackOut";
	op_SceneArr[8] = L"BGOS_Logo_JumpSquare";
	op_SceneArr[9] = L"BGOS_Monitor_professer_clock";
	op_SceneArr[10] = L"BGOS_Clock_10_59PM";
	//SceneArr[9] = L"Background_CreditTex";
	//SceneArr[10] = L"Background_LogoTex";


	op_TextureArr[0] = L"texture\\opening_cutscene\\final\\1. �߱� �ƽ�.bmp";
	op_TextureArr[1] = L"texture\\opening_cutscene\\final\\2. 59.bmp";
	op_TextureArr[2] = L"texture\\opening_cutscene\\final\\3. 11.bmp";
	op_TextureArr[3] = L"texture\\opening_cutscene\\final\\4. mail_03.bmp";
	op_TextureArr[4] = L"texture\\opening_cutscene\\final\\5. mail_03.bmp";
	op_TextureArr[5] = L"texture\\opening_cutscene\\final\\6. opening_cutscene_Mail_1.bmp";
	op_TextureArr[6] = L"texture\\opening_cutscene\\final\\7. opening_cutscene_Mail_2.bmp";
	op_TextureArr[7] = L"texture\\opening_cutscene\\final\\8.bmp";
	op_TextureArr[8] = L"texture\\opening_cutscene\\final\\title.bmp";
	op_TextureArr[9] = L"texture\\ORYU_TEST\\testmy2.bmp";
	op_TextureArr[10] = L"texture\\ORYU_TEST\\testmy1.bmp";

	//TextureArr[8] = L"texture\\opening_cutscene\\ending_test\\ending_monitor.bmp";
	//TextureArr[9] = L"texture\\opening_cutscene\\ending_test\\ending_credit.bmp";
	//TextureArr[10] = L"texture\\opening_cutscene\\ending_test\\ending_logo.bmp";


	// Background 
	m_pBackground = new CBackground;
	m_pBackground->SetName(L"m_pBackground_op");
	m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(op_SceneArr[0], op_TextureArr[0]));
	AddObject(m_pBackground, GROUP_TYPE::BACKGROUND);

	// Anagram
	// m_pAnagram = new CAnagram;
	// AddObject(m_pAnagram, GROUP_TYPE::BACKGROUND);

	// TextBox
	m_pTextBox = new CTextBox;
	//m_pTextBox2 = new CTextBox;

	// =======
	// Scene_3
	// =======
	// �ֱ����� ���
	Ending_Scene3_StringVec.push_back(L"�� �㿡 ���� �����̾�.");

	// =======
	// Scene_4
	// =======


	// =======
	// Scene_5
	// =======
	// �ý��� ���


	// �÷��� �̹��� �ؽ�ó �ε�
	/*m_pFloatingTex = new CFloating;
	m_pFloatingTex->SetTexture(CResMgr::GetInst()->LoadTexture
	(L"EndingFloatingTex", L"texture\\Floating_Test.bmp"));*/

	// ProfessorAnim
	m_pProfessorAnim_0 = new CProfessorAnim;
	m_pProfessorAnim_0->SetName(L"m_pProfessorAnim_0");
	AddObject(m_pProfessorAnim_0, GROUP_TYPE::BACKGROUND);

	m_pProfessorAnim_1 = new CProfessorAnim_1;
	m_pProfessorAnim_1->SetName(L"m_pProfessorAnim_1");
	AddObject(m_pProfessorAnim_1, GROUP_TYPE::BACKGROUND);

	m_pLogo = new CStaticObject;
	m_pLogo->SetTexture(CResMgr::GetInst()->LoadTexture(L"BGOS_Logo_JumpSquare", L"texture\\opening_cutscene\\final\\title.bmp"));
	m_pLogo->SetTexPos(Vec2(0.f, 0.f));
	m_pLogo->SetVisible(false);

	AddObject(m_pLogo, GROUP_TYPE::BACKGROUND);
}


void CScene_Opening::Enter_Scene()
{
	m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture
	(op_SceneArr[m_SceneCount], op_TextureArr[m_SceneCount]));

	m_IsEnter = true;

}

void CScene_Opening::SceneUpdate()
{
	switch (m_SceneCount)
	{
	case 0: Scene_0();		break;
	case 1: Scene_1();		break;
	case 2: Scene_2();		break;
	case 3: Scene_3();		break;
	case 4: Scene_4();		break;
	case 5: Scene_5();		break;
	case 6: Scene_6();		break;
	case 7: Scene_7();		break;
	case 8: Scene_8();		break;
	case 9: Scene_9();		break;
	case 10: Scene_10();	break;
	}

	if (m_IsExitScene)
	{
		Next_Scene();
	}
	/*if (KEY_TAP(KEY::SPACE))
	{
		m_SceneCount++;
		m_IsEnter = false;
	}*/
}


// [Ű���� Ÿ����]
// ����� �� ������ / �ڿ� �ð� 1
void CScene_Opening::Scene_0()
{
	if (!m_IsEnter)
	{
		Enter_Scene();
	}

	m_Timer += fDT;

	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;
		m_SceneCount++;
		m_IsEnter = false;

	}
}


//[�ð� ȭ�� Ŭ�����] 10 : 59
// �� 11�ø� ����Ű�� �ִ� �ð� -> 2 (2��)
void CScene_Opening::Scene_1()
{
	if (!m_IsEnter)
	{
		Camera::GetInst()->FadeIn(1.f);
		Enter_Scene();
	}

	m_Timer += fDT;


	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;

		m_SceneCount++;
		m_IsEnter = false;

	}


}

// [�ð� ȭ�� Ŭ�����] 11 : 00
// �� 11�ø� ����Ű�� �ִ� �ð� -> 2 (2��)
void CScene_Opening::Scene_2()
{
	if (!m_IsEnter)
	{
		//Camera::GetInst()->FadeIn(1.f);

		Enter_Scene();
	}

	m_Timer += fDT;


	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;

		m_SceneCount++;
		m_IsEnter = false;
	}
}


//
// [���� ���� ����]
// -���� �ΰ� ����� �����
// ���� �㿡 ���� �����̾�.��
void CScene_Opening::Scene_3()
{
	if (!m_IsEnter)
	{
		for (UINT i = 0; i < 1; i++)
		{
			m_Scene3Arr[i] = Ending_Scene3_StringVec[i];
		}

		Camera::GetInst()->FadeIn(1.f);

		Enter_Scene();
		SoundManager::GetInst()->playSFX(SFX::message_tone);

		m_pTextBox->SetTXTInfo(m_Scene3Arr, 1);
		PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::PLAYER_BASIC };
		m_pTextBox->SetPortrait(_type, 1);
	}

	m_Timer += fDT;

	if (1.f <= m_Timer && !m_CreateTextBox)
	{
		AddObject(m_pTextBox, GROUP_TYPE::INTERACTIVE);
		m_CreateTextBox = true;

	}

	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;

		m_TextBoxCount++;


		if (GameManager::GetInst()->GetTextEnd() && 1 <= m_TextBoxCount)
		{
			GameManager::GetInst()->SetTextEnd(false);

			m_SceneCount++;
			m_IsEnter = false;

		}
	}
}


// ���콺 �����Ͱ� ���� �ΰ� ���� �ö󰣴�. 4
// [���콺 Ŭ����]
void CScene_Opening::Scene_4()
{
	if (!m_IsEnter)
	{
		//Camera::GetInst()->FadeIn(1.f);

		Enter_Scene();
	}

	m_Timer += fDT;


	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;

		m_SceneCount++;
		m_IsEnter = false;
		SoundManager::GetInst()->playSFX(SFX::mouse_click);

	}



}

// ���� ȭ�� â 5 , 6 (���콺 Ŀ�� ���ٰ� �ִ� ��� �ϳ���)
void CScene_Opening::Scene_5()
{
	if (!m_IsEnter)
	{
		Camera::GetInst()->FadeIn(1.f);

		Enter_Scene();
	}

	m_Timer += fDT;

	if (m_Time <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;

		m_SceneCount++;
		m_IsEnter = false;

	}
}


// ���� ȭ�� â 5 , 6 (���콺 Ŀ�� ���ٰ� �ִ� ��� �ϳ���) -> ���콺 Ŀ�� �ö󰡸� Ŭ����
void CScene_Opening::Scene_6()
{
	if (!m_IsEnter)
	{
		Enter_Scene();
	}

	m_Timer += fDT;

	if (m_Time <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::mouse_click);

		SoundManager::GetInst()->playSFX(SFX::ghost_whispering_1);

		m_SceneCount++;
		m_IsEnter = false;

	}
}

// ����
void CScene_Opening::Scene_7()
{
	if (!m_IsEnter)
	{
		Enter_Scene();
		
	}

	m_Timer += fDT;

	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		

		m_Timer = 0.f;

		m_SceneCount++;
		m_IsEnter = false;

		SoundManager::GetInst()->playSFX(SFX::logo_lending);

	}
}


// �ͽ� �ӻ��� ���� & 1�� �� �ΰ� ���������� �˾�
void CScene_Opening::Scene_8()
{
	if (!m_IsEnter)
	{
		m_IsEnter = true;
		m_pLogo->SetVisible(true);
	}

	m_Timer += fDT;



	if (m_skipTime <= m_Timer && KEY_TAP(KEY::SPACE))
	{
		DeleteObject(m_pLogo);
		m_Timer = 0.f;
		//m_IsExitScene = true;
		//Next_Scene();
		m_SceneCount++;
		m_IsEnter = false;
		//SoundManager::GetInst()->playSFX(SFX::heavy_sound);


	}
}

//������ �ִϸ��̼�-1
void CScene_Opening::Scene_9()
{
	if (!m_IsEnter)
	{
		Enter_Scene();
		m_pProfessorAnim_0->GetAnimator()->Play(L"ProfessorAnim_1", false);
	}

	m_Timer += fDT;

	if (4.8f <= m_Timer)
	{
		m_Timer = 0.f;

		DeleteObject(m_pProfessorAnim_0);

		m_SceneCount++;
		m_IsEnter = false;
	}
}

//������ �ִϸ��̼�-2
void CScene_Opening::Scene_10()
{
	if (!m_IsEnter)
	{
		Enter_Scene();
		m_pProfessorAnim_1->GetAnimator()->Play(L"ProfessorAnim_2", false);
	}

	m_Timer += fDT;
	if (4.4f <= m_Timer)
	{
		m_pProfessorAnim_1->GetAnimator()->StopFrame(L"ProfessorAnim_2", 10);

		if (KEY_TAP(KEY::SPACE))
		{
			m_Timer = 0.f;

			DeleteObject(m_pProfessorAnim_1);

			m_IsExitScene = true;

			m_SceneCount++;
			m_IsEnter = false;
		}
	}
}

void CScene_Opening::Next_Scene()
{
	if (m_IsExitScene)
	{
		CSceneMgr::GetInst()->changeScene(SCENE_TYPE::MONITER_AI);
	}

}


void CScene_Opening::Exit()
{
	//	CCollisionMgr::GetInst()->Reset();
	//	GameManager::GetInst()->SetPreScene(SCENE_TYPE::OPENING);
	SoundManager::GetInst()->stopBGM();

}


