#include "pch.h"
#include "CTimeMgr.h"
#include "TextManager.h"
#include "CCore.h"

TextManager::TextManager()
	: hFont{}
	,oldFont{}

{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	// f2str �迭 �� �Ҵ�
	f2str[(UINT)FONT::TEST] = L"���� �ձ۾� 2022 ������";
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

	// std �迭 �� �Ҵ�
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

	

	// ��Ʈ ������ ����� �� �ִ� ��Ʈ ���ҽ��� ������ش�
	AddFontResourceA("content\\font\\testTXT.ttf");
	AddFontResourceA("content\\font\\DungGeunMo.ttf");

	// �ؽ�Ʈ ����� memDC �޾ƿ���
	hdc = CCore::GetInst()->TestMemDC();

	bClear = false;

}
TextManager::~TextManager()
{
	DeleteDC(hdc);
}
bool TextManager::printTXT(LPCWSTR _txt, RECT _rt, COLORREF _cr, int _fs, FONT font, double _dt)
{
	// ����� hfont �� ��Ʈ�� ��������ش�
	hFont = CreateFont(_fs, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// ���� ����
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, _cr);
	// �޾ƿ� ���ڿ��� ����
	int len = lstrlenW(_txt);
	// ��µ� ���ڿ�
	WCHAR displayTXT[500] = { ' ' };
	// ��µ� ���� ��
	static int displayLen = 0;
	// ���� �ð�
	static double accumulatedTime = 0.0;
	accumulatedTime += CTimeMgr::GetInst()->GetDT();
	if (bClear)
	{
		// ������ ���� ���� ���� ��µ� ���� �� �� �ʱ�ȭ
		displayLen = 0;
		accumulatedTime = 0;
		bClear = false;
	}

	// ������ Ÿ�Ӹ�ŭ �ð��� �帣�� (������ ����)
	if (accumulatedTime >= _dt)
	{
		// ��µ� ���� �� ++
		displayLen++;
		// ���� �ð� �ʱ�ȭ
		accumulatedTime -= _dt;
	}
	// ��µ� ���ڼ���ŭ �迭�� ���� �Ҵ�
	for (int i = 0; i < displayLen; i++)
	{
		displayTXT[i] = _txt[i];
	}

	// �������� �ι��� �־��ֱ�
//	displayTXT[displayLen] = '\0';
	
	if(displayLen < len)
	{
		// ���� ���ڿ� ����ϱ� (ũ�� ����)
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
	
		// ���ڿ��� ��� ����ߴٸ� false ��ȯ
		return false;
	}
	return true;

	
}
bool TextManager::printSTDTXT(LPCWSTR _txt, TTYPE _type)
{
	// ����� hfont �� ��Ʈ�� ��������ش�
	hFont = CreateFont(textStyle[(UINT)_type].fontSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)textStyle[(UINT)_type].font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// ��� ������
	SetBkMode(hdc, TRANSPARENT);
	// ���� ����
	SetTextColor(hdc, textStyle[(UINT)_type].cr4text);
	// �޾ƿ� ���ڿ��� ����
	int len = lstrlenW(_txt);
	// ��µ� ���ڿ�
	WCHAR displayTXT[500] = { ' ' };
	// ��µ� ���� ��
	static int displayLen = 0;
	// ���� �ð�
	static double accumulatedTime = 0.0;
	accumulatedTime += CTimeMgr::GetInst()->GetDT();
	if (bClear)
	{
		// ������ ���� ���� ���� ��µ� ���� �� �� �ʱ�ȭ
		displayLen = 0;
		accumulatedTime = 0;
		bClear = false;
	}
	// ������ Ÿ�Ӹ�ŭ �ð��� �帣�� (������ ����)
	if (accumulatedTime >= textStyle[(UINT)_type].delayTime)
	{
		// ��µ� ���� �� ++
		displayLen++;
		// ���� �ð� �ʱ�ȭ
		accumulatedTime -= textStyle[(UINT)_type].delayTime; 		
	}
	
	// ��µ� ���ڼ���ŭ �迭�� ���� �Ҵ�
	for (int i = 0; i < displayLen; i++) displayTXT[i] = _txt[i];
	// �������� �ι��� �־��ֱ�
	//displayTXT[displayLen] = '\0';
	// ���� ���ڿ� ����ϱ� (ũ�� ����)
	DrawText(hdc, displayTXT, -1, &textStyle[(UINT)_type].rt4text, DT_LEFT | DT_WORDBREAK);
	// ������ ���� ���� ���� ��µ� ���� �� �� �ʱ�ȭ
	if (displayLen < len)
	{
		// ���� ���ڿ� ����ϱ� (ũ�� ����)
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
		
		// ���ڿ��� ��� ����ߴٸ� false ��ȯ
		return false;
	}
	return true;
}
void TextManager::printChat(LPCWSTR _txt)
{
	hFont = CreateFont(textStyle[(UINT)TTYPE::AI_CHAT].fontSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, f2str[(UINT)textStyle[(UINT)TTYPE::AI_CHAT].font]);
	oldFont = (HFONT)SelectObject(hdc, hFont);
	// ��� ������
	SetBkMode(hdc, TRANSPARENT);
	// ���� ����
	SetTextColor(hdc, textStyle[(UINT)TTYPE::AI_CHAT].cr4text);
	// �޾ƿ� ���ڿ��� ����
	int len = lstrlenW(_txt);
	// �޾ƿ� ���ڿ� �� �ڿ� Ŀ�� ������ �ֱ� ����... ���ڿ�
	WCHAR displayTXT[100] = { '\0', };
	for (int i = 0; i < len; i++) displayTXT[i] = _txt[i];
	// �������� �ð��� ���� �ι��� �Ǵ� Ŀ��+�ι��� �־��ֱ�
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
	// ���� ���ڿ� ����ϱ� (ũ�� ����)
	DrawText(hdc, displayTXT, -1, &textStyle[(UINT)TTYPE::AI_CHAT].rt4text, DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	return;

}

void TextManager::clearText()
{
	bClear = true;
}

