#include "pch.h"
#include "CPortrait.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "GameManager.h"


CPortrait::CPortrait()
{
	m_pTexs[(int)PORTAIT_TYPE::DEFAULT] = nullptr;

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_BASIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// �÷��̾� �⺻

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // �÷��̾� �д�
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// �÷��̾� �ɰ�
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// �÷��̾� ���
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// �÷��̾� ������
	
	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // ��ȹ ����
	
	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // ��Ʈ ����
	
	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // �ù� ����
	
	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst() ->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // ������ ����
	

	m_totalShowPortrait = 0;
	m_curShowPortrait = 0;
}

CPortrait::~CPortrait()
{
}

void CPortrait::initCenterPos()
{
	
}

void CPortrait::update()
{



}

void CPortrait::render(HDC _dc)
{
	//DEFAULT �� ��� �ƹ��͵� �������� �ʴ´�
	if (nullptr == m_pTexs[arrPortait[m_curShowPortrait]])
	{
		return;
	}
	// ��� �ʻ�ȭ�� ����� ��� ������Ʈ ����
	if (m_curShowPortrait >= m_totalShowPortrait)
	{
		//GameManager::GetInst()->SetMovable(true);
		DeleteObject(this);
		return;
	}

	// ���÷��� ũ�� ����
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos�� ���÷��� ���� �߾����� ����
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);

	int iWidth = (int)m_pTexs[arrPortait[m_curShowPortrait]]->Width();
	int iHeight = (int)m_pTexs[arrPortait[m_curShowPortrait]]->Height();

	TransparentBlt(_dc,
		(int)vPos.x - iWidth / 2,
		(int)vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTexs[arrPortait[m_curShowPortrait]]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));

	
	if (KEY_TAP(KEY::SPACE))
	{
		// ��� �ʻ�ȭ�� ����ϸ� ������Ʈ�� �����Ѵ�

		//TextManager::GetInst()->clearText();
		// ����� �۾�. �ʿ��Ѱ�



		m_curShowPortrait++;
	}
	
}
