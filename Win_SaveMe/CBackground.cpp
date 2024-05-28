#include "pch.h"
#include "CBackground.h"
#include "CCollider.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "CCore.h"
CBackground::CBackground()
    : m_pTex(nullptr)
{
    // ��� �ؽ�ó �ε�
    // m_pTex = CResMgr::GetInst()->LoadTexture(L"BackgroundTex", L"texture\\Background.bmp");
}

CBackground::~CBackground()
{
    

}

void CBackground::initCenterPos()
{
    // ���÷��� ũ�� ����
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos�� ���÷��� ���� �߾����� ����
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}

void CBackground::update()
{
    Vec2 vPos = GetPos();
    SetPos(vPos);
}

void CBackground::render(HDC _dc)
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

void CBackground::SetTexture(CTexture* _tex)
{
    m_pTex = _tex;
}

