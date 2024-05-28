#pragma once
#include "CObject.h"


class AI_TextObj :
	public CObject
{
private:
	LPCWSTR m_text;
	HFONT m_hfont;
	HDC m_mdc;
	Vec2 m_textPos;
	UINT m_fontSize;

	TEXT_TYPE m_textType;
	bool m_IsVisibleText;

	bool m_IsFlicker;
	float m_flickerTime = 0;

	bool m_IsSelectUp;

	LPCWSTR m_textUp;
	LPCWSTR m_textDown;

public:
	virtual void initCenterPos();
	virtual void update();
	virtual void render(HDC _dc);

public:
	void SetTextData(LPCWSTR _text, UINT _fontSize, TEXT_TYPE _textType = TEXT_TYPE::NORMAL);
	void DrawMyText();
	void FlickerText();

	void SetSelctText(LPCWSTR _text1, LPCWSTR _text2);

	void SetTextPos(Vec2 _pos) { m_textPos.x = _pos.x; m_textPos.y = _pos.y; }
	Vec2 GetTextPos() { return m_textPos; }

	void SetVisible(bool _isVisible) { m_IsVisibleText = _isVisible; }
	bool GetVisible() { return m_IsVisibleText; }
	
	bool GetIsUpSelect() { return m_IsSelectUp; }

	TEXT_TYPE GetTextType() { return m_textType; }
	LPCWSTR GetText() { return m_text; }

	LPCWSTR SelectText();

public:
	AI_TextObj();
	~AI_TextObj();
};

