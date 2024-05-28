#include "pch.h"
#include "CScene_Ending.h"

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
#include "CFloating.h"
#include "AI_TextObj.h"

#include "SoundManager.h"

#include "CStaticObject.h"

// ���� ���� ���̴ϴ� - �����
// ���� ���ϵ���� - ���ؼ�
// �� �ڵ� ¼�׿�. �� ���ڽ��ϴ� - ������

CScene_Ending::CScene_Ending()
	: m_pBackground(nullptr)
	, m_SceneCount(0)
	, m_TextBoxCount(0)
	, m_pAnagram(nullptr)
	, m_pTextBox(nullptr)
	, m_CreateTextBox(false)
	, m_IsEnter(false)
	, m_Timer(0.f)
	, m_pTextBox2(nullptr)
	, m_pFloatingTex(nullptr)
	, m_isFloating(false)
	, m_AIObjVec{}
	, m_fontSize(30)
	, m_talkIndex(0)
	, m_pLogo(nullptr)
{
}

CScene_Ending::~CScene_Ending()
{
}

void CScene_Ending::Enter()
{
	SoundManager::GetInst()->playBGM(BGM::SheDiedUp);

	Camera::GetInst()->FadeIn(2.f);

	// �� ���� �ؽ�ó �迭���� �޾���
	SceneArr[0] = L"Ending_01";
	SceneArr[1] = L"Ending_02";
	SceneArr[2] = L"Ending_03";
	SceneArr[3] = L"Ending_04";
	SceneArr[4] = L"Ending_05";
	SceneArr[5] = L"Ending_06";
	SceneArr[6] = L"Ending_07";
	SceneArr[7] = L"Ending_08";
	SceneArr[8] = L"Ending_09";
	SceneArr[9] = L"Ending_10";
	SceneArr[10] = L"Ending_11";
	SceneArr[11] = L"Ending_12";
	SceneArr[12] = L"Ending_13";
	SceneArr[13] = L"Ending_14";
	SceneArr[14] = L"Ending_15";
	SceneArr[15] = L"Ending_16";
	SceneArr[16] = L"Ending_17";
	SceneArr[17] = L"Ending_18";
	SceneArr[18] = L"Ending_19";
	SceneArr[19] = L"Ending_20";
	SceneArr[20] = L"Ending_21";
	SceneArr[21] = L"Ending_22";
	SceneArr[22] = L"Ending_23";
	SceneArr[23] = L"Ending_24";
	SceneArr[24] = L"Ending_25";
	SceneArr[25] = L"Ending_26";
	SceneArr[26] = L"Ending_27";
	SceneArr[27] = L"Ending_28";
	SceneArr[28] = L"Ending_29";

	TextureArr[0] = L"texture\\ending_cutscene\\1980X1080\\01.bmp";
	TextureArr[1] = L"texture\\ending_cutscene\\1980X1080\\02.bmp";
	TextureArr[2] = L"texture\\ending_cutscene\\1920X1080\\03.bmp";
	TextureArr[3] = L"texture\\ending_cutscene\\1920X1080\\04.bmp";
	TextureArr[4] = L"texture\\ending_cutscene\\1980X1080\\05.bmp";
	TextureArr[5] = L"texture\\ending_cutscene\\1980X1080\\06.bmp";
	TextureArr[6] = L"texture\\ending_cutscene\\1920X1080\\07.bmp";
	TextureArr[7] = L"texture\\ending_cutscene\\1920X1080\\08.bmp";
	TextureArr[8] = L"texture\\ending_cutscene\\1920X1080\\09.bmp";
	TextureArr[9] = L"texture\\ending_cutscene\\1980X1080\\10.bmp";
	TextureArr[10] = L"texture\\ending_cutscene\\1980X1080\\11.bmp";
	TextureArr[11] = L"texture\\ending_cutscene\\1920X1080\\12.bmp";
	TextureArr[12] = L"texture\\ending_cutscene\\1980X1080\\13.bmp";
	TextureArr[13] = L"texture\\ending_cutscene\\1920X1080\\14.bmp";
	TextureArr[14] = L"texture\\ending_cutscene\\1920X1080\\15.bmp";
	TextureArr[15] = L"texture\\ending_cutscene\\1980X1080\\16.bmp";
	TextureArr[16] = L"texture\\ending_cutscene\\1920X1080\\17.bmp";
	TextureArr[17] = L"texture\\ending_cutscene\\1920X1080\\18.bmp";
	TextureArr[18] = L"texture\\ending_cutscene\\1980X1080\\19.bmp";
	TextureArr[19] = L"texture\\ending_cutscene\\1920X1080\\20.bmp";
	TextureArr[20] = L"texture\\ending_cutscene\\1920X1080\\21.bmp";
	TextureArr[21] = L"texture\\ending_cutscene\\1920X1080\\22.bmp";
	TextureArr[22] = L"texture\\ending_cutscene\\1920X1080\\23.bmp";
	TextureArr[23] = L"texture\\ending_cutscene\\1920X1080\\24.bmp";
	TextureArr[24] = L"texture\\ending_cutscene\\1920X1080\\25_2.bmp";
	TextureArr[25] = L"texture\\ending_cutscene\\1920X1080\\26.bmp";
	TextureArr[26] = L"texture\\ending_cutscene\\1920X1080\\27.bmp";
	TextureArr[27] = L"texture\\ending_cutscene\\1920X1080\\28.bmp";	// ũ����
	TextureArr[28] = L"texture\\ending_cutscene\\1920X1080\\29.bmp";

	// Background 
	m_pBackground = new CBackground;
	m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture
	(SceneArr[0], TextureArr[0]));
	AddObject(m_pBackground, GROUP_TYPE::BACKGROUND);

	// Anagram
	m_pAnagram = new CAnagram;
	AddObject(m_pAnagram, GROUP_TYPE::BACKGROUND);

	// TextBox
	m_pTextBox = new CTextBox;
	m_pTextBox2 = new CTextBox;
	m_pTextBox3 = new CTextBox;
	m_pTextBox4 = new CTextBox;
	m_pTextBox5 = new CTextBox;
	m_pTextBox6 = new CTextBox;
	m_pTextBox7 = new CTextBox;

	// Hater ���
	Ending_Hater_StringVec.push_back(L"[������ �ʿ��� �� ������ ���� ���ʾ�.]");
	Ending_Hater_StringVec.push_back(L"[�׷��� �� ������ ����.]");
	Ending_Hater_StringVec.push_back(L"[���� ����]");
	Ending_Hater_StringVec.push_back(L"[����]");
	Ending_Hater_StringVec.push_back(L"[���� ���� ����]");
	Ending_Hater_StringVec.push_back(L"[���� ���� ���� ���� ����]");
	Ending_Hater_StringVec.push_back(L"[���� �� ������ ���� ����־�!!]");
	Ending_Hater_StringVec.push_back(L"[���� ���常�� �� ���� ������ ���� �� �ְŵ�]");
	Ending_Hater_StringVec.push_back(L"[������ ĳ���Ͱ� ������ ���� ������ ����]");
	Ending_Hater_StringVec.push_back(L"[�� ���� �� ������ ��� �� ����]");
	Ending_Hater_StringVec.push_back(L"[��������!!!!!!!!!!!!!!!]");
	Ending_Hater_StringVec.push_back(L"[������������!!!!!!!!!!!!!!]");
	Ending_Hater_StringVec.push_back(L"[����������������������!!!!!!!]");
	Ending_Hater_StringVec.push_back(L"[�ȵ�]");
	Ending_Hater_StringVec.push_back(L"[�׸�]");
	Ending_Hater_StringVec.push_back(L"[�׸���!!!!!!]");
	Ending_Hater_StringVec.push_back(L"[����]");
	Ending_Hater_StringVec.push_back(L"[���� ���� ����]");
	Ending_Hater_StringVec.push_back(L"[���� ���� ���� ���� ����]");

	// ������ ���
	Ending_PF_StringVec.push_back(L"������ ����� �� ��� ������");
	Ending_PF_StringVec.push_back(L"���� �˾Ҿ�.");
	Ending_PF_StringVec.push_back(L"�� ��ﳪ.");
	Ending_PF_StringVec.push_back(L"�� ���� �� �žߡ� �� ���̳��� �� ���̰�");
	Ending_PF_StringVec.push_back(L"����? ���� �� ������ �÷��̾� ĳ���;�.");
	Ending_PF_StringVec.push_back(L"�׸��� �ʴ¡� ���ϱ");
	Ending_PF_StringVec.push_back(L"��Ź�Ұԡ� �� ������ �����ࡦ");
	Ending_PF_StringVec.push_back(L"�ð��̡� �󸶡� ���.");
	Ending_PF_StringVec.push_back(L"����.");

	// �ý��� ���
	Ending_System_StringVec.push_back(L"���������� ������ �����. �ǰ� ���� �帥��.");
	Ending_System_StringVec.push_back(L"[HEART]�� ȹ���ߴ�.");
	Ending_System_StringVec.push_back(L"������� ���� ������, �ǰ� �帣�� ������ �Ծ� ġ���.");
	Ending_System_StringVec.push_back(L"�ͱ��� �ͱ��ۡ� ����-");
	Ending_System_StringVec.push_back(L"HEART >> SAVEME ������ �ϼ� �Ǿ����ϴ�.");

	// �÷��� �̹��� �ؽ�ó �ε�
	m_pFloatingTex = new CFloating;
	m_pFloatingTex->SetTexture(CResMgr::GetInst()->LoadTexture
	(L"EndingFloatingTex", L"texture\\Floating_Test.bmp"));


	// AI ��ȭ �ؽ�Ʈ
	//TODO : ����Ϳ� �� HATER ����ε� ��𼭺��� ������ �� ������ ����� ���� �������� ���ž���
	for (UINT i = 0; i < Ending_Hater_StringVec.size(); i++)
	{
		AI_TextObj* AIObj = new AI_TextObj;
		AIObj->SetTextData(Ending_Hater_StringVec[i], m_fontSize, TEXT_TYPE::NORMAL);
		m_AIObjVec.push_back(AIObj);
		AddObject(AIObj, GROUP_TYPE::MONITOR_TEXT);
	}

	m_pLogo = new CStaticObject;
	m_pLogo->SetTexture(CResMgr::GetInst()->LoadTexture(L"Ending_Logo", L"texture\\ending_cutscene\\1920X1080\\29.bmp"));
	m_pLogo->SetTexPos(Vec2(0.f, 0.f));
	m_pLogo->SetVisible(false);

	AddObject(m_pLogo, GROUP_TYPE::BACKGROUND);

}

