#pragma once

class CRes
{
private:
    wstring m_strKey;           // 리소스 키
    wstring m_strRelativePath;  // 리소스 상대경로

public:
    // 키, 경로 설정 
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }

    // 키, 경로 반환 
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

public:
    CRes();
    ~CRes();
};

