#pragma once
#include<vector>
#include<map>
#include<string>
#include"../Utility/SunUtility.h"
class ModelManager
{
public:
	//定数
	//アニメーションデフォルトの速度
	static constexpr float ANIM_SPEED_DEFAULT = SunUtility::DEFAULT_FPS;

	//角度
	//前
	static constexpr float FLONT_DEG = 180.0f;
	//後ろ
	static constexpr float BACK_DEG = 0.0f;
	//右
	static constexpr float RIGHT_DEG = 270.0f;
	//左
	static constexpr float LEFT_DEG = 180.0f;

	//アニメーションの終わり
	static constexpr float END_ANIM = 59.0F;

	//読み込むものがどういうものか
	enum class OBJECT
	{
		SLIME
		,ANIMAL
	};

	//読み込むモデル
	enum class MODEL_TYPE
	{
		KOKAGE
		,YUUHI
	};
	//アニメーション
	enum class ANIM_TYPE 
	{
		IDLE
		, STEP
		, CHARGE
		, ATTACK
		, WIN
		, DRAW_K
		, DRAW_Y
		, MAX
	};

	//モデルデータ
	struct MODEL_DATA
	{

	};
	//ロードするモデルを選べるようにする
	void ModelInit(void);

	std::map<OBJECT, MODEL_TYPE>object_;

	//モデルのロード
	int LoadModel (MODEL_TYPE model);

	//モデルのパラメータ設定
	void SetModelParam(MODEL_TYPE model, VECTOR pos, SunUtility::DIR_3D dir);
	//角度
	void SetRotation(SunUtility::DIR_3D dir,MODEL_TYPE model);

	//アニメーション処理
	void Animation(MODEL_TYPE model,VECTOR pos,VECTOR scl,SunUtility::DIR_3D dir);

	/// <summary>
	/// アニメーション更新処理
	/// </summary>
	/// <param name="accel">どれだけ遅くするか</param>
	void AnimUpdate(MODEL_TYPE model,float accel);

	//モデルの描画
	void DrawModel(MODEL_TYPE model);

	//アニメーション終わった後
	void EndAnimation(MODEL_TYPE model);

	//アニメーション変化
	void ChangeAnim(MODEL_TYPE model,ANIM_TYPE anim);

	//アニメーション中時間のセッタ
	void SetStepAnim(MODEL_TYPE model,float num);

	//モデルの削除
	void DeleteModel(MODEL_TYPE model);

	//モデルハンドルのゲッタ
	int GetModelHandle(MODEL_TYPE model);

	//モデルハンドルセッタ
	void SetModelHandle(MODEL_TYPE model, int handle);
	

private:
	std::map<MODEL_TYPE, int>modelId_;

	//モデルファイル名
	std::map<MODEL_TYPE,std::string> modelFilePass_;

	//角度
	VECTOR rot_;

	////BGMのタイプ指定
	//std::map<MODEL_TYPE, int>model_;

	//アニメーションのアタッチ番号
	std::map<MODEL_TYPE,int>animAttachNo_;

	//アニメ番号
	std::map<MODEL_TYPE, int> animNo_;

	//アニメ遷移用
	ANIM_TYPE anim_;

	//アニメーションの総再生時間
	std::map<MODEL_TYPE, float> animTotalTime_;

	//再生中のアニメーション時間
	std::map<MODEL_TYPE, float> stepAnim_;

	//アニメーション速度
	std::map<MODEL_TYPE, float> speedAnim_;

	//アニメ終わった判定
	std::map<MODEL_TYPE, bool> endAnim_;

};