void CScene_Ending::Enter_Scene(UINT _index)
{
	m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture
	(SceneArr[_index], TextureArr[_index]));

	m_IsEnter = true;
}

void CScene_Ending::SceneUpdate()
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
	case 11: Scene_11();	break;
	case 12: Scene_12();	break;
	case 13: Scene_13();	break;
	case 14: Scene_14();	break;
	case 15: Scene_15();	break;
	case 16: Scene_16();	break;
	case 17: Scene_17();	break;
	case 18: Scene_18();	break;
	case 19: Scene_19();	break;
	case 20: Scene_20();	break;
	case 21: Scene_21();	break;
	case 22: Scene_22();	break;
	case 23: Scene_23();	break;
	case 24: Scene_24();	break;
	case 25: Scene_25();	break;
	case 26: Scene_26();	break;
	case 27: Scene_27();	break;
	case 28: Scene_28();	break;
	case 29: Scene_29();	break;
	case 30: Scene_30();	break;
	case 31: Scene_31();	break;
	}
}

// 1��Ī �����
void CScene_Ending::Scene_0()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);

	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;

	}
}

// ���� �������
void CScene_Ending::Scene_1() 
{
	if (!m_IsEnter)
	{
		Enter_Scene(2);

	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

// ��������� ����
void CScene_Ending::Scene_2() 
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}

	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		//SoundManager::GetInst()->playSFX(SFX::message_tone);

	}
}

