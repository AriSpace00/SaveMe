#pragma once
#include "CObject.h"

class CTexture;


class CPortrait :
    public CObject
{
private:
    Vec2 vPos;

    // ���� �ʻ�ȭ�� ����ΰ�
    UINT m_curShowPortrait;
    UINT m_totalShowPortrait;

    CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];

    int arrPortait[50];

public:
    CPortrait();
    ~CPortrait();

    // �ִ� 10�� ������ �ʻ�ȭ ������ �޾ƿ� & �� ��� �ʻ�ȭ�� �����ϴ���(������ �������� ������)
    void SetPortrait(PORTAIT_TYPE _type[], UINT _count)
    {
		for (UINT i = 0; i < 10; i++) arrPortait[i] = (int)PORTAIT_TYPE::DEFAULT;
        for (UINT i = 0; i < _count; i++) arrPortait[i] = (int)_type[i];
        //arrPortait[i] = m_pTexs �� i -> arrPortait[0]=BASIC
        m_totalShowPortrait = _count;
    }

	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);
};

