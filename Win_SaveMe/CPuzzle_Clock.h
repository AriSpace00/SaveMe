#pragma once
#include "CObject.h"

class CTexture;

class CPuzzle_Clock :
    public CObject
{
private:
	CTexture* m_pBGTex;     // ��� �̹���
	CTexture* m_pTex[3];       // �ð��� �⺻ �̹���(��ư �ȴ��� �ִ� ����)

	CTexture* m_pHourTex[2];      // �ð� �ð� ���� �̹���
	CTexture* m_pMinTex[2];       // �ð� �� ���� �̹���
	CTexture* m_pDotTex;     // ��� �̹���

	Vec2 vPos;              // �̹��� ��� ��ġ

	RECT m_button[2];       // ��ư ��ġ ��ǥ ����ü (��ư�� ��, ������ �ΰ�)

	UINT m_answer[2];         // ������ ������ �迭 ��/��
	UINT m_input[2];          // �÷��̾��� ������ ���� ��/��

	bool isCorrect;

	Vec2 m_vMousePos;         // ���콺 Ŭ�� ��ġ�� ���� ��ǥ

	bool m_isCorrect;

	// �ð� ��/ �п� ���� Ű�� & ��� �迭
	const wchar_t* texKeyArr[10] = {};
	const wchar_t* textureArr[10] = {};

	const wchar_t* buttonTexKeyArr[3] = {};
	const wchar_t* buttonTextureArr[3] = {};

	UINT button_state;		// 0�� �⺻, 1�� ���� ���� ����, 2�� �ð��� ��������

	UINT min_count;
	UINT hour_count;

	UINT min_count2;
	UINT hour_count2;

	double elapedTime;
	double delayTime;

public:
	CPuzzle_Clock();
	~CPuzzle_Clock();

	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);

};

