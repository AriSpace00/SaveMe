#pragma once

#include "CScene.h"

class CScene_JH_Test :
	public CScene
{

private:
	string testStringArr;
	HIMC hImc;
	string plusString;
	bool m_inputCheck;
	bool m_isNextWord;

public:
	bool IsKoreanInputEnabled();

public:
	virtual void Enter();
	virtual void Exit();

public:
	CScene_JH_Test();
	~CScene_JH_Test();
};

