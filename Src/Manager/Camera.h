#pragma once
#include<DxLib.h>

class Camera
{
public:
	//定数
	//初期座標
	static constexpr VECTOR INIT_POS = { 0.0f,600.0f,-200.0f };

	//初期座標
	static constexpr VECTOR INIT_ANGLES = { 75.0f * DX_PI_F / 180.0f,0.0f,0.0f };

	//カメラが見える範囲
	static constexpr float CAMERA_NEAR = 10.0f;

	//遠く
	static constexpr float CAMERA_FAR = 10.0f;
	//コンストラクタ
	Camera(void);

	//デストラクタ
	~Camera();


	enum class SHAKE_STATE
	{
		SHAKE_UP
		,SHAKE_DOWN
	};
	/// <summary>
	///初期化処理(基本的に最初の1回だけ実装)
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// 更新処理(毎フレーム実行)
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// カメラ設定
	/// </summary>
	/// <param name=""></param>
	void SetBeforeDraw(void);
	
	/// <summary>
	/// 描画処理(毎フレーム実行)
	/// </summary>
	/// <param name=""></param>
	void Draw(void);
	
	/// <summary>
	/// 解放処理(基本的に最後の1回だけ実装)
	/// </summary>
	/// <param name=""></param>
	void Release(void);

	//カメラシェイク
	void CameraShake(int shakeCnt,float cameraLimit);

	//カメラワークのセット
	void SetCameraWork(VECTOR pos, VECTOR rot);

private:

	/// <summary>
	/// カメラの位置
	/// </summary>
	VECTOR pos_;

	VECTOR angles_;

	int shakeCnt_;

	SHAKE_STATE shakeState_;

};
