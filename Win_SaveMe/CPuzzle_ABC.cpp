#include "pch.h"
#include "CPuzzle_ABC.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTextBox.h"
#include "CKeyMgr.h"
#include "SoundManager.h"
#include "GameManager.h"

CPuzzle_ABC::CPuzzle_ABC()
    :m_answer{ 0 }, m_input{ 5 }
{
    GameManager::GetInst()->SetMovable(false);

    m_buttonPushed = 0;
    m_buttonAlphabet = 0;

    // ㅋㅋ 진짜 행복하다~
    texKeyArr[0] = L"Puzzle_PM_Default";
    texKeyArr[1] = L"Puzzle_PM_A";
    texKeyArr[2] = L"Puzzle_PM_B";
    texKeyArr[3] = L"Puzzle_PM_C";
    texKeyArr[4] = L"Puzzle_PM_D";
    texKeyArr[5] = L"Puzzle_PM_E";
    texKeyArr[6] = L"Puzzle_PM_F";
    texKeyArr[7] = L"Puzzle_PM_G";
    texKeyArr[8] = L"Puzzle_PM_H";
    texKeyArr[9] = L"Puzzle_PM_I";
    texKeyArr[10] = L"Puzzle_PM_J";
    texKeyArr[11] = L"Puzzle_PM_K";
    texKeyArr[12] = L"Puzzle_PM_L";
    texKeyArr[13] = L"Puzzle_PM_M";
    texKeyArr[14] = L"Puzzle_PM_N";
    texKeyArr[15] = L"Puzzle_PM_O";
    texKeyArr[16] = L"Puzzle_PM_P";
    texKeyArr[17] = L"Puzzle_PM_Q";
    texKeyArr[18] = L"Puzzle_PM_R";
    texKeyArr[19] = L"Puzzle_PM_S";
    texKeyArr[20] = L"Puzzle_PM_T";
    texKeyArr[21] = L"Puzzle_PM_U";
    texKeyArr[22] = L"Puzzle_PM_V";
    texKeyArr[23] = L"Puzzle_PM_W";
    texKeyArr[24] = L"Puzzle_PM_X";
    texKeyArr[25] = L"Puzzle_PM_Y";
    texKeyArr[26] = L"Puzzle_PM_Z";
    
    textureArr[0] = L"texture\\puzzle_PM\\puzzle_PM_default.bmp";
    textureArr[1] = L"texture\\puzzle_PM\\A.bmp";
    textureArr[2] = L"texture\\puzzle_PM\\B.bmp";
    textureArr[3] = L"texture\\puzzle_PM\\C.bmp";
    textureArr[4] = L"texture\\puzzle_PM\\D.bmp";
    textureArr[5] = L"texture\\puzzle_PM\\E.bmp";
    textureArr[6] = L"texture\\puzzle_PM\\F.bmp";
    textureArr[7] = L"texture\\puzzle_PM\\G.bmp";
    textureArr[8] = L"texture\\puzzle_PM\\H.bmp";
    textureArr[9] = L"texture\\puzzle_PM\\I.bmp";
    textureArr[10] = L"texture\\puzzle_PM\\J.bmp";
    textureArr[11] = L"texture\\puzzle_PM\\K.bmp";
    textureArr[12] = L"texture\\puzzle_PM\\L.bmp";
    textureArr[13] = L"texture\\puzzle_PM\\M.bmp";
    textureArr[14] = L"texture\\puzzle_PM\\N.bmp";
    textureArr[15] = L"texture\\puzzle_PM\\O.bmp";
    textureArr[16] = L"texture\\puzzle_PM\\P.bmp";
    textureArr[17] = L"texture\\puzzle_PM\\Q.bmp";
    textureArr[18] = L"texture\\puzzle_PM\\R.bmp";
    textureArr[19] = L"texture\\puzzle_PM\\S.bmp";
    textureArr[20] = L"texture\\puzzle_PM\\T.bmp";
    textureArr[21] = L"texture\\puzzle_PM\\U.bmp";
    textureArr[22] = L"texture\\puzzle_PM\\V.bmp";
    textureArr[23] = L"texture\\puzzle_PM\\W.bmp";
    textureArr[24] = L"texture\\puzzle_PM\\X.bmp";
    textureArr[25] = L"texture\\puzzle_PM\\Y.bmp";
    textureArr[26] = L"texture\\puzzle_PM\\Z.bmp";


    /// 빈칸용
	// ㅋㅋ 진짜 행복하다~
	blankKeyArr[0] = L"Puzzle_PM_Default";
	blankKeyArr[1] = L"Puzzle_BLANK_A";
	blankKeyArr[2] = L"Puzzle_BLANK_B";
	blankKeyArr[3] = L"Puzzle_BLANK_C";
	blankKeyArr[4] = L"Puzzle_BLANK_D";
	blankKeyArr[5] = L"Puzzle_BLANK_E";
	blankKeyArr[6] = L"Puzzle_BLANK_F";
	blankKeyArr[7] = L"Puzzle_BLANK_G";
	blankKeyArr[8] = L"Puzzle_BLANK_H";
	blankKeyArr[9] = L"Puzzle_BLANK_I";
	blankKeyArr[10] = L"Puzzle_BLANK_J";
    blankKeyArr[11] = L"Puzzle_BLANK_K";
    blankKeyArr[12] = L"Puzzle_BLANK_L";
    blankKeyArr[13] = L"Puzzle_BLANK_M";
    blankKeyArr[14] = L"Puzzle_BLANK_N";
    blankKeyArr[15] = L"Puzzle_BLANK_O";
    blankKeyArr[16] = L"Puzzle_BLANK_P";
    blankKeyArr[17] = L"Puzzle_BLANK_Q";
    blankKeyArr[18] = L"Puzzle_BLANK_R";
	blankKeyArr[19] = L"Puzzle_BLANK_S";
	blankKeyArr[20] = L"Puzzle_BLANK_T";
	blankKeyArr[21] = L"Puzzle_BLANK_U";
	blankKeyArr[22] = L"Puzzle_BLANK_V";
	blankKeyArr[23] = L"Puzzle_BLANK_W";
	blankKeyArr[24] = L"Puzzle_BLANK_X";
	blankKeyArr[25] = L"Puzzle_BLANK_Y";
	blankKeyArr[26] = L"Puzzle_BLANK_Z";

    blanktextureArr[0] = L"texture\\puzzle_PM\\puzzle_PM_default.bmp";
	blanktextureArr[1] = L"texture\\puzzle_PM\\Answer\\Alphabet_A.bmp";
	blanktextureArr[2] = L"texture\\puzzle_PM\\Answer\\Alphabet_B.bmp";
	blanktextureArr[3] = L"texture\\puzzle_PM\\Answer\\Alphabet_C.bmp";
	blanktextureArr[4] = L"texture\\puzzle_PM\\Answer\\Alphabet_D.bmp";
	blanktextureArr[5] = L"texture\\puzzle_PM\\Answer\\Alphabet_E.bmp";
	blanktextureArr[6] = L"texture\\puzzle_PM\\Answer\\Alphabet_F.bmp";
	blanktextureArr[7] = L"texture\\puzzle_PM\\Answer\\Alphabet_G.bmp";
	blanktextureArr[8] = L"texture\\puzzle_PM\\Answer\\Alphabet_H.bmp";
	blanktextureArr[9] = L"texture\\puzzle_PM\\Answer\\Alphabet_I.bmp";
	blanktextureArr[10] = L"texture\\puzzle_PM\\Answer\\Alphabet_J.bmp";
	blanktextureArr[11] = L"texture\\puzzle_PM\\Answer\\Alphabet_K.bmp";
	blanktextureArr[12] = L"texture\\puzzle_PM\\Answer\\Alphabet_L.bmp";
	blanktextureArr[13] = L"texture\\puzzle_PM\\Answer\\Alphabet_M.bmp";
	blanktextureArr[14] = L"texture\\puzzle_PM\\Answer\\Alphabet_N.bmp";
	blanktextureArr[15] = L"texture\\puzzle_PM\\Answer\\Alphabet_O.bmp";
	blanktextureArr[16] = L"texture\\puzzle_PM\\Answer\\Alphabet_P.bmp";
	blanktextureArr[17] = L"texture\\puzzle_PM\\Answer\\Alphabet_Q.bmp";
	blanktextureArr[18] = L"texture\\puzzle_PM\\Answer\\Alphabet_R.bmp";
	blanktextureArr[19] = L"texture\\puzzle_PM\\Answer\\Alphabet_S.bmp";
	blanktextureArr[20] = L"texture\\puzzle_PM\\Answer\\Alphabet_T.bmp";
	blanktextureArr[21] = L"texture\\puzzle_PM\\Answer\\Alphabet_U.bmp";
	blanktextureArr[22] = L"texture\\puzzle_PM\\Answer\\Alphabet_V.bmp";
	blanktextureArr[23] = L"texture\\puzzle_PM\\Answer\\Alphabet_W.bmp";
	blanktextureArr[24] = L"texture\\puzzle_PM\\Answer\\Alphabet_X.bmp";
	blanktextureArr[25] = L"texture\\puzzle_PM\\Answer\\Alphabet_Y.bmp";
	blanktextureArr[26] = L"texture\\puzzle_PM\\Answer\\Alphabet_Z.bmp";

    // CODE
    m_answer[0] = 3;
    m_answer[1] = 15;
    m_answer[2] = 4;
    m_answer[3] = 5;
    // HAND
    m_answer[4] = 8;
    m_answer[5] = 1;
    m_answer[6] = 14;
    m_answer[7] = 4;

    initCenterPos();
    m_inputCount = 0;
    m_isCorrect = false;
    for (int i = 0; i < 8; i++) m_input[i] = 100;



	// 빈칸

	vAlphabetOffest.x = /*26*/0.f;
	vAlphabetOffest.y = 0.f;

    for (int i = 0; i < 8; i++) blankPos[i].y = 1080.f-313.f;



	blankPos[0].x = 350.f + vAlphabetOffest.x;
	blankPos[1].x = 476.f + vAlphabetOffest.x;
	blankPos[2].x = 601.f + vAlphabetOffest.x;
	blankPos[3].x = 727.f + vAlphabetOffest.x;
	blankPos[4].x = 902.f + vAlphabetOffest.x;
	blankPos[5].x = 1027.f + vAlphabetOffest.x;
	blankPos[6].x = 1154.f + vAlphabetOffest.x;
	blankPos[7].x = 1279.f + vAlphabetOffest.x;


}

