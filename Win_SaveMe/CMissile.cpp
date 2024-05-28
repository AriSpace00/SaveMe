#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fDir(1.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f,15.f));
}

CMissile::~CMissile()
{

}

void CMissile::initCenterPos()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	vPos.y += 200.f * fDT * (float)m_fDir;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x /2.f), int(vPos.y - vScale.y / 2.f)
	,  (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
