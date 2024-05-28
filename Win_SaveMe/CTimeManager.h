#pragma once

class CTimeManager
{
	SINGLE(CTimeManager);

private:
	LARGE_INTEGER m_11CurCount;
	LARGE_INTEGER m_11PrevCount;
	LARGE_INTEGER m_11Frequency;

	double		  m_dDT;   // ������ ������ �ð� ��
	double		  m_dAcc;  // 1�� üũ�� ���� ���� �ð�
	UINT		  m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT		  m_iFPS;  // �ʴ� ȣ�� Ƚ��

	// FPS
	// 1 �����Ӵ� �ð� (Delta TIme)

public:
	void init();
	void update();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