//  ����� ���� �ϴ� HATER ��ȭâ
void CScene_Ending::Scene_3()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		for (UINT i = 0; i < m_talkIndex; i++)
		{
			m_AIObjVec[i]->SetVisible(true);
			m_AIObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
				resolution.y / 2 + 250 - (m_talkIndex - i) * m_fontSize));
		}
		m_talkIndex++;

		if (m_talkIndex > 3)
		{
			for (UINT i = 0; i < m_talkIndex; i++)
			{
				m_AIObjVec[i]->SetVisible(false);
			}

			m_SceneCount++;
			m_IsEnter = false;
			m_Timer = 0.f;
			m_lastTalkIndex = m_talkIndex;
		}
		else if(m_talkIndex > 1)
		{
			SoundManager::GetInst()->playSFX(SFX::message_tone);

		}
	}
}

// ������� ����
void CScene_Ending::Scene_4()
{
	if (!m_IsEnter)
	{
		Enter_Scene(2);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::question);

	}
}

// �� �������?
void CScene_Ending::Scene_5()
{
	if (!m_IsEnter)
	{
		Enter_Scene(2);

		m_Scene3Arr[0] = Ending_PF_StringVec[0];

		PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::PLAYER_BASIC };
		m_pTextBox->SetTXTInfo(m_Scene3Arr, 1);
		m_pTextBox->SetPortrait(_type, 1);
		AddObject(m_pTextBox, GROUP_TYPE::TEXT);
	}

	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);
		SoundManager::GetInst()->playSFX(SFX::message_tone);

	}

}

