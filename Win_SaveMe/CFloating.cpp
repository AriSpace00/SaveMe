#include "pch.h"
#include "CFloating.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCore.h"

CFloating::CFloating()
    : m_pTex(nullptr)
{
}

CFloating::~CFloating()
{
}
void CFloating::initCenterPos()
{
    // ���÷��� ũ�� ����
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos�� ���÷��� ���� �߾����� ����
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}

void CFloating::update()
{
    Vec2 vPos = GetPos();
    SetPos(vPos);
}

void CFloating::render(HDC _dc)
{
    // �ؽ�ó ũ�� ����
    int iWidth = (int)m_pTex->Width();
    int iHeight = (int)m_pTex->Height();

    Vec2 vPos = GetPos();

    // ���÷��� �߾ӿ� �ؽ�ó �׸���
    BitBlt(_dc,
        (int)vPos.x - iWidth / 2,
        (int)vPos.y - iHeight / 2,
        iWidth, iHeight,
        m_pTex->GetDC(),
        0, 0,
        SRCCOPY);

    component_render(_dc);
}

void CFloating::SetTexture(CTexture* _tex)
{
    m_pTex = _tex;
}

