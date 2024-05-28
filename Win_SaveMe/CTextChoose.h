#pragma once
#include "CObject.h"

class CTexture;
class AI_TextObj;

class CTextChoose :
    public CObject
{
private:
    
    CTexture*       m_pTex;                         // ��ȭâ �ؽ���
    Vec2			vPos;
    UINT			m_curShowText;

    CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];     // �ʻ�ȭ �迭 
    int arrPortait[50];                             // �ۿ��� ���� �ʻ�ȭ ǥ�� �迭

    // ������ �� �ʱ�ȭ���� ����
    UINT			m_textCount;	// ���ڿ��� ����
    LPCWSTR			m_txt[10];		// ���� ��� ����

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

    // ���ڿ��� �迭, ���ڿ� ����(�ִ� 10 ����)
    void SetTXTInfo(LPCWSTR _txt[], UINT _count, bool _isChooseText[])
    {
        for (UINT i = 0; i < 10; i++) m_txt[i] = L"";
        for (UINT i = 0; i < _count; i++) m_txt[i] = _txt[i];
        m_textCount = _count;
        for (UINT i = 0; i < 10; i++) isChooseText[i] = false;
        for (UINT i = 0; i < 10; i++) isChooseText[i] = _isChooseText[i];
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

