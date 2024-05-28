#pragma once

class CObject;
class CBackground;
class CAnagram;
class CFloating;
class CStaticObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	vector<CBackground*> m_arrBgTex[(UINT)GROUP_TYPE::END];
	vector<CFloating*> m_arrFloatingTex[(UINT)GROUP_TYPE::END];
	vector<CStaticObject*> m_staticObjTex[(UINT)GROUP_TYPE::END];

	CAnagram* m_pAnagram;

	wstring m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void initCenterPos(); // 배경 텍스처를 디스플레이 기준 중앙으로 맞춰놓기 위해 제작한 함수
	/*void initPos(Vec2 _TexPosInfo);*/
	void update();
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0; // 해당 씬에 진입 시 사용
	virtual void Exit() = 0; // 해당 씬을 탈출 시 사용
	
	//virtual void testUpdate(); // Korean Key Input Test
	virtual void SceneUpdate(); // 씬 업데이트 테스트 함수
	virtual void SceneReset();

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	//void AddObject(CBackground* _pTex, GROUP_TYPE _eType)
	//{
	//	m_arrBgTex[(UINT)_eType].push_back(_pTex);
	//}


	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

public:
	CScene();
	virtual ~CScene();
};

