#pragma once
#include<DxLib.h>
class Parameta
{
public:
	//�f�t�H���g�R���X�g���N�^
	Parameta(void);

	//�R���X�g���N�^
	Parameta(VECTOR ipos, VECTOR irot, VECTOR iscl, bool iisLoop = false, bool iisStop = false);

	//�f�X�g���N�^
	~Parameta();


	//�����o�[�ϐ�
	VECTOR pos;
	VECTOR rot;
	VECTOR scl;
	bool isLoop;
	bool isStop;
};

