#pragma once

class CPathMgr
{
    SINGLE(CPathMgr);

private:
    // ������Ʈ ����� ���� ����, 255�� �ִ���.
    wchar_t m_szContentPath[255];

public:
    void init();
    // ���� �Ұ��ϵ��� const �����ͷ� ��� ��ȯ
    const wchar_t* GetContentPath() { return m_szContentPath; }
};

