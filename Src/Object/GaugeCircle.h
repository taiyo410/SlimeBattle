#pragma once
#include<DxLib.h>
#include<vector>
#include<map>
class GaugeCircle
{
public:
	//ポリゴン数,ポリゴンの分割数
	enum class GAUGE_TYPE
	{
		CHARGE
		,PARRY_K
		,PARRY_Y
	};
	static constexpr int DIV_NUM = 8;

	void Init(void);

	/// <summary>
	///描画
	/// </summary>
	/// <param name="pos">表示位置(スクリーン位置)</param>
	/// <param name="SIZEX">表示サイズX</param>
	/// <param name="SIZEY">表示サイズY</param>
	/// <param name="rate">円の描画範囲(最大値は1.0なので割合を計算してから使うこと)</param>
	void Draw(GAUGE_TYPE type,VECTOR pos, int sizeX, int sizeY, float rate,bool isDraw);

	void Release(void);

	//画像ハンドルゲッタ
	int GetImg(GAUGE_TYPE type);

private:
	//ゲージ画像のハンドルID
	std::map<GAUGE_TYPE , int> textureGauge_;
	std::vector<VERTEX2D> vertexes_;
	std::vector<VERTEX2D> frameVertexes_;

	//フレーム画像
	int textureFrame_;

	//作成したポリゴンの数
	int polygonNum_;

	//頂点の作成
	void MakeCircleVertex(VECTOR pos, int sizeX, int sizeY, float rate);

	//フレーム
	void MakeFrameVertex(VECTOR pos, int sizeX, int sizeY, float rate = 1.0f);

	//頂点位置の計算
	VECTOR MakeRotLocalPos(float rad, float sizeX, float sizeY);
};

