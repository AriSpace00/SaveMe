#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "Camera.h"
#include "SoundManager.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "GameManager.h"

#include "CObject.h"
#include "CUI_Title.h"


CScene_Title::CScene_Title()
	:ptitle_UI{}
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::FirstEnter()
{
	// camera
	Camera::GetInst()->FadeIn(3.f);


	//background
	ptitle_UI = new CUI_Title;
	ptitle_UI->SetPos(Vec2(960.f, 540.f));
	
	AddObject(ptitle_UI, GROUP_TYPE::BACKGROUND);
}

void CScene_Title::Enter()
{
	// camera
	Camera::GetInst()->FadeIn(3.f);


	//background
	ptitle_UI = new CUI_Title;
	ptitle_UI->SetPos(Vec2(960.f, 540.f));

	AddObject(ptitle_UI, GROUP_TYPE::BACKGROUND);

	SoundManager::GetInst()->playBGM(BGM::NoOpen);
}

void CScene_Title::Exit()
{
	SoundManager::GetInst()->stopBGM();
}


void CScene_Title::SecondEnter()
{
	ptitle_UI->SetPos(Vec2(960.f, 540.f));
}
