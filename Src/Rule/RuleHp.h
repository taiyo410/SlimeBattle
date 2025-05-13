#pragma once
#include "RuleBase.h"
class SceneGame;
class RuleHp :
    public RuleBase
{
public:
    //定数
    //プレイヤー番号
    static constexpr int PLAYER = 0;
    //HPゲージの視点座標
    static constexpr int HP_GAUGE_START_X = Application::SCREEN_SIZE_X - 275;

    // HPゲージの描画に関する定数
    static constexpr int HP_GAUGE_PLAYER1_POS_X = 15;
    static constexpr int HP_GAUGE_PLAYER1_POS_Y = 15;
    static constexpr int HP_GAUGE_HEIGHT = 25;
    static constexpr int HP_GAUGE_HEIGHT_Y = HP_GAUGE_PLAYER1_POS_Y+ HP_GAUGE_HEIGHT;
    static constexpr int HP_GAUGE_WIDTH = 260;
    static constexpr int HP_GAUGE_WIDTH_X = HP_GAUGE_PLAYER1_POS_X+ HP_GAUGE_WIDTH;
    static constexpr int HP_GAUGE_INNER_OFFSET = 1;

    //ゲージ内側
    static constexpr int HP_IN_GAUGE_X = HP_GAUGE_WIDTH_X - HP_GAUGE_INNER_OFFSET;
    static constexpr int HP_IN_GAUGE_Y = HP_GAUGE_PLAYER1_POS_Y + HP_GAUGE_INNER_OFFSET;



    static constexpr unsigned int HP_GAUGE_BG_COLOR = 0x000000;
    static constexpr unsigned int HP_GAUGE_COLOR = 0x2ce70b;

    // 敵HPゲージの描画に関する定数
    static constexpr int HP_GAUGE_ENEMY_POS_X = 15;
    static constexpr int HP_GAUGE_ENEMY_POS_Y = 15;
    static constexpr int HP_GAUGE_ENEMY_HEIGHT = 25;
    static constexpr int HP_GAUGE_ENEMY_WIDTH = 260;
    static constexpr int HP_GAUGE_ENEMY_INNER_OFFSET = 1;
    static constexpr unsigned int HP_GAUGE_ENEMY_BG_COLOR = 0x000000;
    static constexpr unsigned int HP_GAUGE_ENEMY_COLOR = 0x2ce70b;

   
    static constexpr int HP_GAUGE_P2_POS_X = 15;  
    static constexpr int HP_GAUGE_P2_POS_Y = 15; 
    static constexpr int HP_GAUGE_P2_HEIGHT = 25;
    static constexpr int HP_GAUGE_P2_WIDTH = 260;
    // P2 HPゲージの描画に関する定数
    static constexpr int HP_GAUGE_P2_WIDTH_X = HP_GAUGE_P2_WIDTH+ HP_GAUGE_P2_POS_X;
    static constexpr int HP_GAUGE_P2_HEIGHT_Y = HP_GAUGE_P2_HEIGHT + HP_GAUGE_P2_POS_Y;

    static constexpr int HP_GAUGE_P2_INNER_OFFSET = 1;
  


    void Init(SceneGame* parent) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;


private:
  

};

