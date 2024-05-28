#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
    : m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
    // 현재 디렉토리 경로 추출
    GetCurrentDirectory(255, m_szContentPath);

    // 현재 디렉토리 경로의 길이
    size_t iLen = wcslen(m_szContentPath);

    // '\\' 기준으로 상위 폴더 체크
    for (int i = (int)(iLen - 1); 0 <= i; i--)
    {
        if ('\\' == m_szContentPath[i])
        {
            // 경로 문자열의 끝 체크
            m_szContentPath[i] = '\0';
            break;
        }
    }

    // 리소스 폴더 이어붙여서 연결시키기
    wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

    // 윈도우 창에 띄워서 경로 확인
    SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
