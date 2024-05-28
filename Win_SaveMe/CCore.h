#pragma once

class CCore
{
public:
	SINGLE(CCore);

private:
	HWND m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC;			// ���� �����쿡 Draw �� DC

	HBITMAP m_hBit;
	HDC m_memDC;

	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	Vec2 m_screenSize;


public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC TestMemDC() { return m_memDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

	Vec2 GetScreenSize() { return m_screenSize; }
};