#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"

using namespace FMOD;

class SoundManager
{
	SINGLE(SoundManager);
private:

	LPCWSTR str[(UINT)BGM::END];

	// FMOD 시스템
	FMOD_SYSTEM* pSystem;
	// 배경음악 리소스를 저장할 변수
	FMOD_SOUND* pBGM[(UINT)BGM::END];
	// 효과음 리소스를 저장할 변수
	FMOD_SOUND* pSFX[(UINT)SFX::END];
	// 배경음악과 효과음 채널
	FMOD_CHANNEL* pChannel[(UINT)CH::END];
	// 중복 재생 방지
	bool isPlaying;
	UINT SFXcount;
public:
	// 배경음악 재생 (BGM::)
	// scene > enter 에서 호출합니다
	void playBGM(BGM);
	// 배경음악 멈춤 (BGM::)
	// scene > enter 에서 호출합니다
	void stopBGM();
	// 효과음 재생 (SFX::)
	// 관련된 오브젝트에서 호출합니다
	void playSFX(SFX);
};

