#include "pch.h"
#include "CMonster.h"

#include"CTimeMgr.h"
#include "CCollider.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(-1)
	, m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	m_pTex = CResMgr::GetInst()->LoadTexture(L"InterectiveTex", L"texture\\penguin.bmp");
}

CMonster::~CMonster()
{
}

void CMonster::OnCollision(CCollider* _pOther)
{

}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;
		if (m_iHP <= 0)
			DeleteObject(this);
	}
}

void CMonster::initCenterPos()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회거리 기준량을 넘어섰는지 확인 
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// 방향 변경
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}


