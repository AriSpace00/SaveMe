#include "pch.h"
#include "CProfessorAnim_1.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CCore.h"

CProfessorAnim_1::CProfessorAnim_1()
	: m_pTex(nullptr)
	, m_SceneInfo(1920.f, 1080.f)
	, m_TexPosInfo(0.f, 0.f)
{
	// 애니메이션 텍스처 지정
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ProfessorAnim_2", L"texture\\opening_cutscene\\opening_animation\\02_Anim_11.bmp");

	// 애니메이션 제작, 애니메이터에 연결
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ProfessorAnim_2", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.4f, 11);
}

CProfessorAnim_1::~CProfessorAnim_1()
{
}

void CProfessorAnim_1::initCenterPos()
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

	vPos.x = ScreenSize.x / 2 + m_TexPosInfo.x;
	vPos.y = ScreenSize.y / 2 + m_TexPosInfo.y;

	SetPos(vPos);
}

void CProfessorAnim_1::SetTexPos(Vec2 _TexPosInfo)
{
	m_TexPosInfo = _TexPosInfo;
}

void CProfessorAnim_1::update()
{
	Vec2 vPos = GetPos();
	SetPos(vPos);

	// Play는 씬에서 호출, ProgrammingNPC 클래스에서는 애니메이션 업데이트만 해줌
	GetAnimator()->update();
}

void CProfessorAnim_1::render(HDC _dc)
{
	component_render(_dc);
}