#include "pch.h"
#include "CPuzzle_DoorLock.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTextBox.h"
#include "CKeyMgr.h"
#include "SoundManager.h"
#include "GameManager.h"

#include "CTimeMgr.h"

// 이동 제어 안되고 클릭 초기화 안됨;

CPuzzle_DoorLock::CPuzzle_DoorLock()
    :m_answer{0}, m_input{5}
{
    GameManager::GetInst()->SetMovable(false);
    m_buttonPushed = 0;

    texKeyArr[0] = L"DoorLock_Default";
	texKeyArr[1] = L"DoorLock_0";
	texKeyArr[2] = L"DoorLock_1";
	texKeyArr[3] = L"DoorLock_2";
	texKeyArr[4] = L"DoorLock_3";
	texKeyArr[5] = L"DoorLock_4";
	texKeyArr[6] = L"DoorLock_5";
	texKeyArr[7] = L"DoorLock_6";
	texKeyArr[8] = L"DoorLock_7";
	texKeyArr[9] = L"DoorLock_8";
	texKeyArr[10] = L"DoorLock_9";
	texKeyArr[11] = L"DoorLock_OK";
	texKeyArr[12] = L"DoorLock_NO";

    textureArr[0] = L"texture\\puzzle_doorlock\\Door_Lock.bmp";
	textureArr[1] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number0.bmp";
	textureArr[2] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number1.bmp";
	textureArr[3] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number2.bmp";
	textureArr[4] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number3.bmp";
	textureArr[5] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number4.bmp";
	textureArr[6] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number5.bmp";
	textureArr[7] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number6.bmp";
	textureArr[8] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number7.bmp";
	textureArr[9] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number8.bmp";
	textureArr[10] = L"texture\\puzzle_doorlock\\button_On\\door_lock_number9.bmp";
	textureArr[11] = L"texture\\puzzle_doorlock\\door_lock_OK.bmp";
	textureArr[12] = L"texture\\puzzle_doorlock\\door_lock_NO.bmp";

    //m_pTex = CResMgr::GetInst()->LoadTexture(L"puzzle_doorlock", L"texture\\black_alpha channel.bmp");


    m_answer[0] = 7;
    m_answer[1] = 0;
    m_answer[2] = 0;
    m_answer[3] = 7;
    m_answer[4] = 0;

    m_elapsedTime = 0;
    initCenterPos();
    m_inputCount = 0;
    m_isCorrect = false;
    for (int i = 0; i < 5; i++) m_input[i] = 100;

    //m_answer[] = {0,0,0,0,0};
    // 생성자에서 vPos 중앙에 제대로 안옴;;
    //m_button[0] = { (long)vPos.x - 50,(long)vPos.y - 50,(long)vPos.x + 50,(long)vPos.y + 50 };
    //m_button[1] = { (long)vPos.x + 50,(long)vPos.y - 50,(long)vPos.x + 150,(long)vPos.y + 50 };
}

CPuzzle_DoorLock::~CPuzzle_DoorLock()
{
    GameManager::GetInst()->SetMovable(true);
}


void CPuzzle_DoorLock::initCenterPos()
{
    // 디스플레이 크기 정보
    Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

    // vPos를 디스플레이 기준 중앙으로 설정
    Vec2 vPos = GetPos();
    vPos.x = ScreenSize.x / 2 + vPos.x;
    vPos.y = ScreenSize.y / 2 + vPos.y;
    SetPos(vPos);

}

