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
	// 현재 카운트
	QueryPerformanceCounter(&m_11PrevCount);

	// 초당 카운트 횟수 (천만..)
	QueryPerformanceFrequency(&m_11Frequency);
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_11CurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_11CurCount.QuadPart - m_11PrevCount.QuadPart) / (double)m_11Frequency.QuadPart;

	// 이전 카운트 값을 현재값으로 갱신 (다음번에 계산을 위해서)
	m_11PrevCount = m_11CurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;  // DT 누적

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
