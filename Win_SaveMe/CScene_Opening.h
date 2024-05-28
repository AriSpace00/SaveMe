#pragma once
#include "CScene.h"

class CBackground;
class CObject;
class CAnagram;
class CTextBox;

class CStaticObject;

class CProfessorAnim;
class CProfessorAnim_1;

class CScene_Opening :
    public CScene
{
private:

	float m_skipTime;
	float m_Time;

	// Background
	CBackground* m_pBackground;

	const wchar_t* op_SceneArr[11] = {};
	const wchar_t* op_TextureArr[11] = {};

	UINT m_SceneCount; // 씬 카운트
	Vec2 m_SceneInfo; // 씬 크기 정보

	// Anagram
	CAnagram* m_pAnagram;

	// TextBox
	CTextBox* m_pTextBox;
	CTextBox* m_pTextBox2;

	LPCWSTR m_Scene3Arr[10] = {};

	vector<LPCWSTR> Ending_Scene3_StringVec = {};

	bool m_CreateTextBox; // 텍스트 박스 생성 조건
	int m_TextBoxCount; // 텍스트 박스 카운트

	bool m_IsEnter;
	float m_Timer;

	bool m_IsExitScene;

	CStaticObject* m_pLogo;
	//ProfessorAnim
	CProfessorAnim* m_pProfessorAnim_0;
	CProfessorAnim_1* m_pProfessorAnim_1;

public:
	CScene_Opening();
	~CScene_Opening();

public:
	virtual void Enter();
	virtual void Exit();
	virtual void SceneUpdate();

public:
	void Scene_0();
	void Scene_1();
	void Scene_2();
	void Scene_3();
	void Scene_4();
	void Scene_5();
	void Scene_6();
	void Scene_7();
	void Scene_8();
	void Scene_9();
	void Scene_10();
	void Next_Scene();

public:
	void Enter_Scene();

};

