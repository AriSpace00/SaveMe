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

	// ������ �� �ʱ�ȭ���� ����
	UINT			m_textCount;	// ���ڿ��� ����
	LPCWSTR			m_txt[10];		// ���� ��� ����
	
	// ���� �ʻ�ȭ�� ����ΰ�
	//UINT m_curShowPortrait;
	//UINT m_totalShowPortrait;

	CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];

	int arrPortait[50];

	bool m_isCreated;

public:

	CTextBox();
	~CTextBox();

	// ���ڿ��� �迭, ���ڿ� ����(�ִ� 10 ����)
	void SetTXTInfo(LPCWSTR _txt[], UINT _count)
	{
		for (UINT i = 0; i < 10; i++) m_txt[i] = L"";
		for (UINT i = 0; i < _count; i++) m_txt[i] = _txt[i];
		m_textCount = _count;
	}

	// �ִ� 10�� ������ �ʻ�ȭ ������ �޾ƿ� & �� ��� �ʻ�ȭ�� �����ϴ���(������ �������� ������)
	void SetPortrait(PORTAIT_TYPE _type[], UINT _count)
	{
		for (UINT i = 0; i < 10; i++) arrPortait[i] = (int)PORTAIT_TYPE::DEFAULT;
		for (UINT i = 0; i < _count; i++) arrPortait[i] = (int)_type[i];
		//arrPortait[i] = m_pTexs �� i -> arrPortait[0]=BASIC
		m_textCount = _count;
	}
	
	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);

};

