#pragma once
#include "CObject.h"

class CTexture;

class CUI_Title :
    public CObject
{
private:

    CTexture* m_pBGTex;     // ��� �̹���
	CTexture* m_pYesTex;    // NO/YES/DEFAULT ������
	CTexture* m_pNoTex;    // NO/YES/DEFAULT ������

	UINT button_state;		// 0�̸� �ȴ���, 1�̸� YES, 2�� NO

	Vec2 vPos;              // �̹��� ��� ��ġ
	Vec2 m_vMousePos;         // ���콺 Ŭ�� ��ġ�� ���� ��ǥ

	RECT m_button[2];       // ��ư ��ġ ��ǥ ����ü (��ư�� ��, ������ �ΰ�)

	bool m_fadeOut;
	double delay;

	const wchar_t* yesTexKeyArr[3] = {};
	const wchar_t* yesTextureArr[3] = {};

	const wchar_t* noTexKeyArr[3] = {};
	const wchar_t* noTextureArr[3] = {};

public:
	CUI_Title();
	~CUI_Title();

	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);

};

