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
    // AI_TextObjVec �� �ִ� �޸� �������ֱ�.
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

    // �����̴� Ŀ�� ����
    m_FlickerObj = new AI_TextObj;
    m_FlickerObj->SetTextData(L"|", m_fontSize, TEXT_TYPE::FLICKER);
    AddObject(m_FlickerObj, GROUP_TYPE::TEXT);


    // ��ȭ ������ ����
    m_SelectTextObj = new AI_TextObj;
    m_SelectTextObj->SetTextData(L"", m_fontSize * 2, TEXT_TYPE::SELECT);
    m_SelectTextObj->SetSelctText(L"�� ����? ���ϴ� ���̾�?", L"����? �����̶��?");
    AddObject(m_SelectTextObj, GROUP_TYPE::TEXT);

    AI_SelectStringVec.push_back(L"�ּ���");
    AI_SelectStringVec.push_back(L"������");

    AI_SelectStringVec.push_back(L"�� ����. ���ϴ� ���̾�.");
    AI_SelectStringVec.push_back(L"����? �����̶��?");

    AI_SelectStringVec.push_back(L"������ ����? �峭�ϳ�?");
    AI_SelectStringVec.push_back(L"���� ������ �� ���� �� ����.");


    AI_StringVec.push_back(L"<HATER> �ȳ�, ȯ����.");
    AI_StringVec.push_back(L"<HATER> �� �̸��� ����?");

    AI_StringVec.push_back(L">>> �ּ���"); // �̸� �Է��ϱ�

    AI_StringVec.push_back(L"<HATER> ���� �� ������ �����ϴ� [HATER] ��� ��.");
    AI_StringVec.push_back(L"<HATER> ���ݺ��� �� �� ��� ��.");
    AI_StringVec.push_back(L"<HATER> WASD�� SPACE BAR �� ������ �˾Ƽ� �� ��.");
    AI_StringVec.push_back(L"<HATER> �׷��� ������ �ſ� ������ ���� ������ �ž�.");

    AI_StringVec.push_back(L">>> ��Ҹ������� �Ӹ�"); // ������

    AI_StringVec.push_back(L"<HATER> �� ������ ��������...");
    AI_StringVec.push_back(L"<HATER> �� ������ ������ ������ ���Ƿ� ������ ��.");
    AI_StringVec.push_back(L"<HATER> �� ������ ������ ���� ���ŵ�.");

    AI_StringVec.push_back(L">>> �ּ���");   // ������

    AI_StringVec.push_back(L"<HATER> ������ ������ ��� ����İ�?");
    AI_StringVec.push_back(L"<HATER> �װ� �ʰ� ã�ƾ���.");


    // AI_TextObjVec���� �����ϱ� ���� Ǫ�� ���ֱ�.
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
    case 0:   Scene_0();   break; // 1. å�� �������ִ� �� , 2.å�� ���� ������ ��ٸ� ����
    case 1:   Scene_1();   break; // ����Ϳ� ��ȭ �� , ������ �� �̵�
    case 2:   Scene_2();  break;
    case 3:   Scene_3();  break;
    }
}

void CScene_MoniterAI::PrintDialogue(UINT _index)
{
    Vec2 resolution = CCore::GetInst()->GetResolution();


    // ������� ����ؾ� �ϴ� ��� Set ���ֱ�
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

    // �����̴� Ŀ�� �ֱ�
    m_FlickerObj->SetVisible(true);
    m_FlickerObj->SetTextPos(Vec2(resolution.x / 2 - 430, (resolution.y / 2) + 300));

    // �� ����
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    if (KEY_TAP(KEY::A))
        Next_Scene();

    // TODO  0.5f -> 1.5f 
    if (m_Timer > 0.5f && m_IsSelectVisible == false && IsEndScene == false)
    {
        // �����̽� ������ ���� ���
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

                // ȭ�� ������ �Ѿ�� ��� ���ֱ�
                if (m_textNumber >= m_textOverIndex)
                {
                    AI_TextObjVec[checkIndex]->SetVisible(false);
                    checkIndex++;
                }

                // ��� ���
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

            // ������  ������ ��ȭ�� ���� ����. 
          
            m_SelectTextObj->SetSelctText(AI_SelectStringVec[SelectIndex], AI_SelectStringVec[SelectIndex + 1]);
            AI_TextObjVec[m_textNumber]->SetTextData(m_SelectTextObj->GetText(), m_fontSize);

            m_SelectTextObj->SetVisible(true);


            // �̸� ������ ��ġ�� �ʹ� ����ؼ� ����.
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

                // ȭ�� ������ �Ѿ�� ��� ���ֱ�
                if (m_textNumber >= m_textOverIndex)
                {
                    AI_TextObjVec[checkIndex]->SetVisible(false);
                    checkIndex++;
                }

                // ��� ���
                PrintDialogue(checkIndex);
                m_textNumber++;
                m_Timer = 0.f;

                SelectIndex += 2;
            }
        }
    }

    //�� �̵�
    if (KEY_TAP(KEY::SPACE) && m_Timer > 0.5f && IsEndScene)
    {
        m_FlickerObj->SetVisible(false);
        Next_Scene();
    }
}

void CScene_MoniterAI::Scene_1()
{
    // �� ����
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    //�� �̵�
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
    // �� ����
    if (!m_IsEnter)   Enter_Scene();
    m_Timer += fDT;


    // �� �̵�
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