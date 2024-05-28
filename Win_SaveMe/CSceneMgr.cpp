#include "pch.h"
#include "struct.h"

#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Ending.h"
#include "CScene_Lobby.h"
#include "CScene_Room.h"
#include "CScene_ART.h"
#include "CScene_PM.h"
#include "CScene_MoniterAI.h"
#include "CScene_Title.h"

#include "Camera.h"

#include "CUI_Title.h"
#include "CScene_Title.h"
#include "CScene_Opening.h"



CSceneMgr::CSceneMgr()
	:m_arrScene{}
	, m_pCurScene(nullptr)
{

}
CSceneMgr::~CSceneMgr()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	 m_arrScene[(UINT)SCENE_TYPE::ROOM] = new CScene_Room;
	 m_arrScene[(UINT)SCENE_TYPE::LOBBY] = new CScene_Lobby;
	 m_arrScene[(UINT)SCENE_TYPE::ART] = new CScene_ART;
	 m_arrScene[(UINT)SCENE_TYPE::PM] = new CScene_PM;
	 m_arrScene[(UINT)SCENE_TYPE::ENDING] = new CScene_Ending;
	 m_arrScene[(UINT)SCENE_TYPE::MONITER_AI] = new CScene_MoniterAI;
	 m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	 m_arrScene[(UINT)SCENE_TYPE::OPENING] = new CScene_Opening;

	// ���� �� ����
	 m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];


	m_pCurScene->Enter();
	m_pCurScene->initCenterPos(); // �׷���� ���� �Ҵ�� ���͸� üũ
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();

	m_pCurScene->SceneUpdate(); // ������ ������Ʈ �׽�Ʈ �Լ�
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

// GameManager �� ���� ���� �Ѿ�� ���ǿ� ���� ȣ���Ѵ�
void CSceneMgr::changeScene(SCENE_TYPE _next)
{
 	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_next];
	m_pCurScene->Enter();
	m_pCurScene->initCenterPos();
}

// regame ... fail
void CSceneMgr::initScene()
{
	delete  m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	delete  m_arrScene[(UINT)SCENE_TYPE::ROOM];
	delete  m_arrScene[(UINT)SCENE_TYPE::ART];
	delete  m_arrScene[(UINT)SCENE_TYPE::PM];
	delete  m_arrScene[(UINT)SCENE_TYPE::LOBBY];
	m_arrScene[(UINT)SCENE_TYPE::ROOM] = new CScene_Room;
	m_arrScene[(UINT)SCENE_TYPE::LOBBY] = new CScene_Lobby;
	m_arrScene[(UINT)SCENE_TYPE::ART] = new CScene_ART;
	m_arrScene[(UINT)SCENE_TYPE::PM] = new CScene_PM;


	delete  m_arrScene[(UINT)SCENE_TYPE::MONITER_AI];
	delete  m_arrScene[(UINT)SCENE_TYPE::OPENING];
	delete  m_arrScene[(UINT)SCENE_TYPE::ENDING];
	m_arrScene[(UINT)SCENE_TYPE::ENDING] = new CScene_Ending;
	//m_arrScene[(UINT)SCENE_TYPE::MONITER_AI]->SceneReset();
	m_arrScene[(UINT)SCENE_TYPE::MONITER_AI] = new CScene_MoniterAI;
	m_arrScene[(UINT)SCENE_TYPE::OPENING] = new CScene_Opening;

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_pCurScene->Enter();
	m_pCurScene->initCenterPos();

}