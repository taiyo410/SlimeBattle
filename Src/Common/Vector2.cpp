#include"./Vector2.h"
#include"./Vector2F.h"
//�f�t�H���g�R���X�g���N�^
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

//�R���X�g���N�^
Vector2::Vector2(int ix, int iy)
{
	x = ix;
	y = iy;
	
}

//�f�X�g���N�^
Vector2::~Vector2()
{
	
}
//Vector2F�֕ϊ�����
Vector2F Vector2::ToVector2F(void)
{
	Vector2F ret;
	ret.x = static_cast<float>(x);
	ret.y = static_cast<float>(y);
	return ret;
}