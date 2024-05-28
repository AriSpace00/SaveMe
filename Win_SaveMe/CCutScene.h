#pragma once
#include "CObject.h"



class CTexture;

class CCutScene :
    public CObject
{
private:
    CTexture* m_pTex;
    UINT m_textCount;           // 대사의 개쇼ㅜ
    LPCWSTR m_txt[10];           // 각 대사 

public:
    CCutScene();
    ~CCutScene();

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
    void SetTexture(CTexture* _tex);

    void SetTextCount(UINT _count) { m_textCount = _count; }
    void SetText(LPCWSTR _t1, LPCWSTR _t2 = L"", LPCWSTR _t3 = L"", LPCWSTR _t4 = L"", LPCWSTR _t5 = L"", LPCWSTR _t6 = L"", LPCWSTR _t7 = L"", LPCWSTR _t8 = L"", LPCWSTR _t9 = L"", LPCWSTR _t10 = L"")
    {
        m_txt[0] = _t1;
        m_txt[1] = _t2;
        m_txt[2] = _t3;
        m_txt[3] = _t4;
        m_txt[4] = _t5;
        m_txt[5] = _t6;
        m_txt[6] = _t7;
        m_txt[7] = _t8;
        m_txt[8] = _t9;
        m_txt[9] = _t10;
    }

};

