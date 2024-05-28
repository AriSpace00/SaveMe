#pragma once
#include "CObject.h"

class CTexture;

class CPuzzle_ABC :
    public CObject
{
private:

	CTexture* m_pTex[27];       // 퍼즐의 이미지 default + A~Z(26) ㅋ
    
    // 키/ 경로 값 매칭용
    const wchar_t* texKeyArr[27] = {};
    const wchar_t* textureArr[27] = {};

    //CTexture* m_pblankTex[8];

	CTexture* m_pBlankTex1;
	CTexture* m_pBlankTex2;
	CTexture* m_pBlankTex3;
	CTexture* m_pBlankTex4;
	CTexture* m_pBlankTex5;
	CTexture* m_pBlankTex6;
	CTexture* m_pBlankTex7;
	CTexture* m_pBlankTex8;


	// 키/ 경로 값 매칭용
	const wchar_t* blankKeyArr[27] = {};
	const wchar_t* blanktextureArr[27] = {};
    
    Vec2 vPos;              // 이미지 출력 위치
	Vec2 vAlphabetOffest;              // 이미지 출력 위치

    RECT m_button[26];        // 버튼 위치 지정 사각형 구조체(알파벳 26^^)

    UINT m_answer[8];         // 정답을 저장할 배열
    UINT m_input[8];          // 플레이어의 정답을 저장
    
    UINT m_inputCount;        // 정답의 개수(입력 개수 카운트)
    UINT m_buttonPushed;      // 눌린 버튼이 뭔지 저장할 변수

    Vec2 m_vMousePos;         // 마우스 클릭 위치를 받을 좌표

    bool m_isCorrect;



    // 빈칸 알파벳 위치
    Vec2 blankPos[8];       // 텍스쳐의 중점이 될 좌표값
	UINT m_buttonAlphabet;      // 눌린 버튼이 뭔지 저장할 변수
    UINT m_buttonCount;
    

public:
    CPuzzle_ABC();
    ~CPuzzle_ABC();
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
};

