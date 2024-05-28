#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene;					   // ÇöÀç ¾À

public:
	void init();
	void update();
	void render(HDC _dc);
	void changeScene(SCENE_TYPE _pre);

	void initScene();

public:
	CScene* GetCurScene() { return m_pCurScene; }
};