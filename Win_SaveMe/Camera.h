#pragma once
# include "CTexture.h"

class CObject;


// 

class Camera
{
	SINGLE(Camera);

public:

	void init();
	void update();
	void render(HDC _dc);

	// 씬 엔터에서 호출 ㅠㅠ
	void FadeIn(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_IN;
		m_fDuration = _fDuration;
		m_fcurTime = 0;

		if (0.f == m_fDuration)
			assert(nullptr);
	}

	// 문 콜라이더 엔터에서 호출 ㅠㅠ
	void FadeOut(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fDuration = _fDuration;
		m_fcurTime = 0;

		if (0.f == m_fDuration)
			assert(nullptr);
	}


private:


	/// 카메라 이펙트
	Vec2			m_vResolution;
	CAM_EFFECT		m_eEffect;		// enum 변수	
	CTexture*		m_pVeilTex;		// Fade 효과 표현용 검정 텍스쳐
	float			m_fDuration;	// 이펙트 진행시간
	float			m_fcurTime;		// 현재시간 (시간측정용도)

	CTexture* m_layTex;
	CTexture* m_contTex;
	CTexture* m_mainTex;
	CTexture* m_quitTex;
	CTexture* m_curButtonTex;

	Vec2 m_vMousePos;

	/*RECT m_Continuebutton = { 60, 342, 320, 432 };
	RECT m_Mainbutton = { 348, 342, 608, 432 };
	RECT m_Quitbutton = { 636, 342, 896, 432 };*/
	RECT m_Continuebutton;
	RECT m_Mainbutton;
	RECT m_Quitbutton;
};
