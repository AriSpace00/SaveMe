#include "pch.h"
#include "CScene_MoniterAI.h"
#include "CTexture.h"
#include "CBackground.h"
#include "CResMgr.h"
#include "CPlayer.h"
#include "GameManager.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "TextManager.h"
#include "AI_TextObj.h"
#include "CCore.h"
#include "CSceneMgr.h"
#include "SoundManager.h"

static UINT SelectIndex = 0;
static UINT checkIndex = 0;
static bool IsEndScene = false;

CScene_MoniterAI::CScene_MoniterAI()
    : m_pBackground(nullptr)
    , m_player(nullptr)
    , m_AI_SceneIndex(0)
    , m_IsNextScene(false)
    , m_Timer(0)
    , SceneArr{}
    , TextureArr{}
    , m_IsEnter(false)
    , m_textNumber(0)
    , m_textOverIndex(0)
    , m_FlickerObj(nullptr)
    , m_SelectTextObj(nullptr)
    , m_fontSize(30)
    , m_IsSelectVisible(false)
{
    int a = 0;
}

CScene_MoniterAI::~CScene_MoniterAI()
{
    // ToDo
    // AI_TextObjVec 에 있는 메모리 해제해주기.
}

void CScene_MoniterAI::SceneReset()
{
    for (UINT i = 0; i < m_AI_SceneIndex; i++)
    {
        AI_TextObjVec[i]->SetVisible(false);
    }

    m_AI_SceneIndex = 0;
    m_textNumber = 0;
    m_Timer = 0;

    SelectIndex = 0;
    checkIndex = 0;
    IsEndScene = false;
    m_IsSelectVisible = false;
    m_IsNextScene = false;

}
void CScene_MoniterAI::Enter()
{

    // 깜빡이는 커서 제작
    m_FlickerObj = new AI_TextObj;
    m_FlickerObj->SetTextData(L"|", m_fontSize, TEXT_TYPE::FLICKER);
    AddObject(m_FlickerObj, GROUP_TYPE::TEXT);


    // 대화 선택지 제작
    m_SelectTextObj = new AI_TextObj;
    m_SelectTextObj->SetTextData(L"", m_fontSize * 2, TEXT_TYPE::SELECT);
    m_SelectTextObj->SetSelctText(L"너 뭐야? 뭐하는 놈이야?", L"게임? 게임이라고?");
    AddObject(m_SelectTextObj, GROUP_TYPE::TEXT);

    AI_SelectStringVec.push_back(L"최성웅");
    AI_SelectStringVec.push_back(L"신혜성");

    AI_SelectStringVec.push_back(L"너 뭐야. 뭐하는 놈이야.");
    AI_SelectStringVec.push_back(L"게임? 게임이라고?");

    AI_SelectStringVec.push_back(L"마스터 파일? 장난하냐?");
    AI_SelectStringVec.push_back(L"전선 끊으면 저 세상 갈 놈이.");


    AI_StringVec.push_back(L"<HATER> 안녕, 환영해.");
    AI_StringVec.push_back(L"<HATER> 네 이름이 뭐야?");

    AI_StringVec.push_back(L">>> 최성웅"); // 이름 입력하기

    AI_StringVec.push_back(L"<HATER> 나는 이 게임을 지배하는 [HATER] 라고 해.");
    AI_StringVec.push_back(L"<HATER> 지금부터 내 말 대로 해.");
    AI_StringVec.push_back(L"<HATER> WASD랑 SPACE BAR 를 가지고 알아서 해 봐.");
    AI_StringVec.push_back(L"<HATER> 그렇지 않으면 매우 끔찍한 일이 벌어질 거야.");

    AI_StringVec.push_back(L">>> 헛소리하지마 임마"); // 선택지

    AI_StringVec.push_back(L"<HATER> 이 게임을 끝내려면...");
    AI_StringVec.push_back(L"<HATER> 이 게임의 마스터 파일을 현실로 보내야 해.");
    AI_StringVec.push_back(L"<HATER> 이 게임은 오류가 아주 많거든.");

    AI_StringVec.push_back(L">>> 최성웅");   // 선택지

    AI_StringVec.push_back(L"<HATER> 마스터 파일을 어떻게 만드냐고?");
    AI_StringVec.push_back(L"<HATER> 그건 너가 찾아야지.");


    // AI_TextObjVec에서 관리하기 위해 푸시 해주기.
    for (UINT i = 0; i < AI_StringVec.size(); i++)
    {
        AI_TextObj* Tobj = new AI_TextObj;
        Tobj->SetTextData(AI_StringVec[i], m_fontSize, TEXT_TYPE::NORMAL);
        AI_TextObjVec.push_back(Tobj);
        AddObject(Tobj, GROUP_TYPE::TEXT);
    }

    SceneArr[0] = L"Background_AIMonitor";
    SceneArr[1] = L"Background_RightTex1";
    SceneArr[2] = L"Background_SaveMeTex";

    TextureArr[0] = L"texture\\cut_scene\\AI_monitor.bmp";
    TextureArr[1] = L"texture\\scene_test\\ending_test\\ending_right1.bmp";
    TextureArr[2] = L"texture\\scene_test\\ending_test\\ending_saveme.bmp";

    //Background 
    m_pBackground = new CBackground;
    m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture(SceneArr[0], TextureArr[0]));
    AddObject(m_pBackground, GROUP_TYPE::BACKGROUND);


    m_textOverIndex = 8;
}

