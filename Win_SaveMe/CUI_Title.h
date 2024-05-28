#pragma once
#include "CObject.h"

class CTexture;

class CUI_Title :
    public CObject
{
private:

    CTexture* m_pBGTex;     // 배경 이미지
	CTexture* m_pYesTex;    // NO/YES/DEFAULT 세가지
	CTexture* m_pNoTex;    // NO/YES/DEFAULT 세가지

	UINT button_state;		// 0이면 안눌림, 1이면 YES, 2면 NO

	Vec2 vPos;              // 이미지 출력 위치
	Vec2 m_vMousePos;         // 마우스 클릭 위치를 받을 좌표

	RECT m_button[2];       // 버튼 위치 좌표 구조체 (버튼은 시, 분으로 두개)

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

