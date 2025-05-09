#include<DxLib.h>
#include"./Grid.h"


//コンストラクタ
Grid::Grid(void)
{

}

//デストラクタ
Grid::~Grid(void)
{

}

void Grid::Init(void)
{

}
void Grid::Update(void)
{

}
void Grid::Draw(void)
{
	//とりあえず1本
	VECTOR sPos = { -HLEN,0.0f,0.0f };
	VECTOR ePos = { HLEN,0.0f,0.0f };
	for (int dis_z = -HNUM; dis_z < HNUM; dis_z++)
	{
		sPos.z = dis_z * TERM;
		ePos.z = dis_z * TERM;
		DrawLine3D(sPos, ePos, 0xff0000);
		DrawSphere3D(ePos, 15.0f, 10, 0xff0000, 0xff0000, true);
	}
	sPos = { 0.0f,0.0f,-HLEN };
	ePos = { 0.0f,0.0f,HLEN };
	for (int dis_x = -HNUM; dis_x < HNUM; dis_x++)
	{
		sPos.x = dis_x * TERM;
		ePos.x = dis_x * TERM;
		DrawLine3D(sPos, ePos, 0x0000ff);
		DrawSphere3D(ePos, 15.0f, 10, 0x0000ff, 0x0000ff, true);
	}
	
}
void Grid::Release(void)
{

}