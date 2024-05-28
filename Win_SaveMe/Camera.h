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

	// �� ���Ϳ��� ȣ�� �Ф�
	void FadeIn(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_IN;
		m_fDuration = _fDuration;
		m_fcurTime = 0;

		if (0.f == m_fDuration)
			assert(nullptr);
	}

	// �� �ݶ��̴� ���Ϳ��� ȣ�� �Ф�
	void FadeOut(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fDuration = _fDuration;
		m_fcurTime = 0;

		if (0.f == m_fDuration)
			assert(nullptr);
	}


private:


	/// ī�޶� ����Ʈ
	Vec2			m_vResolution;
	CAM_EFFECT		m_eEffect;		// enum ����	
	CTexture*		m_pVeilTex;		// Fade ȿ�� ǥ���� ���� �ؽ���
	float			m_fDuration;	// ����Ʈ ����ð�
	float			m_fcurTime;		// ����ð� (�ð������뵵)

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
