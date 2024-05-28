#pragma once

class CTexture;
class CSound;

class CResMgr
{
    SINGLE(CResMgr);

private:
    // 모든 텍스처는 리소스 매니저에서 관리할 것이다.
    // 텍스처는 string 키 값으로 찾아서 사용할 수 있다.
    map<wstring, CTexture*> m_mapTex;

public:
    // 키 값으로 텍스처 찾고, 경로 따라가서 로드
    CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
    // 키 값으로 중복된 텍스처 찾기
    CTexture* FindTexture(const wstring& _strKey);

    CSound* LoadSound(const wstring& _strPath);

};

