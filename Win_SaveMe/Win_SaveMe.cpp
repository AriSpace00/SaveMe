// Win_JH.cpp : 애플리케이션에 대한 진입점을 정의합니다.
// #include "Win_JH.h"  , IDC_WINJH

#include "pch.h"
#include "framework.h"
#include "Win_SaveMe.h"
#include "CCore.h"

#include "GameManager.h"

#include <wingdi.h>
#include <math.h>
#include <Imm.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HWND g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 전체 화면 사이즈 얻어오기
int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

// 윈도우 창 모니터 중앙에 띄우기
void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
{
	RECT ClientRect;
	GetClientRect(window, &ClientRect);

	int ClientWidth = ClientRect.right - ClientRect.left;
	int ClientHeight = ClientRect.bottom - ClientRect.top;

	SetWindowPos(window, NULL, ScreenWidth / 2 - ClientWidth / 2, ScreenHeight / 2 - ClientHeight / 2, ClientWidth, ClientHeight, 0);
}

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(215);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINJH, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Core 초기화
	if (FAILED(CCore::GetInst()->Init(g_hWnd, POINT{ ScreenWidth, ScreenHeight })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINJH));

	MSG msg;

	// 기본 메시지 루프입니다:

	// GetMessage
	// 메세지 큐에서 메세지 확인 될 때까지 대기
	// msg.message == WM_QUIT 인 경우 false 를 반환 -> 프로그램 종료

	// PeekMessage
	// 메세지 유무와 관계없이 반환
	// 메세지 큐에서 메세지를 확인한 경우 true, 메세지 큐에서 메세지가 없는 경우 false를 반환한다.

	// 모니터 중앙에 윈도우 출력
	PlaceInCenterOfScreen(g_hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	while (!GameManager::GetInst()->GetIsGameQuit())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// 메세지가 발생하지 않는 대부분의 시간
		else
		{
			// Game 코드 수행
			// 디자인 패턴 (설계 유형)
			// 싱글톤 패턴

			CCore::GetInst()->progress();
		}
	}

	return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINJH));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32APIAPPLICATION);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

//  < 디폴트 >
//	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	// 위에 옵션 없애고 창 만들기
	g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
		0, 0, ScreenWidth, ScreenHeight, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


#include <vector>
using std::vector;

struct tObjInfo
{
	POINT g_ptObjPos;
	POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

// 좌 상단
POINT g_ptLT;

// 우 하단
POINT g_ptRB;

bool blbtnDown = false;

// wParam = 키보드 입력 데이터 , lParam == 마우스 입력 데이터
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_IME_COMPOSITION:
	{
		// 한글 입력 중인 문자열 처리
		// lParam 매개변수에서 입력 중인 문자열 정보를 추출할 수 있음

		// 문자열 마무리 창을 없애는 처리
		// lParam 매개변수의 GCS_RESULTSTR 플래그를 확인하여 문자열 마무리인지 검사
		if (lParam & GCS_RESULTSTR)
		{
			HIMC hImc = ImmGetContext(hWnd);

			// 문자열 마무리 창이 뜨지 않도록 처리
			ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
			ImmReleaseContext(hWnd, hImc);
		}

		// 추가로 처리해야 할 작업이 있다면 여기에 작성

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
