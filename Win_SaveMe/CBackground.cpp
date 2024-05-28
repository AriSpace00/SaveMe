#include "pch.h"
#include "CBackground.h"
#include "CCollider.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "CCore.h"
CBackground::CBackground()
    : m_pTex(nullptr)
{
    // 배경 텍스처 로드
    // m_pTex = CResMgr::GetInst()->LoadTexture(L"BackgroundTex", L"texture\\Background.bmp");
}

CBackground::~CBackground()
{
    

}

void CBackground::initCenterPos()
{
    // 디스플레이 크기 정보
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
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

    component_render(_dc);
}

void CBackground::SetTexture(CTexture* _tex)
{
    m_pTex = _tex;
}