// ��������
void CScene_Ending::Scene_6()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		for (UINT i = m_lastTalkIndex - 2; i < m_talkIndex; i++)
		{
			m_AIObjVec[i]->SetVisible(true);
			m_AIObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
				resolution.y / 2 + 250 - (m_talkIndex - i) * m_fontSize));
		}
		m_talkIndex++;

		if (m_talkIndex > 7)
		{
			for (UINT i = 0; i < m_talkIndex; i++)
			{
				m_AIObjVec[i]->SetVisible(false);
			}

			m_SceneCount++;
			m_IsEnter = false;
			m_lastTalkIndex = m_talkIndex;
			m_Timer = 0.f;

		}
		else
		{
			SoundManager::GetInst()->playSFX(SFX::message_tone);

		}
	}
}

// ������ ��ư Ŭ��
void CScene_Ending::Scene_7()
{
	if (!m_IsEnter)
	{
 		Enter_Scene(22);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::heavy_sound);

	}
	//SoundManager::GetInst()->playSFX(SFX::heavy_sound);

}

// �Ƿ� �׸� ���Ѵ� ��ȣ
void CScene_Ending::Scene_8()
{
	if (!m_IsEnter)
	{
		Enter_Scene(6);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::heavy_sound);
	}
}

// å�� �ִ� �� ȭ��
void CScene_Ending::Scene_9()
{
	if (!m_IsEnter)
	{
		Enter_Scene(7);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
 		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		//SoundManager::GetInst()->playSFX(SFX::heavy_sound);
	}
}

// â���� �ִ� SAVE ME
void CScene_Ending::Scene_10()
{
	m_SceneCount++;

}

// <1��Ī ����� ȭ��>
void CScene_Ending::Scene_11()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);

		m_Scene3Arr[0] = Ending_PF_StringVec[1];
		m_Scene3Arr[1] = Ending_PF_StringVec[2];
		m_Scene3Arr[2] = Ending_PF_StringVec[3];

		PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::PLAYER_BASIC ,PORTAIT_TYPE::PLAYER_BASIC ,PORTAIT_TYPE::PLAYER_BASIC };
		m_pTextBox2->SetTXTInfo(m_Scene3Arr, 3);
		m_pTextBox2->SetPortrait(_type, 3);
		AddObject(m_pTextBox2, GROUP_TYPE::TEXT);
	}

	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);
		SoundManager::GetInst()->playSFX(SFX::message_tone);

	}
}

// ����� ���� �ϴ� HATER ���â
void CScene_Ending::Scene_12()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		for (UINT i = m_lastTalkIndex - 2; i < m_talkIndex; i++)
		{
			m_AIObjVec[i]->SetVisible(true);
			m_AIObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
				resolution.y / 2 + 250 - (m_talkIndex - i) * m_fontSize));
		}
		m_talkIndex++;

		if (m_talkIndex > 14)
		{
			for (UINT i = 0; i < m_talkIndex; i++)
			{
				m_AIObjVec[i]->SetVisible(false);
			}

			m_SceneCount++;
			m_IsEnter = false;
			m_lastTalkIndex = m_talkIndex;
			m_Timer = 0.f;
		}
		else
		{
			SoundManager::GetInst()->playSFX(SFX::message_tone);

		}


	}
}

