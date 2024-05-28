#pragma once

class TextManager
{
	SINGLE(TextManager);

private:
	HFONT hFont, oldFont;
	// ���� ���̴� �ؽ�Ʈ ��Ÿ���� �����س��� ����ü [�迭]
	struct TXT
	{
		// ��ġ // { LEFT, TOP, RIGHT, BOTTOM }
		RECT rt4text;
		// ���� // RGB(0,0,0)
		COLORREF cr4text;
		// ũ��
		int fontSize;
		// ��Ʈ
		FONT font;
		// ������
		double delayTime;
	};
	TXT textStyle[(UINT)TTYPE::END];
	// FONT�� ã�ƿ��� ���� ���ڿ��� ����
	LPCWSTR f2str[(UINT)FONT::END];
	HDC hdc;
	// �ؽ�Ʈ�� ��� ����� �� ���� ������� �Ѿ ��
	// �Լ� ���� �������� �ʱ�ȭ�� ���� ����
	bool bClear;

public:
	// �����Ӱ� �� �Լ� (L"����", rt4subs(��ġ), c4subs(����), ũ��, FONT::��Ʈ, ������(s))
	// 
	bool printTXT(LPCWSTR, RECT, COLORREF, int, FONT, double);
	// ������ ���Ĵ�� �� �Լ� (L"����", TTYPE::)
	bool printSTDTXT(LPCWSTR, TTYPE);
	// ä�� ���� �� �������� Ŀ��(|) ��������...
	void printChat(LPCWSTR);
	// �ؽ�Ʈ���� false ��ȯ ���� ��쿡�� �������־�� ��
	void clearText();
};

