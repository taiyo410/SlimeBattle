//#pragma once
#include"../Common/CommonData.h"
#include "RuleBase.h"
class RuleScore :
    public RuleBase
{
public:
    //�萔
    //��������
    static constexpr int TIME_LIMIT = 30;
    void Init(SceneGame* parent) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
private:
    CommonData::WINPATTERN win_;



    int startTime_;  //���݌o�ߎ���
    int timeLimit_;  //��������
    int minute_;   //1������
    int count_;        //1�b����
    int countDown_;     //�J�E���g�_�E���p�ϐ�


    LPCSTR fontHandle_;    //�t�H���g�f�[�^�i�[

};

