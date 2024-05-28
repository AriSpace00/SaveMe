#pragma once
#include "CObject.h"

class CTexture;

class CPuzzle_Clock :
    public CObject
{
private:
	CTexture* m_pBGTex;     // 배경 이미지
	CTexture* m_pTex[3];       // 시계의 기본 이미지(버튼 안눌려 있는 상태)

	CTexture* m_pHourTex[2];      // 시계 시간 숫자 이미지
	CTexture* m_pMinTex[2];       // 시계 분 숫자 이미지
	CTexture* m_pDotTex;     // 배경 이미지

	Vec2 vPos;              // 이미지 출력 위치

	RECT m_button[2];       // 버튼 위치 좌표 구조체 (버튼은 시, 분으로 두개)

	UINT m_answer[2];         // 정답을 저장할 배열 시/분
	UINT m_input[2];          // 플레이어의 정답을 저장 시/분

	bool isCorrect;

	Vec2 m_vMousePos;         // 마우스 클릭 위치를 받을 좌표

	bool m_isCorrect;

	// 시계 시/ 분용 숫자 키값 & 경로 배열
	const wchar_t* texKeyArr[10] = {};
	const wchar_t* textureArr[10] = {};

	const wchar_t* buttonTexKeyArr[3] = {};
	const wchar_t* buttonTextureArr[3] = {};

	UINT button_state;		// 0은 기본, 1은 분이 눌린 상태, 2는 시간이 눌린상태

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

