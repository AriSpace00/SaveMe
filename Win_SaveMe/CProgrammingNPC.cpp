#include "pch.h"
#include "CProgrammingNPC.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "CCore.h"

CProgrammingNPC::CProgrammingNPC()
    : m_pTex(nullptr)
    , m_SceneInfo(184.f, 248.f)
	, m_TexPosInfo(0.f, 0.f)
{
	// �ִϸ��̼� �ؽ�ó ����
	m_pTex = CResMgr::GetInst()->LoadTexture(L"ProgrammingNPC", L"texture\\MAP\\programming_class\\program_speit.bmp");

	// �ִϸ��̼� ����, �ִϸ����Ϳ� ����
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ProgrammingNPC", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.8f, 6);
}

CProgrammingNPC::~CProgrammingNPC()
{
}

void CProgrammingNPC::initCenterPos()
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

void CProgrammingNPC::SetTexPos(Vec2 _TexPosInfo)
{
	m_TexPosInfo = _TexPosInfo;
}

void CProgrammingNPC::update()
{
	Vec2 vPos = GetPos();
	SetPos(vPos);

	// Play�� ������ ȣ��, ProgrammingNPC Ŭ���������� �ִϸ��̼� ������Ʈ�� ����
	GetAnimator()->update();
}

void CProgrammingNPC::render(HDC _dc)
{
	component_render(_dc);
}
