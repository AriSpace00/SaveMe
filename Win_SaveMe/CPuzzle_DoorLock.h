#pragma once
#include "CObject.h"


class CTexture;

class CPuzzle_DoorLock :
    public CObject
{
private:
    CTexture* m_pTex[13];       // 도어락 이미지... 디폴트 상태 포함 숫자 총 10개 -> 11개의 상태값

    // 키/ 경로 값 매칭용
	const wchar_t* texKeyArr[13] = {};
	const wchar_t* textureArr[13] = {};

    Vec2 vPos;              // 이미지 출력 위치

    RECT m_button[10];        // 버튼 위치 지정 사각형 구조체
	RECT m_Checkbutton;        // 버튼 위치 지정 사각형 구조체
	RECT m_Cancelbutton;        // 버튼 위치 지정 사각형 구조체


    UINT m_answer[5];         // 정답을 저장할 배열
    UINT m_input[5];          // 플레이어의 정답을 저장
    UINT m_inputCount;        // 정답의 개수(입력 개수 카운트)
    UINT m_buttonPushed;

    Vec2 m_vMousePos;         // 마우스 클릭 위치를 받을 좌표
    
    bool m_isCorrect;

    double m_elapsedTime;

public:
    CPuzzle_DoorLock();
    ~CPuzzle_DoorLock();

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
};

