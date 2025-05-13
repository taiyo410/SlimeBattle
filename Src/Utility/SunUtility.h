#pragma once
#include<DxLib.h>
#include<string>
#include<vector>

class Vector2;
class Vector2F;
class SunUtility
{
	//メンバー変数
public:
	//定数
	static constexpr int DEFAULT_FPS = 60;

	//パーセント
	static constexpr int PERCENT_MAX = 100;
	static constexpr float PERCENT_MAX_F = 1.0f;

	//デルタタイム
	static constexpr float DELTA_TIME = 1.0f / SunUtility::DEFAULT_FPS;

	//座標ゼロ
	static constexpr VECTOR VECTOR_ZERO = { 0.0f,0.0f,0.0f };

	//色関係
	//赤
	static constexpr int RED = 0xff0000;
	//緑
	static constexpr int GREEN = 0x00ff00;
	//青
	static constexpr int BLUE = 0x0000ff;
	//白
	static constexpr int WHITE = 0xffffff;
	//黒
	static constexpr int BLACK = 0x000000;


	//2D方向
	enum class DIR_2D
	{
		UP
		,DOWN
		,LEFT
		,RIGHT
		,MAX
	};

	//3D方向
	enum class DIR_3D
	{
		FLONT
		,BACK
		,RIGHT
		,LEFT
		,MAX
	};

	

	/// <summary>
	/// 文字列の分割
	/// </summary>
	/// <param name="line"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	static std::vector<std::string>Split(std::string& line, char delimiter);

	//四捨五入
	static int Round(float value);
	//四捨五入用の関数(Vector2)
	static Vector2 Round(Vector2F value);

	//球体と球体の当たり判定
	bool IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	

	//無限にある方向から4方向に変える
	static DIR_3D ToDirection(VECTOR dir);

	//オリジナルベクトルから方向べくとるに変える
	static VECTOR ToDirection(DIR_3D dir);

	//比較
	static bool EqualsVZero(const VECTOR& v1);
private:

};
