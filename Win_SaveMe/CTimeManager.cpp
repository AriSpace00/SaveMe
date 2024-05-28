#include "pch.h"
#include "CTimeManager.h"
#include "CCore.h"

#include <tchar.h>

CTimeManager::CTimeManager()
	: m_11CurCount{}
	, m_11PrevCount{}
	, m_11Frequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_11PrevCount);

	// �ʴ� ī��Ʈ Ƚ�� (õ��..)
	QueryPerformanceFrequency(&m_11Frequency);
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_11CurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_11CurCount.QuadPart - m_11PrevCount.QuadPart) / (double)m_11Frequency.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ���� (�������� ����� ���ؼ�)
	m_11PrevCount = m_11CurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;  // DT ����

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