// ���ڿ� �ɾ� ȭ�� �� ������ �ٶ󺸴� �ּ��� ������ [HEART]
void CScene_Ending::Scene_13()
{
	if (!m_IsEnter)
	{
		Enter_Scene(11);

		m_Scene3Arr[0] = Ending_PF_StringVec[4];
		m_Scene3Arr[1] = Ending_System_StringVec[0];
		m_Scene3Arr[2] = Ending_System_StringVec[1];

		PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::PLAYER_BASIC ,PORTAIT_TYPE::DEFAULT ,PORTAIT_TYPE::HEART };
		m_pTextBox3->SetTXTInfo(m_Scene3Arr, 3);
		m_pTextBox3->SetPortrait(_type, 3);
		AddObject(m_pTextBox3, GROUP_TYPE::TEXT);
	}

	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);
	}
}

// �ֱ����� ���â �÷��� [�ʴ�..���ϱ�]
void CScene_Ending::Scene_14()
{
	if (!m_IsEnter)
	{
		Enter_Scene(11);

		m_Scene3Arr[0] = Ending_PF_StringVec[5];
		m_Scene3Arr[1] = Ending_PF_StringVec[6];
		m_Scene3Arr[2] = Ending_PF_StringVec[7];

		PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::PLAYER_BASIC ,PORTAIT_TYPE::PLAYER_BASIC ,PORTAIT_TYPE::PLAYER_BASIC };
		m_pTextBox4->SetTXTInfo(m_Scene3Arr, 3);
		m_pTextBox4->SetPortrait(_type, 3);
		AddObject(m_pTextBox4, GROUP_TYPE::TEXT);
	}
	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);

	}
}

// �ý��� - �ͱ��� �ͱ���
void CScene_Ending::Scene_15()
{
	if (!m_IsEnter)
	{
		Enter_Scene(13);

		m_Scene3Arr[0] = Ending_System_StringVec[2];
		m_Scene3Arr[1] = Ending_System_StringVec[3];
		m_Scene3Arr[2] = Ending_System_StringVec[4];

		PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::DEFAULT ,PORTAIT_TYPE::DEFAULT ,PORTAIT_TYPE::DEFAULT };
		m_pTextBox5->SetTXTInfo(m_Scene3Arr, 3);
		m_pTextBox5->SetPortrait(_type, 3);
		AddObject(m_pTextBox5, GROUP_TYPE::TEXT);
	}
	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);

	}
}

//  [1��Ī] ����� ȭ��
void CScene_Ending::Scene_16()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::message_tone);

	}
}

//  [1��Ī] ����� ȭ�� AI ���
void CScene_Ending::Scene_17()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
	{
		for (UINT i = m_lastTalkIndex - 2; i < m_talkIndex; i++)
		{
			m_AIObjVec[i]->SetVisible(true);
			m_AIObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
				resolution.y / 2 + 250 - (m_talkIndex - i) * m_fontSize));
		}
		m_talkIndex++;

		if (m_talkIndex > 17)
		{
			for (UINT i = 0; i < m_talkIndex; i++)
			{
				m_AIObjVec[i]->SetVisible(false);
			}

			m_SceneCount++;
			m_IsEnter = false;
			m_lastTalkIndex = m_talkIndex;
			m_Timer = 0.f;
			SoundManager::GetInst()->stopBGM();
			SoundManager::GetInst()->playSFX(SFX::change);
		}
		else
		{
			SoundManager::GetInst()->playSFX(SFX::message_tone);

		}
	}
}

// �ֳʱ׷�
void CScene_Ending::Scene_18()
{
	if (!m_IsEnter)
	{
		
		Enter_Scene(26);
		m_pAnagram->GetAnimator()->Play(L"Anagram", false);
	}

	m_Timer += fDT;

	if (4.f <= m_Timer)
	{
		m_pAnagram->GetAnimator()->StopFrame(L"Anagram", 14);
	}
	else if (m_Timer <= 1.f)
	{
		m_pAnagram->GetAnimator()->StopFrame(L"Anagram", 0);
	}
	else
	{
		m_pAnagram->GetAnimator()->Play(L"Anagram", false);
	}

	if (m_Timer >= 4.0f && KEY_TAP(KEY::SPACE))
	{
		DeleteObject(m_pAnagram);

		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::heavy_sound);

	}
}