void CScene_MoniterAI::Enter_Scene()
{
    m_pBackground->SetTexture(CResMgr::GetInst()->LoadTexture
    (SceneArr[m_AI_SceneIndex], TextureArr[m_AI_SceneIndex]));

    m_IsEnter = true;
}

void CScene_MoniterAI::Next_Scene()
{
    m_textNumber = 0;
    m_IsEnter = false;
    m_AI_SceneIndex++;

    for (auto child : AI_TextObjVec)
    {
        child->SetVisible(false);
    }

    CSceneMgr::GetInst()->changeScene(SCENE_TYPE::ROOM);
}

void CScene_MoniterAI::SceneUpdate()
{
    switch (m_AI_SceneIndex)
    {
    case 0:   Scene_0();   break; // 1. 책상에 엎어져있는 씬 , 2.책상 위에 수많은 正바를 정자
    case 1:   Scene_1();   break; // 모니터와 대화 씬 , 마지막 씬 이동
    case 2:   Scene_2();  break;
    case 3:   Scene_3();  break;
    }
}

void CScene_MoniterAI::PrintDialogue(UINT _index)
{
    Vec2 resolution = CCore::GetInst()->GetResolution();


    // 현재까지 출력해야 하는 대사 Set 해주기
    for (UINT i = _index; i <= m_textNumber; i++)
    {
        UINT fontSize = 50;
        AI_TextObjVec[i]->SetVisible(true);
        AI_TextObjVec[i]->SetTextPos(Vec2(resolution.x / 2 - 430,
            (resolution.y / 2 - 130) + (i - _index) * fontSize));
    }
}

void CScene_MoniterAI::Scene_0()
{

    Vec2 resolution = CCore::GetInst()->GetResolution();

    // 깜빡이는 커서 넣기
    m_FlickerObj->SetVisible(true);
    m_FlickerObj->SetTextPos(Vec2(resolution.x / 2 - 430, (resolution.y / 2) + 300));

    // 씬 입장
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    if (KEY_TAP(KEY::A))
        Next_Scene();

    // TODO  0.5f -> 1.5f 
    if (m_Timer > 0.5f && m_IsSelectVisible == false && IsEndScene == false)
    {
        // 스페이스 누르면 다음 대사
        if (KEY_TAP(KEY::SPACE))
        {
            if (m_textNumber < 13)
            {
                SoundManager::GetInst()->playSFX(SFX::message_tone);
            }

            if (m_IsSelectVisible == false)
            {
                if (m_textNumber >= AI_TextObjVec.size())
                {
                    IsEndScene = true;
                    return;
                }

                // 화면 밖으로 넘어가는 대사 없애기
                if (m_textNumber >= m_textOverIndex)
                {
                    AI_TextObjVec[checkIndex]->SetVisible(false);
                    checkIndex++;
                }

                // 대사 출력
                PrintDialogue(checkIndex);
                m_textNumber++;
                m_Timer = 0.f;

                if (m_textNumber == 2 || m_textNumber == 7 || m_textNumber == 11)
                {
                    m_IsSelectVisible = true;
                }
            }
        }
    }
    else
    {
        if (m_Timer > 0.5f && IsEndScene == false)
        {
            if (m_textNumber >= AI_TextObjVec.size())
            {
                IsEndScene = true;
                return;
            }

            // 지정한  선택지 대화가 보일 차례. 
          
            m_SelectTextObj->SetSelctText(AI_SelectStringVec[SelectIndex], AI_SelectStringVec[SelectIndex + 1]);
            AI_TextObjVec[m_textNumber]->SetTextData(m_SelectTextObj->GetText(), m_fontSize);

            m_SelectTextObj->SetVisible(true);


            // 이름 선택지 위치가 너무 어색해서 고정.
            if (m_textNumber == 2)
                m_SelectTextObj->SetTextPos(Vec2(resolution.x / 2, (resolution.y / 2) + 400));
            else
                m_SelectTextObj->SetTextPos(Vec2(resolution.x / 2 - 300, (resolution.y / 2) + 400));


            if (KEY_TAP(KEY::SPACE))
            {
                if (m_textNumber == 2 && !(m_SelectTextObj->GetIsUpSelect()))
                {
                    SoundManager::GetInst()->playSFX(SFX::warning_beep);
                    m_SelectTextObj->SetTextPos(Vec2(resolution.x / 2, (resolution.y / 2) + 400));
                    return;
                }

                m_SelectTextObj->SetVisible(false);
                m_IsSelectVisible = false;

                // 화면 밖으로 넘어가는 대사 없애기
                if (m_textNumber >= m_textOverIndex)
                {
                    AI_TextObjVec[checkIndex]->SetVisible(false);
                    checkIndex++;
                }

                // 대사 출력
                PrintDialogue(checkIndex);
                m_textNumber++;
                m_Timer = 0.f;

                SelectIndex += 2;
            }
        }
    }

    //씬 이동
    if (KEY_TAP(KEY::SPACE) && m_Timer > 0.5f && IsEndScene)
    {
        m_FlickerObj->SetVisible(false);
        Next_Scene();
    }
}

void CScene_MoniterAI::Scene_1()
{
    // 씬 입장
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    //씬 이동
    if (m_Timer > 2.f)
    {
        if (KEY_TAP(KEY::SPACE))
        {
            Next_Scene();
        }
    }
}

void CScene_MoniterAI::Scene_2()
{
    // 씬 입장
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    // 씬 이동
    if (m_Timer > 2.f)
    {
        if (KEY_TAP(KEY::SPACE))
        {
            Next_Scene();
        }
    }
}

void CScene_MoniterAI::Scene_3()
{

}

void CScene_MoniterAI::Exit()
{

}