#include "pch.h"
#include "CCom_Anim.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CCore.h"

CCom_Anim::CCom_Anim()
	:m_pTex(nullptr)
	, m_SceneInfo(600.f, 450.f)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ComAnim", L"texture\\Com_Anim\\anagram_sprite_modify.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ComAnim", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.2f, 15);
}

CCom_Anim::~CCom_Anim()
{
}

void CCom_Anim::initCenterPos()
{
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);
}

void CCom_Anim::SetTexPos(Vec2 _TexPosInfo)
{
	m_TexPosInfo = _TexPosInfo;
}

void CCom_Anim::update()
{
	Vec2 vPos = GetPos();
	SetPos(vPos);

	// Play는 씬에서 호출, Anagram 클래스에서는 애니메이션 업데이트만 해줌
	GetAnimator()->update();
}

void CCom_Anim::render(HDC _dc)
{
	component_render(_dc);
}


