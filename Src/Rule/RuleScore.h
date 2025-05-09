//#pragma once
#include"../Common/CommonData.h"
#include "RuleBase.h"
class RuleScore :
    public RuleBase
{
public:
    //定数
    //制限時間
    static constexpr int TIME_LIMIT = 30;
    void Init(SceneGame* parent) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
private:
    CommonData::WINPATTERN win_;



    int startTime_;  //現在経過時間
    int timeLimit_;  //制限時間
    int minute_;   //1分ごと
    int count_;        //1秒ごと
    int countDown_;     //カウントダウン用変数


    LPCSTR fontHandle_;    //フォントデータ格納

};

