#include "pch.h"
#include "CScene_JH_Test.h"
#include "CKeyMgr.h"
#include "CCore.h"
#include "TextManager.h"

#include <Windows.h>
#include <iostream>  
#include <string>
#include <codecvt>
#include <Imm.h>

CScene_JH_Test::CScene_JH_Test()
	: testStringArr()
	, hImc()
	, plusString{}
	, m_inputCheck(false)
	, m_isNextWord(false)
{
}

CScene_JH_Test::~CScene_JH_Test()
{
	ImmReleaseContext(CCore::GetInst()->GetMainHwnd(), hImc);
}

void CScene_JH_Test::Enter()
{
	testStringArr = "�ȳ��ϼ���";
	hImc = ImmGetContext(CCore::GetInst()->GetMainHwnd());
}

void CScene_JH_Test::Exit()
{
}

bool CScene_JH_Test::IsKoreanInputEnabled()
{
	// ���� Ȱ��ȭ�� â�� �Է� ���ؽ�Ʈ �ڵ��� ������

	HIMC hIMC = ImmGetContext(CCore::GetInst()->GetMainHwnd());
	bool koreanInputEnabled = false;

	if (hIMC)
	{
		DWORD conversionStatus = 0;
		if (ImmGetConversionStatus(hIMC, &conversionStatus, nullptr))
		{
			// ��ȯ ���¿��� �ѱ� �Է±Ⱑ ���� �ִ��� Ȯ��
			if (conversionStatus & IME_CMODE_NATIVE)
			{
				koreanInputEnabled = true;  // �ѱ� �Է±Ⱑ ���� ����
			}
		}

		ImmReleaseContext(GetForegroundWindow(), hIMC);  // �Է� ���ؽ�Ʈ �ڵ� ����
	}

	return koreanInputEnabled;
}

wstring StoWS(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring result(buf);
	delete[] buf;

	return result;
}

 
//void CScene_JH_Test::testUpdate()
//{
//	//TextOutA(CCore::GetInst()->GetMainDC(), 500, 500, testStringArr.c_str(), static_cast<int>(testStringArr.length()));
//	//TextOutA(CCore::GetInst()->GetMainDC(), 600, 500, &testStringArr[testStringArr.size() - 1], 1);
//	//
//	//DWORD compositionLength = ImmGetCompositionStringW(hImc, GCS_COMPSTR, nullptr, 0);
//	//if (compositionLength > 0)
//	//{
//	//	std::wstring composition(compositionLength / sizeof(WCHAR), L'\0');
//	//	ImmGetCompositionStringW(hImc, GCS_COMPSTR, &composition[0], compositionLength);
//	//
//	//	size_t stringLastIndex = testStringArr.size() - 1;
//	//
//	//	// composition�� std::string���� ��ȯ
//	//	int bufferSize = WideCharToMultiByte(CP_ACP, 0, composition.c_str(), -1, nullptr, 0, nullptr, nullptr);
//	//	WideCharToMultiByte(CP_ACP, 0, composition.c_str(), -1, &testStringArr[stringLastIndex], bufferSize, nullptr, nullptr);
//	//}
//
//	//if (KEY_TAP(KEY::ESC))
//	//{
//	//	if (!testStringArr.empty())
//	//		testStringArr.clear();
//	//}
//
//	if (KEY_TAP(KEY::ESC))
//	{
//		if (!testStringArr.empty())
//		{
//			testStringArr.pop_back();
//			testStringArr.pop_back();
//		}
//	}
//
//	if (IsKoreanInputEnabled())
//	{
//		WCHAR tempString[16] = { 0 };
//		DWORD compositionLength = ImmGetCompositionStringW(hImc, GCS_RESULTSTR, tempString, sizeof(tempString) - sizeof(WCHAR));
//
//		if (compositionLength > 0)
//		{
//			// �Է��ϰ� �ִ°� ���� ��
//
//			WCHAR lpszString[16] = { 0 };
//			wcscpy_s(lpszString, tempString);
//
//			int wideStrLen = wcslen(lpszString);
//			int bufferSize = WideCharToMultiByte(CP_UTF8, 0, lpszString, wideStrLen, nullptr, 0, nullptr, nullptr);
//			std::string appendString(bufferSize, '\0');  // null ���� �����Ͽ� �ʱ�ȭ
//			WideCharToMultiByte(CP_ACP, 0, lpszString, wideStrLen, &appendString[0], bufferSize, nullptr, nullptr);
//
//			// �߰��� ����
//			plusString = appendString.substr(0, appendString.length() - 1);
//
//			if ((KEY_TAP(KEY::RIGHT) || KEY_TAP(KEY::LEFT) || KEY_TAP(KEY::UP) ||
//				 KEY_TAP(KEY::DOWN) || KEY_TAP(KEY::ENTER) || KEY_TAP(KEY::SPACE)) &&
//				 m_inputCheck == false)
//			{
//				testStringArr += plusString;
//				plusString = "";
//				m_inputCheck = true;
//			}
//		}
//		else
//		{
//			// �ѱ��� �پ� , compositionLength�� 0 �� �ɶ�
//
//			if (m_inputCheck == true)
//			{
//				plusString = "";
//
//				m_inputCheck = false;
//				return;
//			}
//
//			// ���ڿ��� �߰��� ����
//			testStringArr += plusString;
//			plusString = "";
//		}
//	}
//
//	std::wstring stemp = StoWS(testStringArr);
//	LPCWSTR result = stemp.c_str();
//
//	TextManager::GetInst()->printTXT(result, { 1500,500,2500,1000 }, RGB(0, 255, 0), 50, FONT::TEST, 0.15);
//	
//	TextOutA(CCore::GetInst()->GetMainDC(), 1500, 700, testStringArr.c_str(), static_cast<int>(testStringArr.length()));
//}
