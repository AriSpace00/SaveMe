#pragma once

#include "CSceneMgr.h"


class GameManager
{
	SINGLE(GameManager)

public:
	void skipScene() {	}

	void SetDebugMode()
	{
		m_debugMode = !m_debugMode;
	}

	bool GetDebugMode()
	{
		return m_debugMode;
	}
	void SetPreScene(SCENE_TYPE _scene) { m_preScene = _scene; }
	SCENE_TYPE GetPreScene() { return m_preScene; }

	void SetCurScene(SCENE_TYPE _scene) { m_curScene = _scene; }
	SCENE_TYPE GetCurScene() { return m_curScene; }


	// 한 번만 상호작용 가능한 오브젝트에 대한 상호작용 여부 반환
	bool GetInteractionStatus(INTERACTIVE_TYPE _type)
	{
		return m_interactionStatus[(UINT)_type];
	}
	// 한 번만 상호작용 가능한 오브젝트에 대한 상호작용 상태 여부 셋
	void SetInteractionStatus(INTERACTIVE_TYPE _type, bool _status)
	{
		m_interactionStatus[(UINT)_type] = _status;
	}

	// 정수 오브젝트 획득 정보 반환 함수(퍼즐 및 심장)
	bool GetIsCollected(CLEAR_OBJECT _obj)
	{
		return m_isCollected[(UINT)_obj];
	}

	// 정수 획득 정보 셋
	void SetIsCollected(CLEAR_OBJECT _obj, bool _isCollected)
	{
		m_isCollected[(UINT)_obj] = _isCollected;
	}

	void initGame();

	void update();

	bool GetMovable() { return m_isMovable; }

	// 상호작용 중일때, 상호작용 끝났을때
	void SetMovable(bool _isMovable) 
	{
		m_isMovable = _isMovable;
	}

	// 문에서 
	void SetScene(SCENE_TYPE _nextScene) 
	{ 
		CSceneMgr::GetInst()->changeScene(_nextScene);
		m_onCollision[(UINT)COLLIDER_DIR::TOP] = false;
		m_onCollision[(UINT)COLLIDER_DIR::BOTTOM] = false;
		m_onCollision[(UINT)COLLIDER_DIR::RIGHT] = false;
		m_onCollision[(UINT)COLLIDER_DIR::LEFT] = false;
	}
	
	// 문에서
	bool GetSceneAcsess(SCENE_TYPE _scene)
	{
		return m_sceneAcsess[(UINT)_scene];
	}
	// 컴퓨터에 넣을때 호출해야함
	void SetSceneAcsess(SCENE_TYPE _scene, bool _b)
	{
		m_sceneAcsess[(UINT)_scene] = _b;
	}

	// 액자퍼즐 맞출때 스페이스마다 바꿔주어야함
	void SetFrameAnswer(int _frameNum, bool _b)
	{
		frameAnswer[_frameNum] = _b;
	}
	// 액자퍼즐 맞출때마다 답 확인해야함
	bool GetFrameAnswer()
	{
		for (int i = 0; i < 4; i++)
		{
			if (!frameAnswer[i]) return false;
		}
		return true;
	}

	bool GetSceneFirst(SCENE_TYPE _type) 
	{
		return m_isSceneFirst[(UINT)_type];
	}
	void SetSceneFirst(SCENE_TYPE _type, bool _b) 
	{
		m_isSceneFirst[(UINT)_type] = _b;
	}

	void SetTextEnd(bool _isEnd)
	{
		m_isTextEnd = _isEnd;
	}

	bool GetTextEnd()
	{
		return m_isTextEnd;
	}
	void SetOnCollision(COLLIDER_DIR _dir, bool _isCrash)
	{
		m_onCollision[(UINT)_dir] = _isCrash;
	}

	bool GetOnCollision(COLLIDER_DIR _dir)
	{
		return m_onCollision[(UINT)_dir];
	}

	void SetGameQuit() { m_isGameQuit = true; }
	bool GetIsGameQuit() { return m_isGameQuit; }


private:

	bool m_debugMode;

	SCENE_TYPE m_preScene;

	SCENE_TYPE m_curScene;

	bool m_onCollision[(UINT)COLLIDER_DIR::END];

	bool m_isMovable;

	bool frameAnswer[4];

	bool m_sceneAcsess[(UINT)SCENE_TYPE::END];

	bool m_interactionStatus[(UINT)INTERACTIVE_TYPE::END];

	bool m_isCollected[(UINT)CLEAR_OBJECT::END];		// 정수 오브젝트 획득 정보
	//SCENE_TYPE sceneType;
	

	bool m_isSceneFirst[(UINT)SCENE_TYPE::END];

	bool m_isTextEnd;

	bool m_isGameQuit;

	// 씬 접근 정보
	// Pause 기능 활성화 함수
	// 대사창 활성화 + 1인칭 시점 변화 시 플레이어 이동키 제어

};

