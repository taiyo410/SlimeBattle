#pragma once
class InputManager
{
	//�����o�[�֐�
public:
	//�萔
	//-----------------------
	static constexpr int KEY_BUF_LEN = 256;

	static constexpr int PAD_NUM = 2;



	



	/// <summary>
	/// ������̕���
	/// </summary>
	/// <param name=""></param>
	void InitInput(void);

	/// <summary>
	/// ������̕���
	/// </summary>
	/// <param name=""></param>
	void StepInput(void);

#pragma region �L�[�{�[�h����
	/// <summary>
	/// �P���ɉ�����Ă��邩(Check_Hit_Key�Ɠ�������)
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns>true:�����ꂽ		false:������ĂȂ�</returns>
	bool IsKeyDown(int key_code);

	/// <summary>
	/// �������ꂽ
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns></returns>
	bool IsKeyPush(int key_code);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns>true:���������ꂽ		false:����������ĂȂ�</returns>
	bool IsKeyKeep(int key_code);

	/// <summary>
	/// �������ꂽ
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns>true:�����ꂽ		false:������ĂȂ�</returns>
	bool IsKeyRelease(int key_code);
#pragma endregion
#pragma region �R���g���[���[
	//���䏈��
	void StepPadInput(void);

	/// <summary>
/// �P���ɉ�����Ă��邩(Check_Hit_Key�Ɠ�������)
/// </summary>
/// <param name="key_code">�L�[�̏ꏊ</param>
/// <returns>true:�����ꂽ		false:������ĂȂ�</returns>
	bool IsPadDown(int padNum,int key_code);

	/// <summary>
	/// �������ꂽ
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns></returns>
	bool IsPadPush(int padNum, int key_code);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns>true:���������ꂽ		false:����������ĂȂ�</returns>
	bool IsPadKeep(int padNum, int key_code);

	/// <summary>
	/// �������ꂽ
	/// </summary>
	/// <param name="key_code">�L�[�̏ꏊ</param>
	/// <returns>true:�����ꂽ		false:������ĂȂ�</returns>
	bool IsPadRelease(int padNum, int key_code);
#pragma endregion

	

	//�C���X�^���X�̉��
	void ReleaseInput(void);

	//�V���O���g����
	//------------------------------
	static void CreateInput(void);

	//�O���ŃC���X�^���X�𗘗p�\�ɂ��邽�߂�
	//�C���X�^���X�ŕԂ��֐���p��
	static InputManager& GetInput(void);

	//�C���X�^���X�̍폜
	void Destroy(void);
	
private:
	//�V���O���g����
	//�f�t�H���g�R���X�g���N�^
	InputManager(void);
	//�f�X�g���N�^
	~InputManager(void);
	

	//�R�s�[�R���X�g���N�^�𗘗p�s�ɂ���
	InputManager(const InputManager& ins);


	//�O�t���[���̃L�[���
	int prePadBuf_[PAD_NUM];

	//���݃t���[���̃L�[���
	int currentPadBuf_[PAD_NUM];

	//�����o�[�ϐ�
	//���݃t���[���̃L�[���
	char currentKeyBuf_[256];

	//�O�t���[���̃L�[���
	char preKeyBuf_[256];


	//�ÓI�ȃC���X�^���X������
	static InputManager* input_;
};
