#include "pch.h"
#include "CCutScene.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

CCutScene::CCutScene()
{
}

CCutScene::~CCutScene()
{
}

void CCutScene::update()
{
}

void CCutScene::render(HDC _dc)
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
}

void CCutScene::SetTexture(CTexture* _tex)
{
    m_pTex = _tex;

}

void CCutScene::initCenterPos()
{
    // ���÷��� ũ�� ����
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos�� ���÷��� ���� �߾����� ����
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}
