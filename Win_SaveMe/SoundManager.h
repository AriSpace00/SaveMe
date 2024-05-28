#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"

using namespace FMOD;

class SoundManager
{
	SINGLE(SoundManager);
private:

	LPCWSTR str[(UINT)BGM::END];

	// FMOD �ý���
	FMOD_SYSTEM* pSystem;
	// ������� ���ҽ��� ������ ����
	FMOD_SOUND* pBGM[(UINT)BGM::END];
	// ȿ���� ���ҽ��� ������ ����
	FMOD_SOUND* pSFX[(UINT)SFX::END];
	// ������ǰ� ȿ���� ä��
	FMOD_CHANNEL* pChannel[(UINT)CH::END];
	// �ߺ� ��� ����
	bool isPlaying;
	UINT SFXcount;
public:
	// ������� ��� (BGM::)
	// scene > enter ���� ȣ���մϴ�
	void playBGM(BGM);
	// ������� ���� (BGM::)
	// scene > enter ���� ȣ���մϴ�
	void stopBGM();
	// ȿ���� ��� (SFX::)
	// ���õ� ������Ʈ���� ȣ���մϴ�
	void playSFX(SFX);
};