CPuzzle_ABC::~CPuzzle_ABC()
{
    GameManager::GetInst()->SetMovable(true);

}

void CPuzzle_ABC::initCenterPos()
{
    // 디스플레이 크기 정보
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2 + vPos.x;
    vPos.y = ScreenSize.y / 2 + vPos.y;
    SetPos(vPos);
}

void CPuzzle_ABC::update()
{
    if (KEY_TAP(KEY::ESC))
    {
        GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM, true);
        m_buttonPushed = 0;

        m_buttonAlphabet = 0;
        m_buttonCount = 0;
        DeleteObject(this);
    }

    if (KEY_NONE(KEY::LBTN))
    {
        m_buttonPushed = 0;
    }

    if (KEY_TAP(KEY::LBTN))
    {
        
        m_vMousePos = CKeyMgr::GetInst()->GetMousePos();

        // 아래 반복문의 i 는 버튼의 넘버
        for (int i = 0; i < 26; ++i)
        {
            if (m_vMousePos.x < m_button[i].right &&
                m_vMousePos.x > m_button[i].left &&
                m_vMousePos.y < m_button[i].bottom &&
                m_vMousePos.y > m_button[i].top)
            {
                SoundManager::GetInst()->playSFX(SFX::alphabet_click);

                m_buttonPushed = i + 1; // 만약 0 번이 눌렸으면 m_buttonPushed 는 1
                

                // 입력은 대충 5개(실제 정답 개수)만큼만 받는다
                if (m_inputCount < 8)
                {
                    // i (버튼 넘버) 를 답안지에 기록
                    m_input[m_inputCount] = i + 1;
                    m_inputCount++;

                    m_buttonAlphabet = i + 1;
                    m_buttonCount++;
                }
            }
        }
    }

    if (KEY_TAP(KEY::SPACE))
    {
        if (m_inputCount == 8)
        {
            for (int i = 0; i < m_inputCount; ++i)
            {
                if (m_answer[i] != m_input[i])
                {
                    m_isCorrect = false;
                    m_buttonPushed = 0;
                    m_buttonAlphabet = 0;
                    m_buttonCount = 0;
                    break;
                }
                else
                {
                    m_isCorrect = true;
                }
            }

            // 정답인 경우
            if (m_isCorrect)
            {
                GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_PM, false);
                GameManager::GetInst()->SetIsCollected(CLEAR_OBJECT::PM, true);

				SoundManager::GetInst()->playSFX(SFX::head_open);

                // 핵심 퍼즐이므로 정수 획득 예정 ??뭐라는거야;;;
                CTextBox* pTextBox = new CTextBox;
                LPCWSTR m_txt[2] = { L"논리의 정수를 획득하였다.", L"아직 온기가 남아있어. 누구의 손인지 알 것 같아."};
                PORTAIT_TYPE m_ports[2] = { PORTAIT_TYPE::PM_OBJ,PORTAIT_TYPE::PLAYER_PANIC };
                pTextBox->SetTXTInfo(m_txt, 2);
                pTextBox->SetPortrait(m_ports, 2);
                CreateObject(pTextBox, GROUP_TYPE::TEXT);
                DeleteObject(this);
            }
			else
			{
				SoundManager::GetInst()->playSFX(SFX::warning_beep);

			}
        }
        else
        {
            m_isCorrect = false;
            m_buttonPushed = 0;
            m_buttonAlphabet = 0;
            m_buttonCount = 0;
			SoundManager::GetInst()->playSFX(SFX::warning_beep);

        }

        m_inputCount = 0;
        for (int i = 0; i < 8; i++)
        {
            m_input[i] = 100;
        }
    }
}

