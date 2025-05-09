#include"./Vector2.h"
#include"./Vector2F.h"
//�f�t�H���g�R���X�g���N�^
Vector2F::Vector2F(void)
{
	x = 0.0F;
	y = 0.0F;
	z = 0.0f;
}
//�R���X�g���N�^
Vector2F::Vector2F(float ix,float iy,float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

//�f�X�g���N�^
Vector2F::~Vector2F()
{

}
//Vector2�^�ɕϊ�
Vector2 Vector2F::ToVector2(void)
{
	Vector2 ret;
	ret.x = static_cast<int>(x);
	ret.y = static_cast<int>(y);
	ret.z = static_cast<int>(z);
	return ret;
}
