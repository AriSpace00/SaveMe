#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CCollider.h"

#include "CMissile.h"
#include "Camera.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"

#include "SoundManager.h"
#include "TextManager.h"
#include "GameManager.h"






CPlayer::CPlayer()
	: m_pTex(nullptr)
	, m_PlayerInfo(81.f, 153.f)
	, player_Speed()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 50.f));
	GetCollider()->SetScale(Vec2(55.f, 55.f));

	// Texture �ε��ϱ�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player\\SD_sprite.bmp");
	m_floatingTex = CResMgr::GetInst()->LoadTexture(L"PlayerFloatingTex", L"texture\\ui\\player_floating_UI(2).bmp");

	// �ִϸ����� �����
	CreateAnimator();

	// �ִϸ����Ϳ� �ִϸ��̼� �����
	GetAnimator()->CreateAnimation(L"PLAYER_IDLE", m_pTex, Vec2(0.f, 0.f), Vec2(m_PlayerInfo.x, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"WALK_FRONT", m_pTex, Vec2(0.f, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", m_pTex, Vec2(0.f, m_PlayerInfo.y * 2), Vec2(m_PlayerInfo.x, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", m_pTex, Vec2(0.f, m_PlayerInfo.y * 3), Vec2(m_PlayerInfo.x, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_BACK", m_pTex, Vec2(0.f, m_PlayerInfo.y * 4), Vec2(m_PlayerInfo.x, m_PlayerInfo.y), Vec2(m_PlayerInfo.x, 0.f), 0.2f, 4);

	// IDLE ���� ���
	GetAnimator()->Play(L"PLAYER_IDLE", true);

	floatingStartTime = 2.f;
	floatingEndTime = 3.f;


	/// �÷��̾� ���ǵ� ���� �����Կ�
	player_Speed = 300.f;
	
}

CPlayer::~CPlayer()
{

}

void CPlayer::initCenterPos()
{
	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// �ؽ�ó ũ�� ����
	float iWidth = (int)m_pTex->Width();
	float iHeight = (int)m_pTex->Height();

	// �ش� ������Ʈ(�÷��̾�)�� Scale ��
	Vec2 vScale = GetScale();

	// �ؽ�ó ũ�⸦ Scale�� ����
	vScale.x = iWidth;
	vScale.y = iHeight;

	// Scale �� Set
	SetScale(vScale);

	Vec2 vPos = GetPos();

	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;

	SetPos(vPos);
}

void CPlayer::update()
{
	if (!GameManager::GetInst()->GetMovable()) return;

	Vec2 vPos = GetPos();

	if (KEY_NONE(KEY::A))
	{
		GetAnimator()->StopFrame(L"WALK_LEFT", 0);
	}
	if (KEY_NONE(KEY::D))
	{
		GetAnimator()->StopFrame(L"WALK_RIGHT", 0);
	}
	if (KEY_NONE(KEY::W))
	{
		GetAnimator()->StopFrame(L"WALK_BACK", 0);
	}
	if (KEY_NONE(KEY::S))
	{
		GetAnimator()->StopFrame(L"WALK_FRONT", 0);

		// �̰� �ּ� �ϸ� ������ ���߱� �ϴµ� �տ����� ���̵� ���ϴ� �����߻�
		GetAnimator()->Play(L"PLAYER_IDLE", true);
		GetAnimator()->update();
	}
	if(KEY_HOLD(KEY::W))
	{
		if (!GameManager::GetInst()->GetOnCollision(COLLIDER_DIR::TOP))
		{
			vPos.y -= player_Speed * fDT;

		}
		GetAnimator()->Play(L"WALK_BACK", true);
		GetAnimator()->update();
	}
	else if (KEY_HOLD(KEY::S))
	{
		if (!GameManager::GetInst()->GetOnCollision(COLLIDER_DIR::BOTTOM))
		{
			vPos.y += player_Speed * fDT;

		}
		GetAnimator()->Play(L"WALK_FRONT", true);
		GetAnimator()->update();
	}
	else if (KEY_HOLD(KEY::A))
	{
		if (!GameManager::GetInst()->GetOnCollision(COLLIDER_DIR::LEFT))
		{
			vPos.x -= player_Speed * fDT;
		}
		GetAnimator()->Play(L"WALK_LEFT", true);
		GetAnimator()->update();
	}
	else if (KEY_HOLD(KEY::D))
	{
		if (!GameManager::GetInst()->GetOnCollision(COLLIDER_DIR::RIGHT))
		{
			vPos.x += player_Speed * fDT;

		}
		GetAnimator()->Play(L"WALK_RIGHT", true);
		GetAnimator()->update();
	}

	GetAnimator()->update();
	

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{

	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// �ؽ�ó ũ�� ����
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	int iWidth = 81;
	int iHeight = 153;

	// �÷��̾� ��ġ
	// Vec2 vRenderpos = Camera::GetInst()->GetRenderPos(pos);
	// ī�޶� �����,, ��ü ��ǥ�� ���� GetRenderPos �Լ��� ��ȯ���Ѽ� �������ϼž� ����
	Vec2 vPos = GetPos();
	
	// �÷��̾� �׸���
	/*TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		81, 153,
		m_pTex->GetDC(),
		0, 0,
		81, 153,
		RGB(106, 255, 0));*/

	// �÷��̾ ó�� ���� ����� ��� floating UI 
	static double elapsedTime = 0.0f;

	elapsedTime += DT;

	if (elapsedTime <= floatingEndTime 
		&& floatingStartTime <= elapsedTime)
	{
		if (!m_playSound && GameManager::GetInst()->GetCurScene() != SCENE_TYPE::ROOM)
		{
			SoundManager::GetInst()->playSFX(SFX::exclamation_mark);
			m_playSound = true;
		}


		/*BitBlt(_dc,
			(int)vPos.x-10,
			(int)vPos.y - 120,
			iWidth, iHeight,
			m_floatingTex->GetDC(),
			0, 0,
			SRCCOPY);*/

		TransparentBlt(_dc,
			(int)vPos.x - m_floatingTex->Width()/2,
			(int)vPos.y - 120,
			m_floatingTex->Width(), m_floatingTex->Height(),
			m_floatingTex->GetDC(),
			0, 0,
			m_floatingTex->Width(), m_floatingTex->Height(),
			RGB(106, 255, 0));
	}


	// ������Ʈ (�浹ü, etc...) �� �ִ� ��� ����
	Vec2 m_vPos = GetPos();
	Vec2 m_vScale = GetScale();

	component_render(_dc);
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
}

void CPlayer::OnCollision(CCollider* _pOther)
{
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
}
