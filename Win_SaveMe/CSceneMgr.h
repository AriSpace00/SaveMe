#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene* m_pCurScene;					   // ���� ��

public:
	void init();
	void update();
	void render(HDC _dc);
	void changeScene(SCENE_TYPE _pre);

	void initScene();

public:
	CScene* GetCurScene() { return m_pCurScene; }
};