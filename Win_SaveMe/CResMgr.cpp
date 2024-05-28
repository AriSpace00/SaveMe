#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    // ���� ��ȸ�ϸ� �޸𸮸� �Ҵ��� ���ҽ����� ��� ������
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); iter++)
    {
        delete iter->second;
    }
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // �̹� �ߺ��� Ű ���� �ִ��� üũ
    CTexture* pTex = FindTexture(_strKey);
    // �̹� �� �ȿ� �ߺ��� Ű ���� �ִٸ�, �ش� Ű ���� ����Ű�� ������ ��ȯ
    if (nullptr != pTex)
    {
        return pTex;
    }

    // �ߺ��� Ű ���� ���� ��
    // ������ ���������� ���� ���
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    // ������ ���� + ��� ���
    strFilePath += _strRelativePath;

    // ���ο� �ؽ�ó Ŭ���� �����Ͽ� �ε�
    pTex = new CTexture;
    pTex->Load(strFilePath);

    // ���ҽ��� Ű�� ��θ� ���ҽ� ��ü���� �ľ� �����ϵ��� ��
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    // Ű ���� �ش��ϴ� �ؽ�ó�� ���� �ʿ� ����
    m_mapTex.insert(make_pair(_strKey, pTex));

    // �ش� Ű ���� ����Ű�� ������ ��ȯ
    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    // Ű ���� ���ö����� Ž���Ͽ� �ش� ��ġ�� �����͸� iterator�� ������
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

    // iterator�� ���� ���� Ž������ ��
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    // ���� ���� ������ �κ�(end)�� ���� �κ��� ����Ű�� ������ ��ȯ
    return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strPath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strPath;

    return nullptr;
}
