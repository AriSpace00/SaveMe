#include "pch.h"
#include "SoundManager.h"

#pragma comment (lib, "winmm.lib")    //음악
#include <mmsystem.h>;                //음악
#include <Digitalv.h>;                //음악

using namespace std;

SoundManager::SoundManager()
	:pChannel{}
{
	// 시스템이라는걸 만들어서 초기화해준다
	FMOD_System_Create(&pSystem, FMOD_VERSION);
	FMOD_System_Init(pSystem, 32, FMOD_INIT_NORMAL, NULL);

	///BGM 리소스를 배열에 추가한다
	FMOD_System_CreateSound(pSystem, "content\\sound\\testBGM.mp3", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::testBGM]);


	///SFX 리소스를 배열에 추가한다 (1(test)+ 38(SFX))
	FMOD_System_CreateSound(pSystem, "content\\sound\\testSFX.mp3", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::testSFX]);


	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\alphabet_click.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::alphabet_click]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\change.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::change]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\clock_click.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::clock_click]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\color_change.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::color_change]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\curtain_sound.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::curtain_sound]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\door_open.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::door_open]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\exclamation_mark.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::exclamation_mark]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\eyes_open.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::eyes_open]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\fade_out.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::fade_out]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\frame_success.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::frame_success]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\get_object.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::get_object]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\ghost_whispering_1.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::ghost_whispering_1]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\head_open.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::head_open]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\heavy_sound.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::heavy_sound]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\Idle_ambient_loop.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::Idle_ambient_loop]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\keyboard_typing.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::keyboard_typing]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\laptop.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::laptop]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\logo_lending.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::logo_lending]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\message_tone.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::message_tone]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\monitor_eating.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::monitor_eating]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\monitor_login.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::monitor_login]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\mouse_click.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::mouse_click]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\noise_keyboard_1.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::noise_keyboard_1]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\noise_keyboard_2.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::noise_keyboard_2]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\noise_keyboard_3.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::noise_keyboard_3]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\notice.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::notice]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\password_click.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::password_click]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\player.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::player]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\question.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::question]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\receive_mail.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::receive_mail]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\sending_mail.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::sending_mail]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\shock.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::shock]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\squeeze.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::squeeze]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\warning_beep.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::warning_beep]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\warning_sound_1.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::warning_sound_1]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\warning_sound_2.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::warning_sound_2]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\SFX\\zero_one_1.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::zero_one_1]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\Thanks_3.wav", FMOD_LOOP_OFF, 0, &pSFX[(UINT)SFX::THANKS]);


	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\GaiaInFog.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::GaiaInFog]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\HostilePlanet.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::HostilePlanet]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\Kindergarden.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::Kindergarden]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\NoOpen.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::NoOpen]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\SheDiedUp.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::SheDiedUp]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\StillNoOpen_A.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::StillNoOpen_A]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\StillNoOpen_B.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::StillNoOpen_B]);
	FMOD_System_CreateSound(pSystem, "content\\sound\\BGM\\StillNoOpen_B.wav", FMOD_LOOP_NORMAL, 0, &pBGM[(UINT)BGM::StillNoOpen_B]);


	str[(UINT)BGM::GaiaInFog] = L"content\\sound\\BGM\\GaiaInFog.wav";
	str[(UINT)BGM::HostilePlanet] = L"content\\sound\\BGM\\HostilePlanet.wav";
	str[(UINT)BGM::Kindergarden] = L"content\\sound\\BGM\\Kindergarden.wav";
	str[(UINT)BGM::NoOpen] = L"content\\sound\\BGM\\NoOpen.wav";
	str[(UINT)BGM::SheDiedUp] = L"content\\sound\\BGM\\SheDiedUp.wav";
	str[(UINT)BGM::StillNoOpen_A] = L"content\\sound\\BGM\\StillNoOpen_A.wav";
	str[(UINT)BGM::StillNoOpen_B] = L"content\\sound\\BGM\\StillNoOpen_B.wav";


	// isPlaying 변수 초기화
	isPlaying = false;
}

void SoundManager::playBGM(BGM BGMnum)
{
	if (!isPlaying)
	{
		int volume = 100;
		DWORD dwVolume = (DWORD)(0xFFFF * volume / 100);
		PlaySound(str[(UINT)BGMnum], NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP);
		waveOutSetVolume(NULL, MAKELONG(dwVolume, dwVolume));
		isPlaying = true;
	}
	

}


SoundManager::~SoundManager()
{
	FMOD_System_Close(pSystem);
	FMOD_System_Release(pSystem);
}

//void SoundManager::playBGM(BGM BGMnum)
//{
//	if (!isPlaying)
//	{
//		FMOD_System_PlaySound(pSystem, pBGM[(UINT)BGMnum], 0, 0, &pChannel[(UINT)CH::chBGM]);
//		isPlaying = true;
//	}
//}

void SoundManager::stopBGM()
{
	{
		//FMOD_Channel_Stop(pChannel[(UINT)CH::chBGM]);
		PlaySound(NULL, NULL, NULL);

		isPlaying = false;
	}
}
void SoundManager::playSFX(SFX SFXnum)
{
	FMOD_System_PlaySound(pSystem, pSFX[(UINT)SFXnum], 0, 0, &pChannel[SFXcount]);
	SFXcount++;

	if (SFXcount == 12)
	{
		for (int i = 0; i < 12; i++) pChannel[i] = nullptr;
		SFXcount = 0;
	}
	
}