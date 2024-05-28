#pragma once
#include "CScene.h"

class CBackground;
class CObject;
class CAnagram;
class CTextBox;
class CFloating;
class AI_TextObj;

class CProfessorAnim;
class CProfessorAnim_1;

class CStaticObject;

class CScene_Ending :
	public CScene
{

	//Vec2 resolution = CCore::GetInst()->GetResolution();

private:
	// Background
	CBackground* m_pBackground;

	const wchar_t* SceneArr[29] = {};
	const wchar_t* TextureArr[29] = {};

	UINT m_SceneCount; // 씬 카운트
	Vec2 m_SceneInfo; // 씬 크기 정보

	// Anagram
	CAnagram* m_pAnagram;

	// TextBox
	CTextBox* m_pTextBox;
	CTextBox* m_pTextBox2;
	CTextBox* m_pTextBox3;
	CTextBox* m_pTextBox4;
	CTextBox* m_pTextBox5;
	CTextBox* m_pTextBox6;
	CTextBox* m_pTextBox7;

	LPCWSTR m_Scene3Arr[10] = {};
	LPCWSTR m_Scene4Arr[10] = {};
	LPCWSTR m_Scene5Arr[10] = {};
	LPCWSTR m_Scene8Arr[10] = {};

	vector<LPCWSTR> Ending_PF_StringVec = {};
	vector<LPCWSTR> Ending_Hater_StringVec = {};
	vector<LPCWSTR> Ending_System_StringVec = {};

	vector<AI_TextObj*> m_AIObjVec;

	UINT m_talkIndex;
	UINT m_fontSize;
	UINT m_lastTalkIndex;

	bool m_CreateTextBox; // 텍스트 박스 생성 조건
	int m_TextBoxCount; // 텍스트 박스 카운트

	bool m_IsEnter;
	float m_Timer;

	CFloating* m_pFloatingTex; // 플로팅 텍스처
	bool m_isFloating; // 플로팅 텍스처 출력 조건

	CProfessorAnim* m_pProfessorAnim1;
	CProfessorAnim_1* m_pProfessorAnim_0000;

	float FirstTime;
	float SecondTime;

	CStaticObject* m_pLogo;

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
	void Scene_11();
	void Scene_12();
	void Scene_13();
	void Scene_14();
	void Scene_15();
	void Scene_16();
	void Scene_17();
	void Scene_18();
	void Scene_19();
	void Scene_20();
	void Scene_21();
	void Scene_22();
	void Scene_23();
	void Scene_24();
	void Scene_25();
	void Scene_26();
	void Scene_27();
	void Scene_28();
	void Scene_29();
	void Scene_30();
	void Scene_31();

public:
	void Enter_Scene(UINT _index);

public:
	CScene_Ending();
	~CScene_Ending();
};