void CPuzzle_ABC::render(HDC _dc)
{
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2;
    vPos.y = ScreenSize.y / 2;
    SetPos(vPos);

	Vec2 vPos1 = GetPos();
	vPos1.x = ScreenSize.x / 2;
	vPos1.y = ScreenSize.y / 2;
	//SetPos(vPos);

    m_pTex[m_buttonPushed] = CResMgr::GetInst()->LoadTexture(texKeyArr[m_buttonPushed], textureArr[m_buttonPushed]);

    // 텍스처 크기 정보
    int iWidth = (int)m_pTex[m_buttonPushed]->Width();
    int iHeight = (int)m_pTex[m_buttonPushed]->Height();

	// 디스플레이 중앙에 텍스처 그리기
	BitBlt(_dc,
		vPos1.x - iWidth / 2,
		vPos1.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex[m_buttonPushed]->GetDC(),
		0, 0,
		SRCCOPY);

	/*TransparentBlt(_dc,
		vPos1.x - iWidth / 2,
		vPos1.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex[m_buttonPushed]->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(106, 255, 0));*/

    Vec2 vResolution = CCore::GetInst()->GetResolution();

    Vec2 _Origin;
    _Origin.x = ScreenSize.x / 2 - m_pTex[m_buttonPushed]->Width() / 2 /*+ 760.f*/;
    _Origin.y = ScreenSize.y / 2 + m_pTex[m_buttonPushed]->Height() / 2/*(ScreenSize.y - vResolution.y)/2*/ /*- 180.f*/;

    // screensize - (screen - resolution)/2

    // 좌 상 우 하
    m_button[0] = { (long)_Origin.x + 550, (long)_Origin.y - 612, (long)_Origin.x + 634, (long)_Origin.y - 528 };//A
    m_button[1] = { (long)_Origin.x + 638, (long)_Origin.y - 612, (long)_Origin.x + 722, (long)_Origin.y - 528 };//B
    m_button[2] = { (long)_Origin.x + 726, (long)_Origin.y - 612, (long)_Origin.x + 810, (long)_Origin.y - 528 };//C
    m_button[3] = { (long)_Origin.x + 814, (long)_Origin.y - 612, (long)_Origin.x + 898, (long)_Origin.y - 528 };//D
    m_button[4] = { (long)_Origin.x + 902, (long)_Origin.y - 612, (long)_Origin.x + 986, (long)_Origin.y - 528 };//E
    m_button[5] = { (long)_Origin.x + 990, (long)_Origin.y - 612, (long)_Origin.x + 1074, (long)_Origin.y - 528 };//F
    m_button[6] = { (long)_Origin.x + 1078, (long)_Origin.y - 612, (long)_Origin.x + 1162, (long)_Origin.y - 528 };//G

    m_button[7] = { (long)_Origin.x + 550, (long)_Origin.y - 524, (long)_Origin.x + 634, (long)_Origin.y - 440 };//H
    m_button[8] = { (long)_Origin.x + 638, (long)_Origin.y - 524, (long)_Origin.x + 722, (long)_Origin.y - 440 };//I
    m_button[9] = { (long)_Origin.x + 726, (long)_Origin.y - 524, (long)_Origin.x + 810, (long)_Origin.y - 440 };//J
    m_button[10] = { (long)_Origin.x + 814, (long)_Origin.y - 524, (long)_Origin.x + 898, (long)_Origin.y - 440 };//K
    m_button[11] = { (long)_Origin.x + 902, (long)_Origin.y - 524, (long)_Origin.x + 986, (long)_Origin.y - 440 };//L
    m_button[12] = { (long)_Origin.x + 990, (long)_Origin.y - 524, (long)_Origin.x + 1074, (long)_Origin.y - 440 };//M
    m_button[13] = { (long)_Origin.x + 1078, (long)_Origin.y - 524, (long)_Origin.x + 1162, (long)_Origin.y - 440 };//N

    m_button[14] = { (long)_Origin.x + 550, (long)_Origin.y - 438, (long)_Origin.x + 634, (long)_Origin.y - 354 };//O
    m_button[15] = { (long)_Origin.x + 638, (long)_Origin.y - 438, (long)_Origin.x + 722, (long)_Origin.y - 354 };//P
    m_button[16] = { (long)_Origin.x + 726, (long)_Origin.y - 438, (long)_Origin.x + 810, (long)_Origin.y - 354 };//Q
    m_button[17] = { (long)_Origin.x + 814, (long)_Origin.y - 438, (long)_Origin.x + 898, (long)_Origin.y - 354 };//R
    m_button[18] = { (long)_Origin.x + 902, (long)_Origin.y - 438, (long)_Origin.x + 986, (long)_Origin.y - 354 };//S
    m_button[19] = { (long)_Origin.x + 990, (long)_Origin.y - 438, (long)_Origin.x + 1074, (long)_Origin.y - 354 };//T
    m_button[20] = { (long)_Origin.x + 1078, (long)_Origin.y - 438, (long)_Origin.x + 1162, (long)_Origin.y - 354 };//U

    m_button[21] = { (long)_Origin.x + 550, (long)_Origin.y - 352, (long)_Origin.x + 634, (long)_Origin.y - 268 };//V
    m_button[22] = { (long)_Origin.x + 638, (long)_Origin.y - 352, (long)_Origin.x + 722, (long)_Origin.y - 268 };//W
    m_button[23] = { (long)_Origin.x + 726, (long)_Origin.y - 352, (long)_Origin.x + 810, (long)_Origin.y - 268 };//X
    m_button[24] = { (long)_Origin.x + 814, (long)_Origin.y - 352, (long)_Origin.x + 898, (long)_Origin.y - 268 };//Y
    m_button[25] = { (long)_Origin.x + 902, (long)_Origin.y - 352, (long)_Origin.x + 986, (long)_Origin.y - 268 };//Z


	// 확인용 사각형 렌더
	/*for (int i = 0; i < 26; ++i)
	{
		Rectangle(_dc, m_button[i].left, m_button[i].top, m_button[i].right, m_button[i].bottom);

	}*/


    if (m_buttonCount == 0)
    {
		m_pBlankTex1 = nullptr;
		m_pBlankTex2 = nullptr;
		m_pBlankTex3 = nullptr;
		m_pBlankTex4 = nullptr;
		m_pBlankTex5 = nullptr;
		m_pBlankTex6 = nullptr;
		m_pBlankTex7 = nullptr;
		m_pBlankTex8 = nullptr;
    }
    if (m_buttonCount == 1)
    {
        m_pBlankTex1 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
    }
	if (m_buttonCount == 2)
	{
        m_pBlankTex2 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 3)
	{
		m_pBlankTex3 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 4)
	{
		m_pBlankTex4 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 5)
	{
		m_pBlankTex5 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 6)
	{
		m_pBlankTex6 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 7)
	{
		m_pBlankTex7 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}
	if (m_buttonCount == 8)
	{
		m_pBlankTex8 = CResMgr::GetInst()->LoadTexture(blankKeyArr[m_buttonAlphabet], blanktextureArr[m_buttonAlphabet]);
	}

	//Vec2 _Origin;
	//_Origin.x = ScreenSize.x / 2 - m_pTex[m_buttonPushed]->Width() / 2 /*+ 760.f*/;
	//_Origin.y = ScreenSize.y / 2 + m_pTex[m_buttonPushed]->Height() / 2/*(ScreenSize.y - vResolution.y)/2*/ /*- 180.f*/;

    if (m_pBlankTex1 !=nullptr)
    {
		int iWidth2 = (int)m_pBlankTex1->Width();
		int iHeight2 = (int)m_pBlankTex1->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[0].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
			m_pBlankTex1->GetDC(),
			0, 0,
			SRCCOPY);*/

		TransparentBlt(_dc,
			_Origin.x +blankPos[0].x,
			_Origin.y - blankPos[0].y,
            iWidth2, iHeight2,
            m_pBlankTex1->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
    }

	if (m_pBlankTex2 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex2->Width();
		int iHeight2 = (int)m_pBlankTex2->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[1].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
			m_pBlankTex2->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[1].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[1].y,
			iWidth2, iHeight2,
            m_pBlankTex2->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/
		TransparentBlt(_dc,
			_Origin.x + blankPos[1].x,
			_Origin.y - blankPos[1].y,
			iWidth2, iHeight2,
			m_pBlankTex2->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    if (m_pBlankTex3 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex3->Width();
		int iHeight2 = (int)m_pBlankTex3->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[2].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
			m_pBlankTex3->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[2].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[2].y,
			iWidth2, iHeight2,
            m_pBlankTex3->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/
		TransparentBlt(_dc,
			_Origin.x + blankPos[2].x,
			_Origin.y - blankPos[2].y,
			iWidth2, iHeight2,
			m_pBlankTex3->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    if (m_pBlankTex4 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex4->Width();
		int iHeight2 = (int)m_pBlankTex4->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[3].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
			m_pBlankTex4->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[3].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[3].y,
			iWidth2, iHeight2,
			m_pBlankTex4->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/
		TransparentBlt(_dc,
			_Origin.x + blankPos[3].x,
			_Origin.y - blankPos[3].y,
			iWidth2, iHeight2,
			m_pBlankTex4->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));

	}
    if (m_pBlankTex5 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex5->Width();
		int iHeight2 = (int)m_pBlankTex5->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[4].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
            m_pBlankTex5->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[4].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[4].y,
			iWidth2, iHeight2,
			m_pBlankTex5->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/
		TransparentBlt(_dc,
			_Origin.x + blankPos[4].x,
			_Origin.y - blankPos[4].y,
			iWidth2, iHeight2,
			m_pBlankTex5->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    if (m_pBlankTex6 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex6->Width();
		int iHeight2 = (int)m_pBlankTex6->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[5].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
            m_pBlankTex6->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[5].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[5].y,
			iWidth2, iHeight2,
			m_pBlankTex6->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/

		TransparentBlt(_dc,
			_Origin.x + blankPos[5].x,
			_Origin.y - blankPos[5].y,
			iWidth2, iHeight2,
			m_pBlankTex6->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    if (m_pBlankTex7 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex7->Width();
		int iHeight2 = (int)m_pBlankTex7->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[6].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
            m_pBlankTex7->GetDC(),
			0, 0,
			SRCCOPY);*/

		/*TransparentBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[6].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2 - blankPos[6].y,
			iWidth2, iHeight2,
			m_pBlankTex7->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));*/

		TransparentBlt(_dc,
			_Origin.x + blankPos[6].x,
			_Origin.y - blankPos[6].y,
			iWidth2, iHeight2,
			m_pBlankTex7->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    if (m_pBlankTex8 != nullptr)
	{
		int iWidth2 = (int)m_pBlankTex8->Width();
		int iHeight2 = (int)m_pBlankTex8->Height();

		/*BitBlt(_dc,
			vPos.x - vResolution.x / 2 + 500 + blankPos[7].x - iWidth2 / 2,
			vPos.y - iHeight2 / 2,
			iWidth2, iHeight2,
            m_pBlankTex8->GetDC(),
			0, 0,
			SRCCOPY);*/

		//TransparentBlt(_dc,
		//	vPos.x - vResolution.x / 2 + 500 + blankPos[7].x - iWidth2 / 2,
		//	vPos.y - iHeight2 / 2 - blankPos[7].y,
		//	iWidth2, iHeight2,
		//	m_pBlankTex8->GetDC(),
		//	0, 0,
		//	iWidth2, iHeight2,
		//	RGB(106, 255, 0));

		TransparentBlt(_dc,
			_Origin.x + blankPos[7].x,
			_Origin.y - blankPos[7].y,
			iWidth2, iHeight2,
			m_pBlankTex8->GetDC(),
			0, 0,
			iWidth2, iHeight2,
			RGB(106, 255, 0));
	}
    


	

	
}