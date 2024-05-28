#pragma once
#include "CScene.h"

class CBackground;
class CPlayer;
class AI_TextObj;

class CScene_MoniterAI :
    public CScene
{

private:
    CBackground* m_pBackground;
    CPlayer* m_player;
    UINT m_AI_SceneIndex;
    UINT m_textNumber;
    UINT m_textOverIndex;
    UINT m_fontSize;

    bool m_IsSelectVisible;
    bool m_IsEnter;
    bool m_IsNextScene;
    float m_Timer;

    const wchar_t* SceneArr[10] = {};
    const wchar_t* TextureArr[10] = {};

    AI_TextObj* m_FlickerObj;
    AI_TextObj* m_SelectTextObj;

    vector<LPCWSTR> AI_StringVec = {};
    vector<LPCWSTR> AI_SelectStringVec = {};
    vector<AI_TextObj*> AI_TextObjVec = {};

public:
    CScene_MoniterAI();
    ~CScene_MoniterAI();

public:
    virtual void Enter();
    virtual void Exit();
    virtual void SceneUpdate();
    virtual void SceneReset();

public:
    void Scene_0();
    void Scene_1();
    void Scene_2();
    void Scene_3();


public:
    void PrintDialogue(UINT _index);

public:
    void Enter_Scene();
    void Next_Scene();
};