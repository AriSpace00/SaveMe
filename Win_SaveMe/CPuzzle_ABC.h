#pragma once
#include "CObject.h"

class CTexture;

class CPuzzle_ABC :
    public CObject
{
private:

	CTexture* m_pTex[27];       // ������ �̹��� default + A~Z(26) ��
    
    // Ű/ ��� �� ��Ī��
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


	// Ű/ ��� �� ��Ī��
	const wchar_t* blankKeyArr[27] = {};
	const wchar_t* blanktextureArr[27] = {};
    
    Vec2 vPos;              // �̹��� ��� ��ġ
	Vec2 vAlphabetOffest;              // �̹��� ��� ��ġ

    RECT m_button[26];        // ��ư ��ġ ���� �簢�� ����ü(���ĺ� 26^^)

    UINT m_answer[8];         // ������ ������ �迭
    UINT m_input[8];          // �÷��̾��� ������ ����
    
    UINT m_inputCount;        // ������ ����(�Է� ���� ī��Ʈ)
    UINT m_buttonPushed;      // ���� ��ư�� ���� ������ ����

    Vec2 m_vMousePos;         // ���콺 Ŭ�� ��ġ�� ���� ��ǥ

    bool m_isCorrect;



    // ��ĭ ���ĺ� ��ġ
    Vec2 blankPos[8];       // �ؽ����� ������ �� ��ǥ��
	UINT m_buttonAlphabet;      // ���� ��ư�� ���� ������ ����
    UINT m_buttonCount;
    

public:
    CPuzzle_ABC();
    ~CPuzzle_ABC();
    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
};

