#pragma once
#include "CObject.h"

class CTexture;


class CPortrait :
    public CObject
{
private:
    Vec2 vPos;

    // 현재 초상화가 몇번인가
    UINT m_curShowPortrait;
    UINT m_totalShowPortrait;

    CTexture* m_pTexs[(UINT)PORTAIT_TYPE::END];

    int arrPortait[50];

public:
    CPortrait();
    ~CPortrait();

    // 최대 10개 순서로 초상화 순서를 받아옴 & 총 몇개의 초상화가 존재하는지(없으면 개수에서 제외함)
    void SetPortrait(PORTAIT_TYPE _type[], UINT _count)
    {
		for (UINT i = 0; i < 10; i++) arrPortait[i] = (int)PORTAIT_TYPE::DEFAULT;
        for (UINT i = 0; i < _count; i++) arrPortait[i] = (int)_type[i];
        //arrPortait[i] = m_pTexs 의 i -> arrPortait[0]=BASIC
        m_totalShowPortrait = _count;
    }

	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);
};

