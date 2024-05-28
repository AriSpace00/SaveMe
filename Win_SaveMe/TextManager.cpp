#include "pch.h"
#include "CTimeMgr.h"
#include "TextManager.h"
#include "CCore.h"

TextManager::TextManager()
	: hFont{}
	,oldFont{}

{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	// f2str 배열 값 할당
	f2str[(UINT)FONT::TEST] = L"교보 손글씨 2022 김혜남";
	f2str[(UINT)FONT::DGM] = L"DungGeunMo";

	textStyle[(UINT)TTYPE::AI_CHAT].rt4text
		= { (int)vResolution.x / 2 - 300
		,(int)vResolution.y / 2 + 500
		,(int)vResolution.x
		,(int)vResolution.y };
	textStyle[(UINT)TTYPE::AI_CHAT].cr4text = RGB(255, 0, 0);
	textStyle[(UINT)TTYPE::AI_CHAT].fontSize = 60;
	textStyle[(UINT)TTYPE::AI_CHAT].font = FONT::DGM;
	textStyle[(UINT)TTYPE::AI_CHAT].delayTime = 0.05f;

	// std 배열 값 할당
	textStyle[(UINT)TTYPE::SUBS].rt4text
		= {  (int)vResolution.x / 2 - 370
			,(int)vResolution.y / 2 + 270
			,(int)vResolution.x / 2 + 700
			,(int)vResolution.y / 2 + 470 };	
	textStyle[(UINT)TTYPE::SUBS].cr4text = RGB(255, 0, 0);
	textStyle[(UINT)TTYPE::SUBS].fontSize = 60;
	textStyle[(UINT)TTYPE::SUBS].font = FONT::DGM;
	textStyle[(UINT)TTYPE::SUBS].delayTime = 0.05f;
	
	textStyle[(UINT)TTYPE::L_NAME].rt4text = { 200,500,400,600 };
	textStyle[(UINT)TTYPE::L_NAME].cr4text = RGB(200, 100, 100);
	textStyle[(UINT)TTYPE::L_NAME].fontSize = 30;
	textStyle[(UINT)TTYPE::L_NAME].font = FONT::DGM;
	textStyle[(UINT)TTYPE::L_NAME].delayTime = 0.f;

	textStyle[(UINT)TTYPE::TOP].rt4text
		= { (int)vResolution.x / 2 - 370
			,(int)vResolution.y / 2 + 270
			,(int)vResolution.x / 2 + 700
			,(int)vResolution.y / 2 + 340 };
	textStyle[(UINT)TTYPE::TOP].cr4text = RGB(255, 255, 255);
	textStyle[(UINT)TTYPE::TOP].fontSize = 60;
	textStyle[(UINT)TTYPE::TOP].font = FONT::DGM;
	textStyle[(UINT)TTYPE::TOP].delayTime = 0.1f;

	textStyle[(UINT)TTYPE::MIDDLE].rt4text
		= { (int)vResolution.x / 2 - 370
			,(int)vResolution.y / 2 + 340
			,(int)vResolution.x / 2 + 700
			,(int)vResolution.y / 2 + 410 };
	textStyle[(UINT)TTYPE::MIDDLE].cr4text = RGB(255, 255, 255);
	textStyle[(UINT)TTYPE::MIDDLE].fontSize = 60;
	textStyle[(UINT)TTYPE::MIDDLE].font = FONT::DGM;
	textStyle[(UINT)TTYPE::MIDDLE].delayTime = 0.1f;

	textStyle[(UINT)TTYPE::AC_TOP].rt4text
		= { (int)vResolution.x / 2 - 370
			,(int)vResolution.y / 2 + 270
			,(int)vResolution.x / 2 + 700
			,(int)vResolution.y / 2 + 340 };
	textStyle[(UINT)TTYPE::AC_TOP].cr4text = RGB(255, 0, 0);
	textStyle[(UINT)TTYPE::AC_TOP].fontSize = 60;
	textStyle[(UINT)TTYPE::AC_TOP].font = FONT::DGM;
	textStyle[(UINT)TTYPE::AC_TOP].delayTime = 0.f;

	textStyle[(UINT)TTYPE::AC_MIDDLE].rt4text
		= { (int)vResolution.x / 2 - 370
			,(int)vResolution.y / 2 + 340
			,(int)vResolution.x / 2 + 700
			,(int)vResolution.y / 2 + 410 };
	textStyle[(UINT)TTYPE::AC_MIDDLE].cr4text = RGB(255, 0, 0);
	textStyle[(UINT)TTYPE::AC_MIDDLE].fontSize = 60;
	textStyle[(UINT)TTYPE::AC_MIDDLE].font = FONT::DGM;
	textStyle[(UINT)TTYPE::AC_MIDDLE].delayTime = 0.f;

	

	// 폰트 파일을 사용할 수 있는 폰트 리소스로 만들어준다
	AddFontResourceA("content\\font\\testTXT.ttf");
	AddFontResourceA("content\\font\\DungGeunMo.ttf");

	// 텍스트 출력할 memDC 받아오기
	hdc = CCore::GetInst()->TestMemDC();

	bClear = false;

}
TextManager::~TextManager()
{
	DeleteDC(hdc);
}
bool TextManager::printTXT(LPCWSTR _txt, RECT _rt, COLORREF _cr, int _fs, FONT font, double _dt)
{
	// 사용할 hfont 에 폰트를 적용시켜준다
	hFont = CreateFont(_fs, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// 색상 적용
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, _cr);
	// 받아온 문자열의 길이
	int len = lstrlenW(_txt);
	// 출력될 문자열
	WCHAR displayTXT[500] = { ' ' };
	// 출력될 글자 수
	static int displayLen = 0;
	// 누적 시간
	static double accumulatedTime = 0.0;
	accumulatedTime += CTimeMgr::GetInst()->GetDT();
	if (bClear)
	{
		// 다음에 사용될 때를 위해 출력될 글자 수 값 초기화
		displayLen = 0;
		accumulatedTime = 0;
		bClear = false;
	}

	// 딜레이 타임만큼 시간이 흐르면 (딜레이 적용)
	if (accumulatedTime >= _dt)
	{
		// 출력될 글자 수 ++
		displayLen++;
		// 누적 시간 초기화
		accumulatedTime -= _dt;
	}
	// 출력될 글자수만큼 배열에 글자 할당
	for (int i = 0; i < displayLen; i++)
	{
		displayTXT[i] = _txt[i];
	}

	// 마지막에 널문자 넣어주기
//	displayTXT[displayLen] = '\0';
	
	if(displayLen < len)
	{
		// 이제 문자열 출력하기 (크기 적용)
		DrawText(hdc, displayTXT, -1, &_rt, DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}
	else
	{
		displayLen = len;
		DrawText(hdc, displayTXT, -1, &_rt, DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	
		// 문자열을 모두 출력했다면 false 반환
		return false;
	}
	return true;

	
}
bool TextManager::printSTDTXT(LPCWSTR _txt, TTYPE _type)
{
	// 사용할 hfont 에 폰트를 적용시켜준다
	hFont = CreateFont(textStyle[(UINT)_type].fontSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)textStyle[(UINT)_type].font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// 배경 날리기
	SetBkMode(hdc, TRANSPARENT);
	// 색상 적용
	SetTextColor(hdc, textStyle[(UINT)_type].cr4text);
	// 받아온 문자열의 길이
	int len = lstrlenW(_txt);
	// 출력될 문자열
	WCHAR displayTXT[500] = { ' ' };
	// 출력될 글자 수
	static int displayLen = 0;
	// 누적 시간
	static double accumulatedTime = 0.0;
	accumulatedTime += CTimeMgr::GetInst()->GetDT();
	if (bClear)
	{
		// 다음에 사용될 때를 위해 출력될 글자 수 값 초기화
		displayLen = 0;
		accumulatedTime = 0;
		bClear = false;
	}
	// 딜레이 타임만큼 시간이 흐르면 (딜레이 적용)
	if (accumulatedTime >= textStyle[(UINT)_type].delayTime)
	{
		// 출력될 글자 수 ++
		displayLen++;
		// 누적 시간 초기화
		accumulatedTime -= textStyle[(UINT)_type].delayTime; 		
	}
	
	// 출력될 글자수만큼 배열에 글자 할당
	for (int i = 0; i < displayLen; i++) displayTXT[i] = _txt[i];
	// 마지막에 널문자 넣어주기
	//displayTXT[displayLen] = '\0';
	// 이제 문자열 출력하기 (크기 적용)
	DrawText(hdc, displayTXT, -1, &textStyle[(UINT)_type].rt4text, DT_LEFT | DT_WORDBREAK);
	// 다음에 사용될 때를 위해 출력될 글자 수 값 초기화
	if (displayLen < len)
	{
		// 이제 문자열 출력하기 (크기 적용)
		DrawText(hdc, displayTXT, -1, &textStyle[(UINT)_type].rt4text, DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
	}
	else
	{
		displayLen = len;
		DrawText(hdc, displayTXT, -1, &textStyle[(UINT)_type].rt4text, DT_LEFT | DT_WORDBREAK);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		
		// 문자열을 모두 출력했다면 false 반환
		return false;
	}
	return true;
}
void TextManager::printChat(LPCWSTR _txt)
{
	hFont = CreateFont(textStyle[(UINT)TTYPE::AI_CHAT].fontSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)textStyle[(UINT)TTYPE::AI_CHAT].font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// 배경 날리기
	SetBkMode(hdc, TRANSPARENT);
	// 색상 적용
	SetTextColor(hdc, textStyle[(UINT)TTYPE::AI_CHAT].cr4text);
	// 받아온 문자열의 길이
	int len = lstrlenW(_txt);
	// 받아온 문자열 맨 뒤에 커서 연출을 넣기 위한... 문자열
	WCHAR displayTXT[100] = { '\0', };
	for (int i = 0; i < len; i++) displayTXT[i] = _txt[i];
	// 마지막에 시간에 따라 널문자 또는 커서+널문자 넣어주기
	const double cursorDelay = 0.3;
	static bool cursorActive = true;
	static double accumulatedTime = 0.0;
	accumulatedTime += CTimeMgr::GetInst()->GetDT();
	if (accumulatedTime >= cursorDelay)
	{
		accumulatedTime -= cursorDelay;
		cursorActive = !cursorActive;
	}
	if (cursorActive) displayTXT[len] = '|';
	//displayTXT[len + 1] = '\0';
	// 이제 문자열 출력하기 (크기 적용)
	DrawText(hdc, displayTXT, -1, &textStyle[(UINT)TTYPE::AI_CHAT].rt4text, DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	return;

}

void TextManager::clearText()
{
	bClear = true;
}

