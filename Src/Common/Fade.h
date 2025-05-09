#pragma once

class Fader
{
public:
	//�t�F�[�h���i�ޑ���
	static constexpr float SPEED_ALPHA = 5;

	//���
	enum class STATE
	{
		NONE
		,FADE_OUT	//���X�ɈÓ]
		,FADE_IN	//���X�ɖ��]
	};

	//�R���X�g���N�^
	Fader(void);

	//�f�X�g���N�^
	~Fader(void);
	

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	void Draw(void);

	/// <summary>
	/// �t�F�[�h��Ԃ̃Q�b�^�[
	/// </summary>
	/// <param name=""></param>
	/// <returns>�t�F�[�h���</returns>
	STATE GetState(void);

	/// <summary>
	/// �t�F�[�h��Ԃ��I�����Ă��邩
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�I�����Ă���		false:�I�����Ă��Ȃ�</returns>
	bool IsEnd(void);

	/// <summary>
	/// �t�F�[�h��ݒ肷��
	/// </summary>
	/// <param name="state">�t�F�[�h�̏��</param>
	void SetFade(STATE state);

private:
	//���
	STATE state_;

	//�����x
	float alpha_;

	bool isPreEnd_;

	//�t�F�[�h�����̏I������
	bool isEnd_;

};