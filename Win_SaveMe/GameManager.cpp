#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
	:m_interactionStatus{}
	, m_isCollected{}
	, m_sceneAcsess{}
	, m_isTextEnd()
	, frameAnswer{}
	, m_onCollision{}
	, m_isGameQuit(false)
{
	m_isMovable = true;	

	m_isSceneFirst[(UINT)SCENE_TYPE::LOBBY] = true;
	m_isSceneFirst[(UINT)SCENE_TYPE::ROOM] = true;
	m_isSceneFirst[(UINT)SCENE_TYPE::ART] = true;
	m_isSceneFirst[(UINT)SCENE_TYPE::PM] = true;

	for (int i = 0; i < (UINT)INTERACTIVE_TYPE::END; i++)
	{
		m_interactionStatus[i] = true;
	}
	m_interactionStatus[(UINT)INTERACTIVE_TYPE::PUZZLE_DOORLOCK] = false;

	m_sceneAcsess[(UINT)SCENE_TYPE::ROOM] = true;
}

void GameManager::initGame()
{
	for (int i = 0; i < (UINT)INTERACTIVE_TYPE::END; i++)
	{
		m_interactionStatus[i] = false;
	}
	for (int i = 0; i < (UINT)CLEAR_OBJECT::END; i++)
	{
		m_isCollected[i] = false;
	}
	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++) 
	{
		m_sceneAcsess[i] = false;
	}
	for (int i = 0; i < (UINT)COLLIDER_DIR::END; i++)
	{
		m_onCollision[i] = false;
	}
	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		m_isSceneFirst[i] = true;
	}
	for (int i = 0; i < 4; i++)
	{
		frameAnswer[i] = false;

	}
	for (int i = 0; i < (UINT)INTERACTIVE_TYPE::END; i++)
	{
		m_interactionStatus[i] = true;
	}

	m_interactionStatus[(UINT)INTERACTIVE_TYPE::PUZZLE_DOORLOCK] = false;

	m_sceneAcsess[(UINT)SCENE_TYPE::ROOM] = true;

	m_isTextEnd = false;
	m_isGameQuit = false;
	m_isMovable = true;

}

GameManager::~GameManager()
{
}

void GameManager::update()
{
}