//  [1��Ī] å�� ȭ��
void CScene_Ending::Scene_19()
{
	if (!m_IsEnter)
	{
		Enter_Scene(17);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

//  [1��Ī] ����� ȭ��
void CScene_Ending::Scene_20()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

//  [1��Ī] ����� ȭ�� [HEART ���]
void CScene_Ending::Scene_21()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);
		m_Scene3Arr[0] = Ending_System_StringVec[4];

		PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::HEART};
		m_pTextBox6->SetTXTInfo(m_Scene3Arr, 1);
		m_pTextBox6->SetPortrait(_type, 1);
		AddObject(m_pTextBox6, GROUP_TYPE::TEXT);
	}
	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);
	}
}

//  MASTER ���� �̹���
void CScene_Ending::Scene_22()
{
	if (!m_IsEnter)
	{
		Enter_Scene(20);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

// SAVE ME �����̹���
void CScene_Ending::Scene_23()
{
	
	if (!m_IsEnter)
	{
		Camera::GetInst()->FadeIn(1.f);
		Enter_Scene(21);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

// �̸� ���� ���Ϻ�����
void CScene_Ending::Scene_24()
{
	if (!m_IsEnter)
	{
		Camera::GetInst()->FadeIn(1.f);

		Enter_Scene(22);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

// �̸� ���� ���Ϻ����� - Ȯ��
void CScene_Ending::Scene_25()
{
	if (!m_IsEnter)
	{
		Enter_Scene(23);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::player);

	}
}

// PLAYER ���Ϻ�����
void CScene_Ending::Scene_26()
{
	if (!m_IsEnter)
	{
		Enter_Scene(24);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::receive_mail);

	}
}

// �� �簢�� �̹���
void CScene_Ending::Scene_27()
{
	if (!m_IsEnter)
	{
		Enter_Scene(25);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}

// ������� �̹���
void CScene_Ending::Scene_28()
{
	if (!m_IsEnter)
	{
		Enter_Scene(26);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 1.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playSFX(SFX::THANKS);

	}
}

// ������ '����'
void CScene_Ending::Scene_29()
{
	if (!m_IsEnter)
	{
		Enter_Scene(26);
		m_Scene3Arr[0] = Ending_PF_StringVec[8];

		PORTAIT_TYPE _type[1] = { PORTAIT_TYPE::PLAYER_BASIC };
		m_pTextBox7->SetTXTInfo(m_Scene3Arr, 1);
		m_pTextBox7->SetPortrait(_type, 1);
		AddObject(m_pTextBox7, GROUP_TYPE::TEXT);
	}
	m_Timer += fDT;

	if (GameManager::GetInst()->GetTextEnd() && KEY_TAP(KEY::SPACE) && m_Timer >= 2.5f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		GameManager::GetInst()->SetTextEnd(false);
		SoundManager::GetInst()->playSFX(SFX::logo_lending);
	}
}

// �ΰ� �̹���
void CScene_Ending::Scene_30()
{
	if (!m_IsEnter)
	{
		m_IsEnter = true;
		//Enter_Scene(28);
		m_pLogo->SetVisible(true);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 2.f)
	{
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
		SoundManager::GetInst()->playBGM(BGM::StillNoOpen_B);
	}
}

// ���� ũ����
void CScene_Ending::Scene_31()
{
	if (!m_IsEnter)
	{
		m_pLogo->SetVisible(false);
		Enter_Scene(27);
	}
	m_Timer += fDT;

	if (KEY_TAP(KEY::SPACE) && m_Timer >= 5.f)
	{
		DeleteObject(m_pLogo);
		m_SceneCount++;
		m_IsEnter = false;
		m_Timer = 0.f;
	}
}


void CScene_Ending::Exit()
{
	CCollisionMgr::GetInst()->Reset();
}

/*
//if (!m_IsEnter)
//{
//	for (UINT i = 0; i < 3; i++)
//	{
//		m_Scene3Arr[i] = Ending_PF_StringVec[i];
//	}

//	PORTAIT_TYPE _type[3] = { PORTAIT_TYPE::PLAYER_BASIC, PORTAIT_TYPE::PLAYER_BASIC, PORTAIT_TYPE::PLAYER_BASIC };
//	m_pTextBox->SetTXTInfo(m_Scene3Arr, 3);
//	m_pTextBox->SetPortrait(_type, 3);
//	AddObject(m_pTextBox, GROUP_TYPE::TEXT);
//
//	Enter_Scene(1);
//}

//Vec2 resolution = CCore::GetInst()->GetResolution();
//m_Timer += fDT;

//if (KEY_TAP(KEY::SPACE) && m_Timer >= 0.5f)
//{
//	static UINT talkIndex = 0;
//	bool isTalkEnd = false;

//	if (GameManager::GetInst()->GetTextEnd())
//	{
//		// AI ��ȭ
//		if (talkIndex < m_AIObjVec.size())	talkIndex++;
//		else								isTalkEnd = true;

//		for (UINT i = 0; i < talkIndex; i++)
//		{
// 				m_AIObjVec[i]->SetVisible(true);
   //			m_AIObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
   //										   resolution.y / 2 + 250 - (talkIndex - i) * m_fontSize));
   //		}
   //	}
   //	else
   //	{
   //		// �÷��̾� ���â
//			//if (m_TextBoxCount < Ending_Scene3_StringVec.size() - 1)
   //			m_TextBoxCount++;
   //	}

   //	m_Timer = 0;

   //	if (isTalkEnd == true)
   //	{
   //		GameManager::GetInst()->SetTextEnd(false);

   //		m_SceneCount++;
   //		m_IsEnter = false;
   //		m_TextBoxCount = 0;
   //		m_Timer = 0;

   //		for (auto child : m_AIObjVec)
   //		{
   //			child->SetVisible(false);
   //		}
   //	}
   //}
   */

/*
void CScene_Ending::Scene_4()
{
	if (!m_IsEnter)
	{
		for (UINT i = 0; i < 8; i++)
		{
			//m_Scene4Arr[i] = Ending_Scene4_StringVec[i];
		}

		Enter_Scene(1);

		m_pTextBox2->SetTXTInfo(m_Scene4Arr, 8);
		PORTAIT_TYPE _type2[8] = { PORTAIT_TYPE::PLAYER_BASIC, PORTAIT_TYPE::DEFAULT, PORTAIT_TYPE::HEART,
								   PORTAIT_TYPE::PLAYER_BASIC, PORTAIT_TYPE::PLAYER_BASIC, PORTAIT_TYPE::PLAYER_BASIC,
								   PORTAIT_TYPE::DEFAULT, PORTAIT_TYPE::DEFAULT };

		m_pTextBox2->SetPortrait(_type2, 8);
		AddObject(m_pTextBox2, GROUP_TYPE::INTERACTIVE);

		//m_isFloating = true;
	}

	if (m_isFloating)
	{

		AddObject(m_pFloatingTex, GROUP_TYPE::BACKGROUND);
		//m_pFloatingTex->SetPos(ScreenSize);

	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_TextBoxCount++;
		if (GameManager::GetInst()->GetTextEnd() && 8 <= m_TextBoxCount)
		{
			GameManager::GetInst()->SetTextEnd(false);
			m_SceneCount++;
			m_IsEnter = false;
			//m_isFloating = false;
			m_isFloating = true;
		}
	}
}
*/

/*
//�ֳʱ׷�
void CScene_Ending::Scene_6()
{
	if (!m_IsEnter)
	{
		Enter_Scene(1);
		m_pAnagram->GetAnimator()->Play(L"Anagram", false);
	}

	m_Timer += fDT;

	if (4.f <= m_Timer)
	{
		m_pAnagram->GetAnimator()->StopFrame(L"Anagram", 14);
	}
	else if (m_Timer <= 1.f)
	{
		m_pAnagram->GetAnimator()->StopFrame(L"Anagram", 0);
	}
	else
	{
		m_pAnagram->GetAnimator()->Play(L"Anagram", false);
	}

	if (m_Timer >= 4.0f && KEY_TAP(KEY::SPACE))
	{
		DeleteObject(m_pAnagram);

		m_SceneCount++;
		m_IsEnter = false;
	}
}
*/