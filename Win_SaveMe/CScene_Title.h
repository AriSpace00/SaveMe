#pragma once
#include "CScene.h"

class CObject;
class CUI_Title;

class CScene_Title :
    public CScene
{
public:
    CScene_Title();
    ~CScene_Title();
    virtual void Enter();
    virtual void Exit();
    void FirstEnter();
    void SecondEnter();

private:
    CUI_Title* ptitle_UI;

};
