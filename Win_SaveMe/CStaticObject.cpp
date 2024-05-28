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
	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// �ش� ������Ʈ(�÷��̾�)�� Scale ��
	Vec2 vScale = GetScale();

	// �ؽ�ó ũ�⸦ Scale�� ����
	vScale.x = (int)m_pTex->Width();
	vScale.y = (int)m_pTex->Height();

	// Scale �� Set
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



