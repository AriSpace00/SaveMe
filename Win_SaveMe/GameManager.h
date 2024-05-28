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


	// �� ���� ��ȣ�ۿ� ������ ������Ʈ�� ���� ��ȣ�ۿ� ���� ��ȯ
	bool GetInteractionStatus(INTERACTIVE_TYPE _type)
	{
		return m_interactionStatus[(UINT)_type];
	}
	// �� ���� ��ȣ�ۿ� ������ ������Ʈ�� ���� ��ȣ�ۿ� ���� ���� ��
	void SetInteractionStatus(INTERACTIVE_TYPE _type, bool _status)
	{
		m_interactionStatus[(UINT)_type] = _status;
	}

	// ���� ������Ʈ ȹ�� ���� ��ȯ �Լ�(���� �� ����)
	bool GetIsCollected(CLEAR_OBJECT _obj)
	{
		return m_isCollected[(UINT)_obj];
	}

	// ���� ȹ�� ���� ��
	void SetIsCollected(CLEAR_OBJECT _obj, bool _isCollected)
	{
		m_isCollected[(UINT)_obj] = _isCollected;
	}

	void initGame();

	void update();

	bool GetMovable() { return m_isMovable; }

	// ��ȣ�ۿ� ���϶�, ��ȣ�ۿ� ��������
	void SetMovable(bool _isMovable) 
	{
		m_isMovable = _isMovable;
	}

	// ������ 
	void SetScene(SCENE_TYPE _nextScene) 
	{ 
		CSceneMgr::GetInst()->changeScene(_nextScene);
		m_onCollision[(UINT)COLLIDER_DIR::TOP] = false;
		m_onCollision[(UINT)COLLIDER_DIR::BOTTOM] = false;
		m_onCollision[(UINT)COLLIDER_DIR::RIGHT] = false;
		m_onCollision[(UINT)COLLIDER_DIR::LEFT] = false;
	}
	
	// ������
	bool GetSceneAcsess(SCENE_TYPE _scene)
	{
		return m_sceneAcsess[(UINT)_scene];
	}
	// ��ǻ�Ϳ� ������ ȣ���ؾ���
	void SetSceneAcsess(SCENE_TYPE _scene, bool _b)
	{
		m_sceneAcsess[(UINT)_scene] = _b;
	}

	// �������� ���⶧ �����̽����� �ٲ��־����
	void SetFrameAnswer(int _frameNum, bool _b)
	{
		frameAnswer[_frameNum] = _b;
	}
	// �������� ���⶧���� �� Ȯ���ؾ���
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

	bool m_isCollected[(UINT)CLEAR_OBJECT::END];		// ���� ������Ʈ ȹ�� ����
	//SCENE_TYPE sceneType;
	

	bool m_isSceneFirst[(UINT)SCENE_TYPE::END];

	bool m_isTextEnd;

	bool m_isGameQuit;

	// �� ���� ����
	// Pause ��� Ȱ��ȭ �Լ�
	// ���â Ȱ��ȭ + 1��Ī ���� ��ȭ �� �÷��̾� �̵�Ű ����

};

