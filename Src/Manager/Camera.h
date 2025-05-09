#pragma once
#include<DxLib.h>

class Camera
{
public:

	//�R���X�g���N�^
	Camera(void);

	//�f�X�g���N�^
	~Camera();

	enum class SHAKE_STATE
	{
		SHAKE_UP
		,SHAKE_DOWN
	};
	/// <summary>
	///����������(��{�I�ɍŏ���1�񂾂�����)
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// �X�V����(���t���[�����s)
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// �J�����ݒ�
	/// </summary>
	/// <param name=""></param>
	void SetBeforeDraw(void);
	
	/// <summary>
	/// �`�揈��(���t���[�����s)
	/// </summary>
	/// <param name=""></param>
	void Draw(void);
	
	/// <summary>
	/// �������(��{�I�ɍŌ��1�񂾂�����)
	/// </summary>
	/// <param name=""></param>
	void Release(void);

	//�J�����V�F�C�N
	void CameraShake(int shakeCnt,float cameraLimit);

	//�J�������[�N�̃Z�b�g
	void SetCameraWork(VECTOR pos, VECTOR rot);

private:

	/// <summary>
	/// �J�����̈ʒu
	/// </summary>
	VECTOR pos_;

	VECTOR angles_;

	int shakeCnt_;

	SHAKE_STATE shakeState_;

};
