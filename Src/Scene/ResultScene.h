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
    static constexpr float SLIME_DISTANCE = 5.0f;
    static constexpr float EASING_TOTAL_TIME = SunUtility::DEFAULT_FPS * 2;

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

