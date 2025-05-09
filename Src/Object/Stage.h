#pragma once
#include<DxLib.h>
class Stage
{
public:
	//�P�}�X
	static constexpr int STAGE_ONE_SQUARE = 60;
	//�}�X�̐�
	static constexpr int STAGE_SQUARE_NUM = 11;
	//�X�e�[�W�S�̃T�C�Y
	static constexpr int STAGE_ALL_SIZE_X = STAGE_ONE_SQUARE * STAGE_SQUARE_NUM;
	static constexpr int STAGE_ALL_SIZE_Z = STAGE_ONE_SQUARE * STAGE_SQUARE_NUM;

	//�X�e�[�W�����T�C�Y
	static constexpr int STATE_HALF_SIZE_X = STAGE_ALL_SIZE_X / 2;
	static constexpr int STATE_HALF_SIZE_Z = STAGE_ALL_SIZE_Z / 2;



	//�X�e�[�W�̒��S����̃T�C�Y
	//�㑤�ƉE��
	static constexpr VECTOR STAGE_UP_RIGHT_CENTER2SIZE = { 330,0,330 };
	//�����ƍ���
	static constexpr VECTOR STAGE_DOWN_LEFT_CENTER2SIZE = { -330,0,-330 };
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	int model_;
};

