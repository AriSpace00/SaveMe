#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
	public CObject
{
private:
	CTexture* m_pTex;

	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;
	int m_iDir;

	int m_iHP;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void initCenterPos();
	virtual void update();


public:
	CMonster();
	~CMonster();
};

