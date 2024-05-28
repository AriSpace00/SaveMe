#pragma once
#include "CObject.h"

class CTexture;

class CQR :
    public CObject
{
private:
    UINT m_qrNum;

    CTexture* m_pBGTex;

    CTexture* m_pTex[5];    // 1��Ī ��µ� QR ������ŭ
    const wchar_t* texKeyArr[5] = {};
    const wchar_t* textureArr[5] = {};

    Vec2 vPos;              // �̹��� ��� ��ġ

public:
    CQR();
    ~CQR();

    void SetQrNum(int _num)
    {
        m_qrNum = _num;
    }

    virtual void initCenterPos();
    virtual void update();
    virtual void render(HDC _dc);
};

