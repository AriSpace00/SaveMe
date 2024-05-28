#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
    : m_pCurAnim(nullptr)
    , m_pOwner(nullptr)
    , m_bLoop(false)
{
}

CAnimator::~CAnimator()
{
    // 애니메이터가 소멸할 때, 이 애니메이터에 연결되어있던 애니메이션도 모두 지워줌
    map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
    for (; iter != m_mapAnim.end(); iter++)
    {
        delete iter->second;
    }
}

void CAnimator::update()
{
    if (nullptr != m_pCurAnim)
    {
        m_pCurAnim->update();

        if (m_bLoop && m_pCurAnim->IsFinish())
        {
            m_pCurAnim->SetFrame(0);
        }
    }
}

void CAnimator::render(HDC _dc)
{
    if (nullptr != m_pCurAnim)
    {
        m_pCurAnim->render(_dc);
    }
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
    CAnimation* pAnim = FindAnimation(_strName);
    assert(nullptr == pAnim);

    pAnim = new CAnimation;

    pAnim->SetName(_strName);
    pAnim->m_pAnimator = this;
    pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

    m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::StopFrame(const wstring& _strName, int _frame)
{
    m_pCurAnim->m_bFinish = false;

    CAnimation* pAnim = FindAnimation(_strName);
    pAnim->SetFrame(_frame);
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
    map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

    if (iter == m_mapAnim.end())
    {
        return nullptr;
    }

    return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bLoop)
{
    m_pCurAnim = FindAnimation(_strName);
    m_bLoop = _bLoop;
}

void CAnimator::DeleteAnimation(const wstring& _strName)
{
    CAnimation* pAnim = FindAnimation(_strName);

    map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
    for (; iter != m_mapAnim.end(); iter++)
    {
        m_mapAnim.erase(_strName);
    }

    delete pAnim;
}




