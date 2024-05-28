#pragma once

class TextManager
{
	SINGLE(TextManager);

private:
	HFONT hFont, oldFont;
	// 자주 쓰이는 텍스트 스타일을 저장해놓을 구조체 [배열]
	struct TXT
	{
		// 위치 // { LEFT, TOP, RIGHT, BOTTOM }
		RECT rt4text;
		// 색상 // RGB(0,0,0)
		COLORREF cr4text;
		// 크기
		int fontSize;
		// 폰트
		FONT font;
		// 딜레이
		double delayTime;
	};
	TXT textStyle[(UINT)TTYPE::END];
	// FONT를 찾아오기 위한 문자열을 저장
	LPCWSTR f2str[(UINT)FONT::END];
	HDC hdc;
	// 텍스트를 모두 출력한 후 다음 장면으로 넘어갈 때
	// 함수 안의 정적변수 초기화를 위한 변수
	bool bClear;

public:
	// 자유롭게 쓸 함수 (L"내용", rt4subs(위치), c4subs(색상), 크기, FONT::폰트, 딜레이(s))
	// 
	bool printTXT(LPCWSTR, RECT, COLORREF, int, FONT, double);
	// 정해진 형식대로 쓸 함수 (L"내용", TTYPE::)
	bool printSTDTXT(LPCWSTR, TTYPE);
	// 채팅 쳤을 때 마지막에 커서(|) 깜빡깜빡...
	void printChat(LPCWSTR);
	// 텍스트에서 false 반환 했을 경우에만 실행해주어야 함
	void clearText();
};

