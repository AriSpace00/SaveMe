#include "pch.h"
#include "struct.h"

#include "CScene.h"

#include "CObject.h"
#include "Camera.h"
#include "CTexture.h"
#include "CBackground.h"
#include "CAnagram.h"
#include "CFloating.h"
#include "CStaticObject.h"

CScene::CScene()
	: m_arrObj{}
	, m_pAnagram(nullptr)
	, m_strName()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrBgTex[i].size(); j++)
		{
			//m_arrBgTex[i] 그룹 벡터의 j 물체 삭제
			delete m_arrBgTex[i][j];
		}
		for (size_t j = 0; j < m_staticObjTex[i].size(); ++j)
		{
			delete m_staticObjTex[i][j];
		}
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
			delete m_arrObj[i][j];
		}
		for (size_t j = 0; j < m_arrFloatingTex[i].size(); ++j)
		{
			delete m_arrFloatingTex[i][j];
		}
	}
}

void CScene::initCenterPos()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrBgTex[i].size(); j++)
		{
			m_arrBgTex[i][j]->initCenterPos();
		}

		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->initCenterPos();
		}

		for (int j = 0; j < m_arrFloatingTex[i].size(); j++)
		{
			m_arrFloatingTex[i][j]->initCenterPos();
		}

		for (int j = 0; j < m_staticObjTex[i].size(); j++)
		{
			m_staticObjTex[i][j]->initCenterPos();
		}
	}
}

//void CScene::initPos(Vec2 _TexPosInfo)
//{
//	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
//	{
//		for (int j = 0; j < m_staticObjTex[i].size(); j++)
//		{
//			m_staticObjTex[i][j]->initPos(_TexPosInfo);
//		}
//	}
//}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrBgTex[i].size(); j++)
		{
			m_arrBgTex[i][j]->update();
		}
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
		for (int j = 0; j < m_arrFloatingTex[i].size(); j++)
		{
			m_arrFloatingTex[i][j]->update();
		}
		for (int j = 0; j < m_staticObjTex[i].size(); j++)
		{
			m_staticObjTex[i][j]->update();
		}
	}
	Camera::GetInst()->update();
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrBgTex[i].size(); j++)
		{
			m_arrBgTex[i][j]->render(_dc);
		}

		for (int j = 0; j < m_staticObjTex[i].size(); j++)
		{
			m_staticObjTex[i][j]->render(_dc);
		}

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{				
				auto a = (*iter)->GetName();
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}

		for (int j = 0; j < m_arrFloatingTex[i].size(); j++)
		{
			m_arrFloatingTex[i][j]->render(_dc);
		}
	}
	Camera::GetInst()->render(_dc);
}

void CScene::SceneUpdate()
{
}

void CScene::SceneReset()
{
}
