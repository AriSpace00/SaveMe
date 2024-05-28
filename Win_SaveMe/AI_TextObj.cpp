#include "pch.h"
#include "AI_TextObj.h"
#include "CCore.h"
#include "TextManager.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

AI_TextObj::AI_TextObj()
	: m_text(0)
	, m_textPos(500, 500)
	, m_hfont(0)
	, m_IsVisibleText(false)
	, m_textType(TEXT_TYPE::NORMAL)
	, m_IsFlicker(false)
	, m_flickerTime(0)
	, m_fontSize(30)
	, m_IsSelectUp(false)
	, m_textUp(L"UP")
	, m_textDown(L"DOWN")

{
	m_mdc = CCore::GetInst()->TestMemDC();
}

AI_TextObj::~AI_TextObj()
{
}

void AI_TextObj::SetTextData(LPCWSTR _text, UINT _fontSize, TEXT_TYPE _textType)
{
	m_text = _text;
	m_textType = _textType;
	m_fontSize = _fontSize;

	//Vec2 textPos = GetTextPos();
	//textPos.x = _textPos.x;
	//textPos.y = _textPos.y;

	//SetTextPos(textPos);

	// 글꼴 생성
	m_hfont = CreateFont(
		m_fontSize,          // 글꼴 높이
		0,                  // 글꼴 너비
		0,                  // 텍스트 각도
		0,                  // 기울기 각도
		FW_NORMAL,          // 글꼴 두께
		FALSE,              // Italic 여부
		FALSE,              // 밑줄 여부
		FALSE,              // 취소선 여부
		DEFAULT_CHARSET,    // 문자 집합
		OUT_DEFAULT_PRECIS, // 출력 정밀도
		CLIP_DEFAULT_PRECIS,// 클리핑 정밀도
		DEFAULT_QUALITY,             // 출력 품질
		DEFAULT_PITCH | FF_SWISS,   // 글꼴 모양
		L"DungGeunMo"                  // 글꼴 이름
	);

}

void AI_TextObj::DrawMyText()
{
	HFONT hOldFont = static_cast<HFONT>(SelectObject(m_mdc, m_hfont));
	SetTextColor(m_mdc, RGB(255, 255, 255)); // 텍스트 색상 (RGB)
	SetBkMode(m_mdc, TRANSPARENT);

	Vec2 textPos = GetTextPos();
	TextOut(m_mdc, textPos.x, textPos.y, m_text, lstrlen(m_text));

	// 이전 글꼴로 복원 // 생성한 글꼴 해제
	SelectObject(m_mdc, hOldFont);
}

void AI_TextObj::SetSelctText(LPCWSTR _text1, LPCWSTR _text2)
{
	m_textUp = _text1;
	m_textDown = _text2;
}

LPCWSTR AI_TextObj::SelectText()
{
	HFONT hOldFont = static_cast<HFONT>(SelectObject(m_mdc, m_hfont));
	SetBkMode(m_mdc, TRANSPARENT);
	Vec2 textPos = GetTextPos(); 
	
	if (m_IsSelectUp)
	{
		// 선택 색깔
		SetTextColor(m_mdc, RGB(255, 0, 0));
		TextOut(m_mdc, textPos.x, textPos.y, m_textUp, lstrlen(m_textUp));

		// 선택 안한 색깔
		SetTextColor(m_mdc, RGB(255, 255, 255));
		TextOut(m_mdc, textPos.x, textPos.y + m_fontSize, m_textDown, lstrlen(m_textDown));

		m_text = m_textUp;
	}
	else
	{
		// 선택 안한 색깔
		SetTextColor(m_mdc, RGB(255, 255, 255));
		TextOut(m_mdc, textPos.x, textPos.y, m_textUp, lstrlen(m_textUp));

		// 선택 색깔
		SetTextColor(m_mdc, RGB(255, 0, 0));
		TextOut(m_mdc, textPos.x, textPos.y + m_fontSize, m_textDown, lstrlen(m_textDown));

		m_text = m_textDown;
	}

	// 이전 글꼴로 복원 // 생성한 글꼴 해제
	SelectObject(m_mdc, hOldFont);

	if (KEY_TAP(KEY::W))
	{
		m_IsSelectUp = true;
	}
	else if (KEY_TAP(KEY::S))
	{
		m_IsSelectUp = false;
	}
	else if (KEY_TAP(KEY::SPACE))
	{
		return m_text;
	}
}

void AI_TextObj::FlickerText()
{
	m_flickerTime += fDT;
	m_text = L"|";

	if (m_IsFlicker)
	{
		HFONT hOldFont = static_cast<HFONT>(SelectObject(m_mdc, m_hfont));
		SetTextColor(m_mdc, RGB(255, 255, 255)); // 텍스트 색상 (RGB)
		SetBkMode(m_mdc, TRANSPARENT);

		Vec2 textPos = GetTextPos();
		TextOut(m_mdc, textPos.x, textPos.y, m_text, lstrlen(m_text));

		// 이전 글꼴로 복원 // 생성한 글꼴 해제
		SelectObject(m_mdc, hOldFont);
	}

	if (m_flickerTime > 0.5f)
	{
		m_IsFlicker = !m_IsFlicker;
		m_flickerTime = 0.f;
	}
}

void AI_TextObj::render(HDC _dc)
{
	if (m_IsVisibleText)
	{
		switch (m_textType)
		{
		case TEXT_TYPE::NORMAL:    DrawMyText();    break;
		case TEXT_TYPE::FLICKER:   FlickerText();   break;
		case TEXT_TYPE::SELECT:    SelectText();    break;
		}
	}
}

void AI_TextObj::initCenterPos()
{
}

void AI_TextObj::update()
{
}
