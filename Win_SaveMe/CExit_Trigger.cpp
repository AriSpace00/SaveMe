#include "pch.h"
#include "CExit_Trigger.h"
#include "CCore.h"
#include "CCollider.h"
#include "GameManager.h"
#include "Camera.h"
#include "CTimeMgr.h"
#include "CTextBox.h"
#include "CKeyMgr.h"
#include "SoundManager.h"



CExit_Trigger::CExit_Trigger()
	:m_isCreated(),m_nextSceneType()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f, 200.f));
	delay = 0.f;

}

CExit_Trigger::~CExit_Trigger()
{
}

void CExit_Trigger::SetScale(Vec2 _scale)
{
	GetCollider()->SetScale(_scale);
}

void CExit_Trigger::initCenterPos()
{
	// 

	// 
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CExit_Trigger::update()
{
	
	
}

void CExit_Trigger::render(HDC _dc)
{
	component_render(_dc);
}

void CExit_Trigger::OnCollisionEnter(CCollider* _pOther)
{
	m_isCreated = false;
}

void CExit_Trigger::OnCollision(CCollider* _pOther)
{
	if (GameManager::GetInst()->GetSceneAcsess(m_nextSceneType))
	{
		if (!m_fadeOut)
		{
			GameManager::GetInst()->SetMovable(false);
			Camera::GetInst()->FadeOut(2.5f);
			m_fadeOut = true;
			SoundManager::GetInst()->playSFX(SFX::fade_out);

		}

		delay += DT;
		if (delay >= 2.5f)
		{
			GameManager::GetInst()->SetScene(m_nextSceneType);
			delay = 0;
			m_fadeOut = false;
		}
	}
	else if(!m_isCreated)
	{
		m_isCreated = true;
		CTextBox* pTextBox = new CTextBox;
		PORTAIT_TYPE _type[1];// = { PORTAIT_TYPE::PLAYER_BASIC };
		LPCWSTR txt[1];
		switch (m_nextSceneType)
		{
			case SCENE_TYPE::LOBBY:
			{
				if (GameManager::GetInst()->GetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK))
				{
					_type[0]= { PORTAIT_TYPE::PLAYER_SURPRISE };
					txt[0] = L"문이 잠겨있어.";
				}
				else
				{
					_type[0] = { PORTAIT_TYPE::PLAYER_THINKING };
					txt[0] = L"우선 방을 둘러보자.";
				}
				
				break;
			}
				
			case SCENE_TYPE::ART:
			{
				if (GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::DS))
				{
					_type[0] = { PORTAIT_TYPE::PLAYER_BASIC };

					txt[0] = L"우선 이걸 컴퓨터에 넣어야 해.";
				}
				else
				{
					_type[0] = { PORTAIT_TYPE::PLAYER_SURPRISE };
					txt[0] = L"문이 잠겨있어.";
				}
				break;
			}
			case SCENE_TYPE::PM:
			{
				if (GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::ART) || GameManager::GetInst()->GetIsCollected(CLEAR_OBJECT::DS))
				{
					_type[0] = { PORTAIT_TYPE::PLAYER_BASIC };

					txt[0] = L"우선 이걸 컴퓨터에 넣어야 해.";
				}
				else
				{
					_type[0] = { PORTAIT_TYPE::PLAYER_SURPRISE };
					txt[0] = L"문이 잠겨있어.";
				}
				break;
			}
				
		}

		UINT textCount = 1;
		
		pTextBox->SetPortrait(_type, 1);
		pTextBox->SetTXTInfo(txt, textCount);
		CreateObject(pTextBox, GROUP_TYPE::TEXT);
	}
}