void CPuzzle_DoorLock::update()
{
    if (KEY_TAP(KEY::ESC))
    {
        GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);
        m_buttonPushed = 0;
        DeleteObject(this);
    }

    if (KEY_NONE(KEY::LBTN))
    {
        m_buttonPushed = 0;
    }

    if (KEY_TAP(KEY::LBTN))
    {
       
        m_vMousePos = CKeyMgr::GetInst()->GetMousePos();

        if (m_vMousePos.x < m_Checkbutton.right &&
            m_vMousePos.x > m_Checkbutton.left &&
            m_vMousePos.y < m_Checkbutton.bottom &&
            m_vMousePos.y > m_Checkbutton.top)
        {
			m_buttonPushed = 11; // 만약 0 번이 눌렸으면 m_buttonPushed 는 1이어야함; 1씩 커야함

			if (m_inputCount == 5)
			{
				for (UINT i = 0; i < m_inputCount; ++i)
				{
					if (m_answer[i] != m_input[i])
					{
						m_isCorrect = false;
						m_buttonPushed = 0;
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
					GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, false);
					GameManager::GetInst()->SetSceneAcsess(SCENE_TYPE::LOBBY, true);

					SoundManager::GetInst()->playSFX(SFX::frame_success);
					SoundManager::GetInst()->playSFX(SFX::door_open);

					CTextBox* pTextBox = new CTextBox;
					LPCWSTR m_txt[1] = { L"문이 열렸다!" };
					PORTAIT_TYPE m_ports[1] = { PORTAIT_TYPE::PLAYER_BASIC };
					pTextBox->SetTXTInfo(m_txt, 1);
					pTextBox->SetPortrait(m_ports, 1);
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
				SoundManager::GetInst()->playSFX(SFX::warning_beep);
				m_isCorrect = false;
				//m_buttonPushed = 0;
			}

			m_inputCount = 0;
			for (int i = 0; i < 5; i++)
			{
				m_input[i] = 100;
			}
        }

        if (m_vMousePos.x < m_Cancelbutton.right &&
            m_vMousePos.x > m_Cancelbutton.left &&
            m_vMousePos.y < m_Cancelbutton.bottom &&
            m_vMousePos.y > m_Cancelbutton.top)
        {
			m_buttonPushed = 12; // 만약 0 번이 눌렸으면 m_buttonPushed 는 1이어야함; 1씩 커야함

			GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, true);
			DeleteObject(this);
        }

        // 아래 반복문의 i 는 버튼의 넘버
        for (int i = 0; i < 10; ++i)
        {
            if (m_vMousePos.x < m_button[i].right &&
                m_vMousePos.x > m_button[i].left &&
                m_vMousePos.y < m_button[i].bottom &&
                m_vMousePos.y > m_button[i].top)
            {
                SoundManager::GetInst()->playSFX(SFX::password_click);
                m_buttonPushed = i + 1; // 만약 0 번이 눌렸으면 m_buttonPushed 는 1이어야함; 1씩 커야함

                // 입력은 대충 5개(실제 정답 개수)만큼만 받는다
                if (m_inputCount < 5)
                {
                    // i (버튼 넘버) 를 답안지에 기록
                    m_input[m_inputCount] = i;
                    m_inputCount++;
                }        
            }
        }
    }

    if (KEY_TAP(KEY::SPACE))
    {
        if (m_inputCount == 5)
        {
            for (UINT i = 0; i < m_inputCount; ++i)
            {
                if (m_answer[i] != m_input[i])
                {
                    m_isCorrect = false;
                    m_buttonPushed = 0;
                    break;
                }
                else
                {
                    m_isCorrect = true;
                }
            }

            // 정답인 경우
            if(m_isCorrect)
            {
                GameManager::GetInst()->SetInteractionStatus(INTERACTIVE_TYPE::PUZZLE_DOORLOCK, false);
                //GameManager::GetInst()->SetSceneAcsess(SCENE_TYPE::LOBBY, true);
                
                SoundManager::GetInst()->playSFX(SFX::frame_success);

                CTextBox* pTextBox = new CTextBox;
                LPCWSTR m_txt[1] = { L"문이 열렸다!" };
                PORTAIT_TYPE m_ports[1] = { PORTAIT_TYPE::PLAYER_SURPRISE };
                pTextBox->SetTXTInfo(m_txt, 1);
                pTextBox->SetPortrait(m_ports, 1);
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
            SoundManager::GetInst()->playSFX(SFX::warning_beep);
            m_isCorrect = false;
            m_buttonPushed = 0;
        }

        m_inputCount = 0;
        for (int i=0; i< 5; i++)
        {
            m_input[i] = 100;
        }
    }
}

