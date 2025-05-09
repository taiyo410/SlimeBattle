#include<DxLib.h>
#include<string>
#include<vector>
#include<sstream>
#include"../Common/Vector2.h"
#include"../Common/Vector2F.h"
#include"./SunUtility.h"

std::vector<std::string> SunUtility::Split(std::string& line, char delimiter)
{
	//動的配列の返り値準備
	std::vector<std::string>result;

	//文字列操作用のクラスに置き換える
	std::stringstream stream(line);

	//1データの格納領域
	std::string field;

	//streamを順に読み込み、
	//getlineを使って
	//第３引数で指定されたデリミタ記号までのデータを,
	//第２引数の変数に格納する
	while (getline(stream, field, delimiter))
	{
		//動的配列に取得したデータを追加する
		result.push_back(field);
	}

	return  result;
}

//四捨五入
int SunUtility::Round(float value)
{
	return static_cast<int>(roundf(value));
}

Vector2 SunUtility::Round(Vector2F value)
{
	Vector2 ret;
	ret.x = static_cast<int>(roundf(value.x));
	ret.y = static_cast<int>(roundf(value.y));

	return ret;
}


bool SunUtility::IsHitSpheres(const VECTOR& pos1, float radius1
	, const VECTOR& pos2, float radius2)
{
	//球体同士の当たり判定
	bool ret = false;

	//お互いの半径の合計
	float radius = radius1 + radius2;

	//座標の差からお互いの距離をとる
	VECTOR diff = VSub(pos2, pos1);

	//三平方の定理で比較(SprMagnitudeと同じ)
	float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
	if (dis < (radius * radius))
	{
		ret = true;
	}

	return ret;
}



SunUtility::DIR_3D SunUtility::ToDirection(VECTOR dir)
{
	DIR_3D nearDir = DIR_3D::MAX;

	int size = (int)DIR_3D::MAX; // 4
	float maxDot = -1.0f;
	for (int i = 0; i < size; i++)
	{

		VECTOR dir2 = SunUtility::ToDirection((DIR_3D)i);
		float dot = VDot(dir, dir2);
		if (dot > maxDot)
		{
			nearDir = (DIR_3D)i;
			maxDot = dot;
		}

	}

	return nearDir;

}

VECTOR SunUtility::ToDirection(DIR_3D dir)
{

	VECTOR ret = { 0.0f, 0.0f, 0.0f };

	switch (dir)
	{
	case SunUtility::DIR_3D::FLONT:
		ret = { 0.0f, 0.0f, 1.0f };
		break;
	case SunUtility::DIR_3D::BACK:
		ret = { 0.0f, 0.0f, -1.0f };
		break;
	case SunUtility::DIR_3D::RIGHT:
		ret = { 1.0f, 0.0f, 0.0f };
		break;
	case SunUtility::DIR_3D::LEFT:
		ret = { -1.0f, 0.0f, 0.0f };
		break;
	}

	return ret;

}

bool SunUtility::EqualsVZero(const VECTOR& v1)
{
	const VECTOR& v2 = VECTOR_ZERO;
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
	{
		return true;
	}
	return false;
}
