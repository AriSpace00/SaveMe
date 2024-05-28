#pragma once
#include "CObject.h"

class CTexture;
class AI_TextObj;

class CTextChoose :
    public CObject
{
private:
    
    CTexture*       m_pTex;                         // 대화창 텍스쳐
    Vec2			vPos;
    UINT			m_curShowText;

    CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];     // 초상화 배열 
    int arrPortait[50];                             // 밖에서 받을 초상화 표정 배열

    // 생성할 때 초기화해줄 내용
    UINT			m_textCount;	// 문자열의 개수
    LPCWSTR			m_txt[10];		// 문장 출력 변수

    int m_chooseNum;
    bool isChooseText[10];

    int m_noCount = 0;

    UINT m_curTexCount = 0;

    // AI monitor chat
    vector<AI_TextObj*> m_SelectTextVec;
    LPCWSTR m_stringArr[3];
    UINT m_fontSize;


public:
    CTextChoose();
    ~CTextChoose();

    // 문자열의 배열, 문자열 개수(최대 10 문장)
    void SetTXTInfo(LPCWSTR _txt[], UINT _count, bool _isChooseText[])
    {
        for (UINT i = 0; i < 10; i++) m_txt[i] = L"";
        for (UINT i = 0; i < _count; i++) m_txt[i] = _txt[i];
        m_textCount = _count;
        for (UINT i = 0; i < 10; i++) isChooseText[i] = false;
        for (UINT i = 0; i < 10; i++) isChooseText[i] = _isChooseText[i];
    }

	// 최대 10개 순서로 초상화 순서를 받아옴 & 총 몇개의 초상화가 존재하는지(없으면 개수에서 제외함)
	void SetPortrait(PORTAIT_TYPE _type[], UINT _count)
	{
		for (UINT i = 0; i < 10; i++) arrPortait[i] = (int)PORTAIT_TYPE::DEFAULT;
		for (UINT i = 0; i < _count; i++) arrPortait[i] = (int)_type[i];
		//arrPortait[i] = m_pTexs 의 i -> arrPortait[0]=BASIC
        m_textCount = _count;
	}


    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);


};

