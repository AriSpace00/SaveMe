#include "pch.h"
#include "CStaticObject.h"

#include "CCore.h"
#include "CTexture.h"



CStaticObject::CStaticObject()
    : m_pTex(nullptr)
    , m_TexPosInfo(0.f, 0.f)
{
}

CStaticObject::~CStaticObject()
{
}

void CStaticObject::initCenterPos()
{
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// 해당 오브젝트(플레이어)의 Scale 값
	Vec2 vScale = GetScale();

	// 텍스처 크기를 Scale에 대입
	vScale.x = (int)m_pTex->Width();
	vScale.y = (int)m_pTex->Height();

	// Scale 값 Set
	SetScale(vScale);

	Vec2 vPos = GetPos();

	vPos.x = (ScreenSize.x - 1920) / 2 + m_TexPosInfo.x;
	vPos.y = (ScreenSize.y - 1080) / 2 + m_TexPosInfo.y;

	SetPos(vPos);
}


void CStaticObject::SetTexPos(Vec2 _TexPosInfo)
{
	m_TexPosInfo = _TexPosInfo;

}

void CStaticObject::SetTexture(CTexture* _tex)
{
	m_pTex = _tex;
}

void CStaticObject::update()
{
	Vec2 vPos = GetPos();
	SetPos(vPos);
}

void CStaticObject::render(HDC _dc)
{
	if (m_isVisible == false) return;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	TransparentBlt(_dc, vPos.x, vPos.y, vScale.x, vScale.y, m_pTex->GetDC(), 0, 0, vScale.x, vScale.y, RGB(106, 255, 0));
}



