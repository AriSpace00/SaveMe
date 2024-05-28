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
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_baisc.bmp");	// 플레이어 기본

	m_pTexs[(int)PORTAIT_TYPE::PLAYER_PANIC] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_BASIC", L"texture\\portrait\\s_portrait_panic.bmp");	 // 플레이어 패닉
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SMILE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SMILE", L"texture\\portrait\\S_portrait_smile.bmp");	// 플레이어 쪼갬
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_SURPRISE] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_SURPRISE", L"texture\\portrait\\s_portrait_surpris.bmp");	// 플레이어 놀람
	
	m_pTexs[(int)PORTAIT_TYPE::PLAYER_THINKING] = CResMgr::GetInst()
		->LoadTexture(L"PLAYER_THINKING", L"texture\\portrait\\S_portrait_thinking.bmp");	// 플레이어 생각중
	
	m_pTexs[(int)PORTAIT_TYPE::DS_OBJ] = CResMgr::GetInst()->LoadTexture(L"DS_OBJ", L"texture\\portrait\\brain_object.bmp"); // 기획 정수
	
	m_pTexs[(int)PORTAIT_TYPE::ART_OBJ] = CResMgr::GetInst()->LoadTexture(L"ART_OBJ", L"texture\\portrait\\eyeball_object.bmp"); // 아트 정수
	
	m_pTexs[(int)PORTAIT_TYPE::PM_OBJ] = CResMgr::GetInst()->LoadTexture(L"PM_OBJ", L"texture\\portrait\\hand_object.bmp"); // 플밍 정수
	
	m_pTexs[(int)PORTAIT_TYPE::HEART] = CResMgr::GetInst() ->LoadTexture(L"HEART", L"texture\\portrait\\heart_object.bmp");  // 교수님 심장
	

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
	//DEFAULT 인 경우 아무것도 렌더하지 않는다
	if (nullptr == m_pTexs[arrPortait[m_curShowPortrait]])
	{
		return;
	}
	// 모든 초상화를 출력한 경우 오브젝트 삭제
	if (m_curShowPortrait >= m_totalShowPortrait)
	{
		//GameManager::GetInst()->SetMovable(true);
		DeleteObject(this);
		return;
	}

	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
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
		// 모든 초상화를 출력하면 오브젝트를 삭제한다

		//TextManager::GetInst()->clearText();
		// 지우는 작업. 필요한가



		m_curShowPortrait++;
	}
	
}
