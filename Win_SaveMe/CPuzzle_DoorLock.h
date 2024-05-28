#pragma once
#include "CObject.h"


class CTexture;

class CPuzzle_DoorLock :
    public CObject
{
private:
    CTexture* m_pTex[13];       // ����� �̹���... ����Ʈ ���� ���� ���� �� 10�� -> 11���� ���°�

    // Ű/ ��� �� ��Ī��
	const wchar_t* texKeyArr[13] = {};
	const wchar_t* textureArr[13] = {};

    Vec2 vPos;              // �̹��� ��� ��ġ

    RECT m_button[10];        // ��ư ��ġ ���� �簢�� ����ü
	RECT m_Checkbutton;        // ��ư ��ġ ���� �簢�� ����ü
	RECT m_Cancelbutton;        // ��ư ��ġ ���� �簢�� ����ü


    UINT m_answer[5];         // ������ ������ �迭
    UINT m_input[5];          // �÷��̾��� ������ ����
    UINT m_inputCount;        // ������ ����(�Է� ���� ī��Ʈ)
    UINT m_buttonPushed;

    Vec2 m_vMousePos;         // ���콺 Ŭ�� ��ġ�� ���� ��ǥ
    
    bool m_isCorrect;

    double m_elapsedTime;

public:
    CPuzzle_DoorLock();
    ~CPuzzle_DoorLock();

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
};

