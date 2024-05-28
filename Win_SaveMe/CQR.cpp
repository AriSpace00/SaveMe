#include "pch.h"
#include "CQR.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "Camera.h"
#include "SoundManager.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "GameManager.h"


CQR::CQR()
	:m_qrNum()
{
	//black_alpha channel
	m_pBGTex = CResMgr::GetInst()->LoadTexture(L"QRBG", L"texture\\QR\\black_alpha channel.bmp");

	texKeyArr[0] = L"QR_ART_FRAME";
	texKeyArr[1] = L"QR1";
	texKeyArr[2] = L"ART_FRAME_Y";
	texKeyArr[3] = L"ART_FRAME_K";
	texKeyArr[4] = L"ART_FRAME_K";


	textureArr[0] = L"texture\\puzzle_ART\\art_pr_scene.bmp";
	textureArr[1] = L"texture\\QR\\QR1.bmp";
	textureArr[2] = L"texture\\puzzle_ART\\Y.bmp";
	textureArr[3] = L"texture\\puzzle_ART\\K.bmp";
	textureArr[4] = L"texture\\puzzle_ART\\K.bmp";

	//m_qrNum = 0;
}

CQR::~CQR()
{
}

void CQR::initCenterPos()
{
	// 디스플레이 크기 정보
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2 + vPos.x;
	vPos.y = ScreenSize.y / 2 + vPos.y;
	SetPos(vPos);
}

void CQR::update()
{
	if (KEY_TAP(KEY::ESC) || KEY_TAP(KEY::SPACE))
	{
		DeleteObject(this);
	}
}

void CQR::render(HDC _dc)
{
	/// 배경 (테스트 이미지 검정 -> 추후 노트북 등으로 변경)
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);

	// 텍스처 크기 정보
	int iWidth = (int)m_pBGTex->Width();
	int iHeight = (int)m_pBGTex->Height();
	BitBlt(_dc,
		vPos.x - iWidth / 2,
		vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pBGTex->GetDC(),
		0, 0,
		SRCCOPY);

	m_pTex[m_qrNum] = CResMgr::GetInst()->LoadTexture(texKeyArr[m_qrNum], textureArr[m_qrNum]);


	// 텍스처 크기 정보
	iWidth = (int)m_pTex[m_qrNum]->Width();
	iHeight = (int)m_pTex[m_qrNum]->Height();

	// 디스플레이 중앙에 텍스처 그리기
	BitBlt(_dc,
		vPos.x - iWidth / 2,
		vPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex[m_qrNum]->GetDC(),
		0, 0,
		SRCCOPY);
}
