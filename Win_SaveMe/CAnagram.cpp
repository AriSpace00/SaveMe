#include "pch.h"
#include "CAnagram.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CCore.h"

CAnagram::CAnagram()
    : m_pTex(nullptr)
    , m_SceneInfo(600.f, 450.f)
{
    // 애니메이션 텍스처 지정
    m_pTex = CResMgr::GetInst()->LoadTexture(L"Anagram", L"texture\\anagram\\anagram_sprite_modify.bmp");

    // 애니메이션 제작, 애니메이터에 연결
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Anagram", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.2f, 15);
}

CAnagram::~CAnagram()
{
}

void CAnagram::initCenterPos()
{
    // 디스플레이 크기 정보
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}

void CAnagram::update()
{
    Vec2 vPos = GetPos();
    SetPos(vPos);

    // Play는 씬에서 호출, Anagram 클래스에서는 애니메이션 업데이트만 해줌
	GetAnimator()->update();
}

void CAnagram::render(HDC _dc)
{
	component_render(_dc);
}
