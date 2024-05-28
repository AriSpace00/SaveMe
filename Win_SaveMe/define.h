#pragma once

// Singleton 매크로
#define SINGLE(type)public:\
					static type* GetInst()\
					{\
					static type mgr;\
					return & mgr;\
					}\
				private:\
					type();\
					~type();

 #define fDT CTimeMgr::GetInst()->GetfDT()
 #define DT CTimeMgr::GetInst()->GetDT()
 #define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
 #define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
 #define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
 #define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
 #define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)


enum class GROUP_TYPE
{
	DEFAULT,
	BACKGROUND, 
	INTERACTIVE,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,
	PROJ_MONSTER,
	PORTRAIT,
	MONITOR_TEXT,
	TEXT,
	UI,
	BUTTON,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	TITLE,
	OPENING,
	ROOM,
	LOBBY,
	ART,
	PM,
	//DS,
	//ELEV,

	STAGE_01,
	STAGE_02,
	TEST_JH,
	MONITER_AI,
	ENDING,
	END,
};

enum class SCENETYPE_SKIP
{
	TITLE,
	AIMONITOR_1,
	ROOM,
	CURTAIN,
	DOORLOCK,
	LOBBY,
	CLOCK,
	ART, FRAME,
	PM, ABC,
	COM_ANIM, 
	AIMONITOR_2,
	ENDING,

	END,
};

enum class INTERACTIVE_TYPE
{
	PUZZLE_ART,		// 아트반 퍼즐
	PUZZLE_PM,		// 플밍반 퍼즐
	PUZZLE_DS,		// 기획반 퍼즐
	PUZZLE_DOORLOCK,		
	//COMPUTER,
	//EXIT,
	AI_MONITOR,	// x
	PRO_DESK,	// x
	CHOOSE,		// o
	TEXTBOX,	// o
	QR,

	END,
};

enum class CLEAR_OBJECT
{
	ART,	// 아트반 획득
	PM,		// 플밍반 획득
	DS,		// 기획반 획득
	HEART,	// 교수님의 심장
	END,
};

enum class PORTAIT_TYPE
{
	DEFAULT,    // 아무것도 없음

	PLAYER_BASIC,     // 플레이어 기본
	PLAYER_PANIC,
	PLAYER_SMILE,     // 플레이어 쪼갬
	PLAYER_SURPRISE,     // 플레이어 놀람
	PLAYER_THINKING,     // 플레이어 생각중
	DS_OBJ,     // 기획 정수
	ART_OBJ,    // 아트의 정수
	PM_OBJ,     // 플밍 정수
	HEART,      // 교수님 심장

	END,
};

enum class COLLIDER_DIR
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	
	
	END,
};
enum class BGM
{
	testBGM,

	NoOpen,
	StillNoOpen_A,
	HostilePlanet,
	Kindergarden,
	GaiaInFog,
	SheDiedUp,
	StillNoOpen_B,


	END,
};

enum class SFX
{
	testSFX,
	alphabet_click,
	change,
	clock_click,
	color_change,
	curtain_sound,
	door_open,
	exclamation_mark,
	eyes_open,
	fade_out,
	frame_success,
	get_object,
	ghost_whispering_1,
	head_open,
	heavy_sound,
	Idle_ambient_loop,
	keyboard_typing,
	laptop,
	logo_lending,
	message_tone,
	monitor_eating,
	monitor_login,
	mouse_click,
	noise_keyboard_1,
	noise_keyboard_2,
	noise_keyboard_3,
	notice,
	password_click,
	player,
	question,
	receive_mail,
	sending_mail,
	shock,
	squeeze,
	warning_beep,
	warning_sound_1,
	warning_sound_2,
	zero_one_1,
	zero_one_2,
	THANKS,

	END,
};
// 채널 이름
enum class CH
{
	chSFX1,
	chSFX2,
	chSFX3,
	chSFX4,
	chSFX5,
	chSFX6,
	chSFX7,
	chSFX8,
	chSFX9,
	chSFX10,
	chSFX11,
	chSFX12,
	chBGM,

	END,
};

enum class TTYPE
{
	SUBS,
	TOP,
	MIDDLE,
	BOTTOM,
	AC_TOP,
	AC_MIDDLE,
	AC_BOTOM,
	L_NAME,
	R_NAME,
	AI_CHAT,

	END,
};

enum class TEXT_TYPE
{
	NORMAL,
	FLICKER,
	SELECT,

	END
};


enum class FONT
{
	TEST,
	DGM,

	END,
};

enum class CAM_EFFECT
{
	FADE_IN,	// 점점 어두워져 검정
	FADE_OUT,	// 점점 밝아지며 기본 배경
	NONE,		// 효과 없음
};

