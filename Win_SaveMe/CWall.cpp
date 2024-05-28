#include "pch.h"
#include "CWall.h"

#include "CCollider.h"
#include "CCore.h"
#include "GameManager.h"


CWall::CWall()
	: m_dir()
{
	CreateCollider();
}

CWall::~CWall()
{
}


void CWall::SetScale(Vec2 _scale)
{
	GetCollider()->SetScale(_scale);
}
void CWall::initCenterPos()
{
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CWall::update()
{
}

void CWall::render(HDC _dc)
{
	component_render(_dc);
}

void CWall::OnCollisionEnter(CCollider* _pOther)
{
}

void CWall::OnCollision(CCollider* _pOther)
{
	switch (m_dir)
	{
		case COLLIDER_DIR::LEFT:
		{
			GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::LEFT, true);
			break;
		}
		case COLLIDER_DIR::RIGHT:
		{
			GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::RIGHT, true);
			break;
		}
		case COLLIDER_DIR::TOP:
		{
			GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::TOP, true);
			break;
		}
		case COLLIDER_DIR::BOTTOM:
		{
			GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::BOTTOM, true);
			break;
		}
	}
}

void CWall::OnCollisionExit(CCollider* _pOther)
{
	GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::LEFT, false);
	GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::RIGHT, false);
	GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::TOP, false);
	GameManager::GetInst()->SetOnCollision(COLLIDER_DIR::BOTTOM, false);
}