void CPuzzle_DoorLock::render(HDC _dc)
{
	Vec2 ScreenSize = CCore::GetInst()->GetScreenSize();

	// vPos를 디스플레이 기준 중앙으로 설정
	Vec2 vPos = GetPos();
	vPos.x = ScreenSize.x / 2;
	vPos.y = ScreenSize.y / 2;
	SetPos(vPos);


    long x_offset = 32;
	long y_offset = 40;
    
    // 빈공간 (터치 불가 공간)
    long x_space = 9;
	long y_space = 5;

    vPos.y -= 92;
    vPos.x += 1;
    
    m_button[1] = { (long)vPos.x - x_offset * 3 - x_space, (long)vPos.y , (long)vPos.x - x_offset - x_space, (long)vPos.y + y_offset };
    m_button[2] = { (long)vPos.x - x_offset, (long)vPos.y ,(long)vPos.x + x_offset, (long)vPos.y + y_offset };
    m_button[3] = { (long)vPos.x + x_offset + x_space, (long)vPos.y , (long)vPos.x + x_offset * 3 + x_space, (long)vPos.y + y_offset };


	m_button[4] = { (long)vPos.x - x_offset * 3 - x_space,(long)vPos.y + y_offset + y_space ,(long)vPos.x - x_offset - x_space   ,(long)vPos.y + y_offset * 2 + y_space };
	m_button[5] = { (long)vPos.x - x_offset     ,(long)vPos.y + y_offset + y_space ,(long)vPos.x + x_offset      ,(long)vPos.y + y_offset * 2 + y_space };
	m_button[6] = { (long)vPos.x + x_offset  + x_space   ,(long)vPos.y + y_offset + y_space,(long)vPos.x + x_offset * 3 + x_space ,(long)vPos.y + y_offset * 2 + y_space };
	

    m_button[7] = { (long)vPos.x - x_offset * 3- x_space,(long)vPos.y + y_offset * 2 + y_space*2 ,(long)vPos.x - x_offset - x_space   ,(long)vPos.y + y_offset * 3 + y_space*2 };
	m_button[8] = { (long)vPos.x - x_offset    , (long)vPos.y + y_offset * 2 + y_space*2 ,(long)vPos.x + x_offset    ,(long)vPos.y + y_offset * 3 + y_space*2 };
	m_button[9] = { (long)vPos.x + x_offset + x_space   ,(long)vPos.y + y_offset * 2 + y_space*2,(long)vPos.x + x_offset * 3+ x_space,(long)vPos.y + y_offset * 3 + y_space*2 };

    m_button[0] = { (long)vPos.x - x_offset    ,(long)vPos.y + y_offset * 3 + y_space*3,(long)vPos.x + x_offset    ,(long)vPos.y + y_offset * 4 + y_space*3 };


    m_Checkbutton = { (long)vPos.x + x_offset + x_space     ,(long)vPos.y + y_offset * 3 + y_space * 3,(long)vPos.x + x_offset * 3 + x_space,(long)vPos.y + y_offset * 4 + y_space * 3 };
    m_Cancelbutton = { (long)vPos.x - x_offset * 3 - x_space,(long)vPos.y + y_offset * 3 + y_space * 3,(long)vPos.x - x_offset - x_space, (long)vPos.y + y_offset * 4 + y_space * 3 };


	



    Vec2 vPos1 = GetPos();
    vPos1.x = ScreenSize.x / 2;
    vPos1.y = ScreenSize.y / 2;
    SetPos(vPos1);

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

	//Rectangle(_dc, m_Checkbutton.left, m_Checkbutton.top, m_Checkbutton.right, m_Checkbutton.bottom);
	//Rectangle(_dc, m_Cancelbutton.left, m_Cancelbutton.top, m_Cancelbutton.right, m_Cancelbutton.bottom);

    // 확인용 사각형 렌더
    /*Rectangle(_dc, m_button[0].left, m_button[0].top, m_button[0].right, m_button[0].bottom);
    Rectangle(_dc, m_button[1].left, m_button[1].top, m_button[1].right, m_button[1].bottom);
	Rectangle(_dc, m_button[2].left, m_button[2].top, m_button[2].right, m_button[2].bottom);
	Rectangle(_dc, m_button[3].left, m_button[3].top, m_button[3].right, m_button[3].bottom);
	Rectangle(_dc, m_button[4].left, m_button[4].top, m_button[4].right, m_button[4].bottom);
	Rectangle(_dc, m_button[5].left, m_button[5].top, m_button[5].right, m_button[5].bottom);
	Rectangle(_dc, m_button[6].left, m_button[6].top, m_button[6].right, m_button[6].bottom);
	Rectangle(_dc, m_button[7].left, m_button[7].top, m_button[7].right, m_button[7].bottom);
	Rectangle(_dc, m_button[8].left, m_button[8].top, m_button[8].right, m_button[8].bottom);
	Rectangle(_dc, m_button[9].left, m_button[9].top, m_button[9].right, m_button[9].bottom);*/


}
