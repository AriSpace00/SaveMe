#include "pch.h"
#include "CProfessorAnim.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CCore.h"

CProfessorAnim::CProfessorAnim()
    : m_pTex(nullptr)
    , m_SceneInfo(1920.f, 1080.f)
    , m_TexPosInfo(0.f, 0.f)
{
    // �ִϸ��̼� �ؽ�ó ����
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ProfessorAnim_1", L"texture\\opening_cutscene\\opening_animation\\01_Anim_12.bmp");

    // �ִϸ��̼� ����, �ִϸ����Ϳ� ����
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"ProfessorAnim_1", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.4f, 12);
}

CProfessorAnim::~CProfessorAnim()
{
}

void CProfessorAnim::initCenterPos()
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

	vPos.x = ScreenSize.x / 2 + m_TexPosInfo.x;
	vPos.y = ScreenSize.y / 2 + m_TexPosInfo.y;

	SetPos(vPos);
}

void CProfessorAnim::SetTexPos(Vec2 _TexPosInfo)
{
    m_TexPosInfo = _TexPosInfo;
}

void CProfessorAnim::update()
{
	Vec2 vPos = GetPos();
	SetPos(vPos);

	// Play�� ������ ȣ��, ProgrammingNPC Ŭ���������� �ִϸ��̼� ������Ʈ�� ����
	GetAnimator()->update();
}

void CProfessorAnim::render(HDC _dc)
{
	component_render(_dc);
}



