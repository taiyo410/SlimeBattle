#pragma once
class Vector2F;
class Vector2
{
public:

	//�f�t�H���g�R���X�g���N�^
	Vector2(void);

	//�R���X�g���N�^
	Vector2(int ix, int iy);

	//�f�X�g���N�^
	~Vector2();

	//Vector2F�ɕϊ�����֐�
	Vector2F ToVector2F(void);

	//�����o�[�ϐ�
	int x;
	int y;
	int z;

private:
};
