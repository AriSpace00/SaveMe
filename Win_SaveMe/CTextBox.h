#pragma once
#include "CObject.h"

class CTexture;

class CTextBox :
	public CObject
{
private:

	CTexture*		m_pTex;
	Vec2			vPos;
	UINT			m_curShowText;

	// 생성할 때 초기화해줄 내용
	UINT			m_textCount;	// 문자열의 개수
	LPCWSTR			m_txt[10];		// 문장 출력 변수
	
	// 현재 초상화가 몇번인가
	//UINT m_curShowPortrait;
	//UINT m_totalShowPortrait;

	CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];

	int arrPortait[50];

	bool m_isCreated;

public:

	CTextBox();
	~CTextBox();

	// 문자열의 배열, 문자열 개수(최대 10 문장)
	void SetTXTInfo(LPCWSTR _txt[], UINT _count)
	{
		for (UINT i = 0; i < 10; i++) m_txt[i] = L"";
		for (UINT i = 0; i < _count; i++) m_txt[i] = _txt[i];
		m_textCount = _count;
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

