#pragma once
class SceneBase
{
public:
	//�f�t�H���g�R���X�g���N�^
	SceneBase(void);

	//�f�X�g���N�^(���z��������񂩂畷��)
	virtual	~SceneBase(void);

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�������s		false:������~</returns>
	virtual bool Init(void);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	virtual void Draw(void);

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�������s		false:������~</returns>
	virtual bool Release(void);		//�������


private:
	//�����o�[�ϐ�
};