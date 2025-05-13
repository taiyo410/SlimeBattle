#pragma once
class Grid
{
public:
	//���̒���
	static constexpr float LEN = 800.0f;

	//���̒����̔���
	static constexpr float HLEN = LEN / 2.0f;

	//���̊Ԋu
	static constexpr float TERM = 60.0f;

	//���̐�
	static constexpr float NUM = static_cast<int>(LEN / TERM);

	//���̐��̔���
	static const int HNUM = static_cast<int>(NUM / 2);

	//���̔��a
	static constexpr float RADIUS = 15.0f;

	//���̊p�x�̕�����
	static constexpr int DIV_NUM = 8;

	//�R���X�g���N�^
	Grid(void);

	//�f�X�g���N�^
	~Grid(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
};