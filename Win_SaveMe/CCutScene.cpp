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
    // 텍스처 크기 정보
    int iWidth = (int)m_pTex->Width();
    int iHeight = (int)m_pTex->Height();

    Vec2 vPos = GetPos();

    // 디스플레이 중앙에 텍스처 그리기
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
    // 디스플레이 크기 정보
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}
