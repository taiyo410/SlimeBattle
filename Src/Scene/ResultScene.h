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
    static constexpr float SLIME_DISTANCE = 5.0f;
    static constexpr float EASING_TOTAL_TIME = SunUtility::DEFAULT_FPS * 2;

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

