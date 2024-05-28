#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"

#include "CEventMgr.h"
#include "Camera.h"
#include "CPathMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
	, m_screenSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN))

{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	// �ػ󵵿� �°� ������ ũ�� ����
//	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
//	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // true�� �޴��ٸ� �����ؼ� ����ش޶�� ��
//	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DC�� ������
	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init(); // ��ζ� �� ó���� �ʱ�ȭ����
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	Camera::GetInst()->init();

	return S_OK;
}

void CCore::CreateBrushPen()
{
	// Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// [red blue green] pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::progress()
{
	// ==============
	// Manager Update 
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// �浹üũ
	CCollisionMgr::GetInst()->update();



	// =========
	// Rendering
	// =========
	// ȭ�� û��

//	HBRUSH h_brush = CreateSolidBrush(RGB(255, 255, 255));
//	HBRUSH h_Oldbrush = (HBRUSH)SelectObject(m_memDC, h_brush);
//	Rectangle(m_memDC, 0, 0, m_ptResolution.x, m_ptResolution.y);


//	 Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	 CTimeMgr::GetInst()->render();


//	 SelectObject(m_memDC, h_Oldbrush);
//	 DeleteObject(h_brush);

	// ==============
	// �̺�Ʈ ����ó��
	// ==============

	CEventMgr::GetInst()->update();
}