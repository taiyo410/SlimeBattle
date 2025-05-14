#pragma once
#include<DxLib.h>
#include "SceneBase.h"
#include "../Manager/ModelManager.h"
class SoundManager;
class ModelManager;
class ResultScene :
    public SceneBase
{
public:
    //定数
    //引き分けの時のスライムの間隔
    static constexpr float SLIME_DISTANCE = 5.0f;

    //イージング時間
    static constexpr float EASING_TOTAL_TIME = SunUtility::DEFAULT_FPS * 2;
    //イージング開始座標
    static constexpr float EASING_START_POS_Y = -800;

    //虹の画像回転速度
    static constexpr float RAINBOW_SPD = 0.05;
    //１周の角度
    static constexpr float TWO_PI_F = 2.0f * DX_PI_F;
    //BGMの音量
    static constexpr int BGM_VOL = 50;
    //イージングの強さ
    static constexpr float BACK_IN_S_VALUE = 0.5f;

    //画像
    //背景(WIN)
    const std::string WIN_BG_IMG = "ResultBack.png";
    //DRAW画像
    const std::string DRAW_IMG = "ResultBack(DrawNoback).png";
    //カーテン
    const std::string CURTAIN_IMG = "curtain.png";
    //虹
    const std::string RAINBOW_IMG = "PastelRainBow.png";

    //フォント
    //サイズ
    static constexpr int FONT_SIZE = 45;
    static constexpr int FONT_THICK = 8;

    //背景の座標
    static constexpr int RESULT_BACK_IMG_POS_X = Application::SCREEN_SIZE_X / 2;
    static constexpr int RESULT_BACK_IMG_POS_Y = Application::SCREEN_SIZE_Y / 2 + 50;

    //"Push The Botton!"関係
    //点滅
    static constexpr int STRING_INTERVAL = 30;
    static constexpr int STRING_BLINK = 2;
    //描画座標
    static constexpr int STRING_POS_Y = Application::SCREEN_SIZE_Y / 2 + 240;
    //文字の色
    static constexpr int STRING_COLOR = STRING_POS_Y;


    //基本処理
    bool Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    bool Release(void)override;

private:
    SoundManager* sound_;
    ModelManager* model_;
    int resultbgm_;		//リザルトBGM
    int resultImg_;     //画像
    int resultBackImg_; //リザルト画面背景
    int modelHandle_;   //モデルハンドル
    int curtainImg_;    //カーテン画像
    int stringCnt_;     //点滅用のカウント

    float easeStep_;    //イージングのステップ
    float resultBackImgRot_;//リザルト背景の角度

    VECTOR curtainPos_; //カーテン座標

    ModelManager::MODEL_TYPE modelType_;    //モデルタイプ
    ModelManager::MODEL_TYPE modelType2_;    //モデルタイプ引き分け用
    Parameta modelPar_;
    VECTOR modelPos_;
    VECTOR modelScl_;
    VECTOR modelRot_;

    VECTOR model2Pos_;
    VECTOR model2Scl_;
    VECTOR model2Rot_;
};

