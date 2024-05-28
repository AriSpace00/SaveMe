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
	// 씬 전부 삭제
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
	// Scene 생성
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

	// 현재 씬 지정
	 m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];


	m_pCurScene->Enter();
	m_pCurScene->initCenterPos(); // 그룹들을 돌며 할당된 벡터를 체크
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();

	m_pCurScene->SceneUpdate(); // 엔딩씬 업데이트 테스트 함수
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

// GameManager 를 통해 씬이 넘어가는 조건에 따라 호출한다
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