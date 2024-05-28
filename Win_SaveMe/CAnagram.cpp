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
    // �ִϸ��̼� �ؽ�ó ����
    m_pTex = CResMgr::GetInst()->LoadTexture(L"Anagram", L"texture\\anagram\\anagram_sprite_modify.bmp");

    // �ִϸ��̼� ����, �ִϸ����Ϳ� ����
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Anagram", m_pTex, Vec2(0.f, 0.f), Vec2(m_SceneInfo.x, m_SceneInfo.y), Vec2(m_SceneInfo.x, 0.f), 0.2f, 15);
}

CAnagram::~CAnagram()
{
}

void CAnagram::initCenterPos()
{
    // ���÷��� ũ�� ����
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos�� ���÷��� ���� �߾����� ����
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);
}

void CAnagram::update()
{
    Vec2 vPos = GetPos();
    SetPos(vPos);

    // Play�� ������ ȣ��, Anagram Ŭ���������� �ִϸ��̼� ������Ʈ�� ����
	GetAnimator()->update();
}

void CAnagram::render(HDC _dc)
{
	component_render(_dc);
}
