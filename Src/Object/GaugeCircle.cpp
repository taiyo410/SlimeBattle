#include"../Application.h"
#include "GaugeCircle.h"

void GaugeCircle::Init(void)
{
	textureGauge_[GAUGE_TYPE::CHARGE] = LoadGraph((Application::PATH_IMAGE + "Circle.png").c_str());
	textureGauge_[GAUGE_TYPE::PARRY_K] = LoadGraph((Application::PATH_IMAGE + "ParryK.png.").c_str());
	textureGauge_[GAUGE_TYPE::PARRY_Y] = LoadGraph((Application::PATH_IMAGE + "ParryY.png.").c_str());

	textureFrame_ = LoadGraph((Application::PATH_IMAGE + "CircleFrame.png").c_str());
	
}

void GaugeCircle::Draw(GAUGE_TYPE type, VECTOR pos, int sizeX, int sizeY, float rate,bool isDraw)
{
	if (isDraw)
	{
		//ポリゴンを作成(フレーム)
		MakeFrameVertex(pos, sizeX, sizeY);
	}
	
	//ポリゴンの作成(ゲージ)
	MakeCircleVertex(pos, sizeX, sizeY, rate);
	
	

	//ビルボードのように描画する(ゲージ)
	DrawPolygon2D(vertexes_.data(), polygonNum_, textureGauge_[type], true);

	if (isDraw)
	{
		//ビルボードのように描画する(フレーム)
		DrawPolygon2D(frameVertexes_.data(), 8, textureFrame_, true);
	}


	
	
	
}

void GaugeCircle::Release(void)
{

}

int GaugeCircle::GetImg(GAUGE_TYPE type)
{
	return textureGauge_[type];
}

void GaugeCircle::MakeCircleVertex(VECTOR pos, int sizeX, int sizeY, float rate)
{

	vertexes_.clear();

	//分割角度(3.14*2/8=でグリーでいうと45度)
	float divRad = DX_TWO_PI_F / static_cast<float>(DIV_NUM);

	//作成する最大角度(360°の時rate=1、180°のときrate=0.5)
	float endRad = DX_TWO_PI_F * rate;

	//ポリゴン数のリセット
	polygonNum_ = 0;

	float rad = 0.0f;
	float sizeXF = static_cast<float>(sizeX);
	float sizeYF = static_cast<float>(sizeY);

	//ループでポリゴン(頂点)を作る
	while (polygonNum_ < DIV_NUM)
	{
		VECTOR pos1 = MakeRotLocalPos(rad, sizeXF, sizeYF);
		rad += divRad;
		//上限値
		if (rad > endRad)
		{
			rad = endRad;
		}
		VECTOR pos2 = MakeRotLocalPos(rad, sizeXF, sizeYF);


		VERTEX2D vertex = VERTEX2D();

		//中心座標
		vertex.pos = pos;
		vertex.pos.z = 0.0f;
		vertex.u = 0.5f;
		vertex.v = 0.5f;
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);

		//次の頂点

		vertex.pos = VAdd(pos, pos1);
		vertex.pos.z = 0.0f;
		vertex.u = (pos1.x + sizeXF) / (sizeXF + sizeXF);
		vertex.v = (pos1.y + sizeYF) / (sizeYF + sizeYF);
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);


		vertex.pos = VAdd(pos, pos2);
		vertex.pos.z = 0.0f;
		vertex.u = (pos2.x + sizeXF) / (sizeXF + sizeXF);
		vertex.v = (pos2.y + sizeYF) / (sizeYF + sizeYF);
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);

		//ポリゴン数の増加
		polygonNum_++;
		if (rad >= endRad)
		{
			//作成する最大角度まで到達したので処理終了
			break;
		}

	}


}

void GaugeCircle::MakeFrameVertex(VECTOR pos, int sizeX, int sizeY, float rate)
{
		frameVertexes_.clear();

		//分割角度(3.14*2/8=でグリーでいうと45度)
		float divRad = DX_TWO_PI_F / static_cast<float>(DIV_NUM);

		//作成する最大角度(360°の時rate=1、180°のときrate=0.5)
		float endRad = DX_TWO_PI_F * rate;

		//ポリゴン数のリセット
		int polygonNum = 0;

		float rad = 0.0f;
		float sizeXF = static_cast<float>(sizeX);
		float sizeYF = static_cast<float>(sizeY);

		//ループでポリゴン(頂点)を作る
		while (polygonNum < DIV_NUM)
		{
			VECTOR pos1 = MakeRotLocalPos(rad, sizeXF, sizeYF);
			rad += divRad;
			//上限値
			if (rad > endRad)
			{
				rad = endRad;
			}
			VECTOR pos2 = MakeRotLocalPos(rad, sizeXF, sizeYF);


			VERTEX2D vertex = VERTEX2D();

			//中心座標
			vertex.pos = pos;
			vertex.pos.z = 0.0f;
			vertex.u = 0.5f;
			vertex.v = 0.5f;
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);

			//次の頂点

			vertex.pos = VAdd(pos, pos1);
			vertex.pos.z = 0.0f;
			vertex.u = (pos1.x + sizeXF) / (sizeXF + sizeXF);
			vertex.v = (pos1.y + sizeYF) / (sizeYF + sizeYF);
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);


			vertex.pos = VAdd(pos, pos2);
			vertex.pos.z = 0.0f;
			vertex.u = (pos2.x + sizeXF) / (sizeXF + sizeXF);
			vertex.v = (pos2.y + sizeYF) / (sizeYF + sizeYF);
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);

			//ポリゴン数の増加
			polygonNum++;
			if (rad >= endRad)
			{
				//作成する最大角度まで到達したので処理終了
				break;
			}

		}
	
}

VECTOR GaugeCircle::MakeRotLocalPos(float rad, float sizeX, float sizeY)
{
	VECTOR ret = VECTOR();

	float dirX = sinf(rad);
	float dirY = -cosf(rad);

	//ざっくり斜辺の長さ
	float len = sqrtf(sizeX * sizeX + sizeY * sizeY);

	ret.x = dirX * len;
	ret.y = dirY * len;
	
	//矩形に収める
	if (ret.x > sizeX)
	{
		ret.x = sizeX;
	}
	if (ret.x < -sizeX)
	{
		ret.x = -sizeX;
	}
	if (ret.y > sizeY)
	{
		ret.y = sizeY;
	}
	if (ret.y < -sizeY)
	{
		ret.y = -sizeY;
	}
	return ret;
}
