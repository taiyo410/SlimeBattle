#pragma once
class Vector2F
{
public:

	//�f�t�H���g�R���X�g���N�^
	Vector2F(void);

	//�R���X�g���N�^
	Vector2F(float ix, float iy,float iz);

	//�f�X�g���N�^
	~Vector2F();

	//Vector2F�֕ϊ�����
	Vector2 ToVector2(void);

	//�����o�[�ϐ�
	float x;
	float y;
	float z;
private:
};
