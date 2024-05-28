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
    // ���� ���丮 ��� ����
    GetCurrentDirectory(255, m_szContentPath);

    // ���� ���丮 ����� ����
    size_t iLen = wcslen(m_szContentPath);

    // '\\' �������� ���� ���� üũ
    for (int i = (int)(iLen - 1); 0 <= i; i--)
    {
        if ('\\' == m_szContentPath[i])
        {
            // ��� ���ڿ��� �� üũ
            m_szContentPath[i] = '\0';
            break;
        }
    }

    // ���ҽ� ���� �̾�ٿ��� �����Ű��
    wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

    // ������ â�� ����� ��� Ȯ��
    SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
