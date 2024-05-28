#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    // 맵을 순회하며 메모리를 할당한 리소스들을 모두 지워줌
    map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
    for (; iter != m_mapTex.end(); iter++)
    {
        delete iter->second;
    }
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    // 이미 중복된 키 값이 있는지 체크
    CTexture* pTex = FindTexture(_strKey);
    // 이미 맵 안에 중복된 키 값이 있다면, 해당 키 값이 가리키는 포인터 반환
    if (nullptr != pTex)
    {
        return pTex;
    }

    // 중복된 키 값이 없을 때
    // 컨텐츠 폴더까지의 절대 경로
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    // 컨텐츠 폴더 + 상대 경로
    strFilePath += _strRelativePath;

    // 새로운 텍스처 클래스 생성하여 로드
    pTex = new CTexture;
    pTex->Load(strFilePath);

    // 리소스의 키와 경로를 리소스 자체에서 파악 가능하도록 함
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    // 키 값과 해당하는 텍스처를 묶어 맵에 삽입
    m_mapTex.insert(make_pair(_strKey, pTex));

    // 해당 키 값이 가리키는 포인터 반환
    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    // 키 값이 나올때까지 탐색하여 해당 위치의 포인터를 iterator에 저장함
    map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

    // iterator가 맵을 전부 탐색했을 때
    if (iter == m_mapTex.end())
    {
        return nullptr;
    }

    // 맵의 가장 마지막 부분(end)의 다음 부분을 가리키는 포인터 반환
    return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strPath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strPath;

    return nullptr;
}
