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

	// �۲� ����
	m_hfont = CreateFont(
		m_fontSize,          // �۲� ����
		0,                  // �۲� �ʺ�
		0,                  // �ؽ�Ʈ ����
		0,                  // ���� ����
		FW_NORMAL,          // �۲� �β�
		FALSE,              // Italic ����
		FALSE,              // ���� ����
		FALSE,              // ��Ҽ� ����
		DEFAULT_CHARSET,    // ���� ����
		OUT_DEFAULT_PRECIS, // ��� ���е�
		CLIP_DEFAULT_PRECIS,// Ŭ���� ���е�
		DEFAULT_QUALITY,             // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,   // �۲� ���
		L"DungGeunMo"                  // �۲� �̸�
	);

}

void AI_TextObj::DrawMyText()
{
	HFONT hOldFont = static_cast<HFONT>(SelectObject(m_mdc, m_hfont));
	SetTextColor(m_mdc, RGB(255, 255, 255)); // �ؽ�Ʈ ���� (RGB)
	SetBkMode(m_mdc, TRANSPARENT);

	Vec2 textPos = GetTextPos();
	TextOut(m_mdc, textPos.x, textPos.y, m_text, lstrlen(m_text));

	// ���� �۲÷� ���� // ������ �۲� ����
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
		// ���� ����
		SetTextColor(m_mdc, RGB(255, 0, 0));
		TextOut(m_mdc, textPos.x, textPos.y, m_textUp, lstrlen(m_textUp));

		// ���� ���� ����
		SetTextColor(m_mdc, RGB(255, 255, 255));
		TextOut(m_mdc, textPos.x, textPos.y + m_fontSize, m_textDown, lstrlen(m_textDown));

		m_text = m_textUp;
	}
	else
	{
		// ���� ���� ����
		SetTextColor(m_mdc, RGB(255, 255, 255));
		TextOut(m_mdc, textPos.x, textPos.y, m_textUp, lstrlen(m_textUp));

		// ���� ����
		SetTextColor(m_mdc, RGB(255, 0, 0));
		TextOut(m_mdc, textPos.x, textPos.y + m_fontSize, m_textDown, lstrlen(m_textDown));

		m_text = m_textDown;
	}

	// ���� �۲÷� ���� // ������ �۲� ����
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
		SetTextColor(m_mdc, RGB(255, 255, 255)); // �ؽ�Ʈ ���� (RGB)
		SetBkMode(m_mdc, TRANSPARENT);

		Vec2 textPos = GetTextPos();
		TextOut(m_mdc, textPos.x, textPos.y, m_text, lstrlen(m_text));

		// ���� �۲÷� ���� // ������ �۲� ����
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
