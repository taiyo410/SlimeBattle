#pragma once
#include "RuleBase.h"
class SceneGame;
class RuleHp :
    public RuleBase
{
public:
    //定数
    //HPゲージの視点座標
    static constexpr int HP_GAUGE_START_X = Application::SCREEN_SIZE_X - 275;

    void Init(SceneGame* parent) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;


private:
  

};

