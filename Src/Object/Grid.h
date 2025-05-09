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
	static const int HNUM = NUM / 2;

	//�R���X�g���N�^
	Grid(void);

	//�f�X�g���N�^
	~Grid(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
};