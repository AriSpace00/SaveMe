#pragma once

class CPathMgr
{
    SINGLE(CPathMgr);

private:
    // 프로젝트 경로의 문자 갯수, 255가 최대임.
    wchar_t m_szContentPath[255];

public:
    void init();
    // 수정 불가하도록 const 포인터로 경로 반환
    const wchar_t* GetContentPath() { return m_szContentPath; }
};

