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
    //�萔
    //���������̎��̃X���C���̊Ԋu
    static constexpr float SLIME_DISTANCE = 5.0f;

    //�C�[�W���O����
    static constexpr float EASING_TOTAL_TIME = SunUtility::DEFAULT_FPS * 2;
    //�C�[�W���O�J�n���W
    static constexpr float EASING_START_POS_Y = -800;

    //���̉摜��]���x
    static constexpr float RAINBOW_SPD = 0.05;
    //�P���̊p�x
    static constexpr float TWO_PI_F = 2.0f * DX_PI_F;
    //BGM�̉���
    static constexpr int BGM_VOL = 50;
    //�C�[�W���O�̋���
    static constexpr float BACK_IN_S_VALUE = 0.5f;

    //�摜
    //�w�i(WIN)
    const std::string WIN_BG_IMG = "ResultBack.png";
    //DRAW�摜
    const std::string DRAW_IMG = "ResultBack(DrawNoback).png";
    //�J�[�e��
    const std::string CURTAIN_IMG = "curtain.png";
    //��
    const std::string RAINBOW_IMG = "PastelRainBow.png";

    //�t�H���g
    //�T�C�Y
    static constexpr int FONT_SIZE = 45;
    static constexpr int FONT_THICK = 8;

    //�w�i�̍��W
    static constexpr int RESULT_BACK_IMG_POS_X = Application::SCREEN_SIZE_X / 2;
    static constexpr int RESULT_BACK_IMG_POS_Y = Application::SCREEN_SIZE_Y / 2 + 50;

    //"Push The Botton!"�֌W
    //�_��
    static constexpr int STRING_INTERVAL = 30;
    static constexpr int STRING_BLINK = 2;
    //�`����W
    static constexpr int STRING_POS_Y = Application::SCREEN_SIZE_Y / 2 + 240;
    //�����̐F
    static constexpr int STRING_COLOR = STRING_POS_Y;


    //��{����
    bool Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    bool Release(void)override;

private:
    SoundManager* sound_;
    ModelManager* model_;
    int resultbgm_;		//���U���gBGM
    int resultImg_;     //�摜
    int resultBackImg_; //���U���g��ʔw�i
    int modelHandle_;   //���f���n���h��
    int curtainImg_;    //�J�[�e���摜
    int stringCnt_;     //�_�ŗp�̃J�E���g

    float easeStep_;    //�C�[�W���O�̃X�e�b�v
    float resultBackImgRot_;//���U���g�w�i�̊p�x

    VECTOR curtainPos_; //�J�[�e�����W

    ModelManager::MODEL_TYPE modelType_;    //���f���^�C�v
    ModelManager::MODEL_TYPE modelType2_;    //���f���^�C�v���������p
    Parameta modelPar_;
    VECTOR modelPos_;
    VECTOR modelScl_;
    VECTOR modelRot_;

    VECTOR model2Pos_;
    VECTOR model2Scl_;
    VECTOR model2Rot_;
};

