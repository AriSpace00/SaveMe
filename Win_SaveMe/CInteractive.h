#pragma once
#include "CObject.h"

class CTexture;

class CInteractive :
    public CObject
{
private:
    CTexture* m_pTex;           // 이미지
    CTexture* m_fTex;
    bool m_isFloating;
   
    INTERACTIVE_TYPE m_type;   // 상호작용 종류에 따른 분류(퍼즐, 선택지, 대사)
   
    bool m_isCreated;          // 상호작용 이벤트 생성되었는지 여부 (중복 생성 방지)
    bool mm_isCreated; // 액자르 ㄹ위한.... ㅠ

    // INTERACTIVE_TYPE::JUSTSUBS

    UINT m_textCount;           // 대사의 개쇼ㅜ
    LPCWSTR m_txt[10];           // 각 대사 
    bool m_isChoose[10];
    // INTERACTIVE_TYPE::CHOOSE (위에꺼 포함)
    //UINT arr[] = { 1,3,3,1,3, }; // 한 화면에 출력될 문자열 갯수 

    int m_framenum;
    
    int m_QR_Texnum;


public:
    CInteractive();
    ~CInteractive();

    // Scene 의 Enter 에서 셋팅
    void SetTexture(CTexture* _tex);
    //void setType(int/*enum으로 어떤 오븢벡트인지 관리하자*/);
    void SetType(INTERACTIVE_TYPE _type);


    void SetTextCount(UINT _count) { m_textCount = _count; }
    void SetText(LPCWSTR _t1, LPCWSTR _t2 =L"", LPCWSTR _t3=L"", LPCWSTR _t4 = L"", LPCWSTR _t5 = L"", LPCWSTR _t6 = L"", LPCWSTR _t7 = L"", LPCWSTR _t8 = L"", LPCWSTR _t9 = L"", LPCWSTR _t10 = L"")
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
    void SetisChoose(bool _b1, bool _b2 = false, bool _b3 = false, bool _b4 = false, bool _b5 = false, bool _b6 = false, bool _b7 = false, bool _b8 = false, bool _b9 = false, bool _b10 = false)
    {
        m_isChoose[0] = _b1;
        m_isChoose[1] = _b2;
        m_isChoose[2] = _b3;
        m_isChoose[3] = _b4;
        m_isChoose[4] = _b5;
        m_isChoose[5] = _b6;
        m_isChoose[6] = _b7;
        m_isChoose[7] = _b8;
        m_isChoose[8] = _b9;
        m_isChoose[9] = _b10;


    }
    
    void SetFramenum(int _framenum) { m_framenum = _framenum; }

    void SetQRnum(int _framenum) { m_QR_Texnum = _framenum; }

    // Scene 에서 호출
    virtual void initCenterPos();
    void SetScale(Vec2 _scale);
    virtual void update();
    virtual void render(HDC _dc);

    // Collider Manager 에서 호출
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);


};

