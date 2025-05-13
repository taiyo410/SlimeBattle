#pragma once
#include<DxLib.h>
#include"../Utility/SunUtility.h"
#include"./SlimeBase.h"
class SceneGame;
class Player;
class Enemy:public SlimeBase
{
public:

	//�萔
	//�G���߂Â��X�s�[�h
	static constexpr float MOVE_SPEED = 1.0f;
	//�̗�
	static constexpr int MAX_HP = 200;

	//�G�̈ړ��𑱂�������܂ł̍�
	static constexpr int MOVE_POS_E2P = 90;

	//�N�[���^�C��
	static constexpr int COOL_TIME_MAX = SunUtility::DEFAULT_FPS * 1;

	//�L�͈͍U���W�����v�p���[
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//�L�͈͍U���N�[���^�C��
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//�L�͈͍U���`���[�W�ő�l
	static constexpr float WAID_CHARGE_MAX = static_cast<float>(SunUtility::DEFAULT_FPS) * 1.3f;
	static constexpr float WAID_JUMPCNT_MAX = static_cast<float>(SunUtility::DEFAULT_FPS) * 0.3f;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//�X�^�~�i�񕜏�Ԃ̃J�E���g
	static constexpr int STAMINA_RECOV_TIME = SunUtility::DEFAULT_FPS * 5;

	//�ːi�U�����I�������̃N�[���^�C��
	static constexpr float NORMAL_ATK_COOLTIME = SunUtility::DEFAULT_FPS * 2;

	//�L�͈͍U���̗������p�̏d��
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;
	//���ߎ���
	static constexpr float CHARGE_CNT = 5.0f;
	//�����Ă��鎞��
	static constexpr int FALL_CNT = SunUtility::DEFAULT_FPS * 2;


	//�����J�E���g
	static constexpr int REVIVAL_CNT_MAX = SunUtility::DEFAULT_FPS * 2;

	// �G����v���C���[�ւ�Y�������̃I�t�Z�b�g�l
	static constexpr float ENEMY_TO_PLAYER_Y_OFFSET = 50.0f;

	// ��������X�������̃}�[�W��
	static constexpr float ESCAPE_MARGIN_X = 210.0f;
	// ��������Z�������̃}�[�W��
	static constexpr float ESCAPE_MARGIN_Z = 210.0f;

	//�U���J�n���̃v���C���[�Ƃ̃}�[�W��
	static constexpr float CHARGE_MARGIN_X = 180.0f;
	static constexpr float CHARGE_MARGIN_Z = 180.0f;


	// �ړ��I����̃N�[���^�C�� (�b)
	static constexpr float MOVE_END_COOL_TIME_SEC = 0.5f;

	//�J�����̃V�F�C�N�J�E���g
	static constexpr float SHAKE_CNT = 10;

	//�J�����̐���
	static constexpr float SHAKE_LIMIT = 10;

	//�`��
	 // �X�^�~�i�Q�[�W�̕`��Ɋւ���萔
	static constexpr int STAMINA_GAUGE_X = 15;
	static constexpr int STAMINA_GAUGE_Y = 50;
	static constexpr int STAMINA_GAUGE_WIDTH = 260; // 275 - 15
	static constexpr int STAMINA_GAUGE_HEIGHT = 25;  // 75 - 50
	static constexpr int STAMINA_GAUGE_INNER_OFFSET = 1; // �w�i�Ƃ̌���
	static constexpr int STAMINA_GAUGE_BG_COLOR = 0x000000;
	static constexpr int STAMINA_GAUGE_CURRENT_COLOR = 0x9d370e;
	static constexpr int STAMINA_GAUGE_CONSUMPTION_COLOR = 0xED784A;


	//�L�͈͍U��
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};

	//�G�̍U�߂Ɠ���
	enum class ACT
	{
		Attack
		,ESCAPE
	};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	
	void Update(void) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	void Draw(void) override;

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void) override;

	/// <summary>
	/// �f�o�b�O�p�̊֐�
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);

	//��ԕω��p�֐�
	void ChangeEnemyState(SlimeBase::ENEMYSTATE state)override;

	//�L�͈͍U���p�̏�ԕω��p
	//void ChangeWaidAtkState(const WAID_ATK waidAtk);

	//�X�^�~�i�ƃt���[���̌��Z
	void FrameComsumption(void);

	//�X�^�~�i�񕜏���
	void StaminaRecovery(void);

	//�G�̏�ԃQ�b�^
	SlimeBase::ENEMYSTATE GetState(void);


	//�L�͈͍U����ԃw�b�_
	//Enemy::WAID_ATK GetWaidAtkState(void) const;

	//�G��Ԃ̃Z�b�^�[
	void SetEnemyState(const SlimeBase::ENEMYSTATE enemyState);
	//���������߂�֐�
	void MoveDir(void);

	//��Ԃ��Ƃ̍X�V
	void StateUpdate(void)override;

#pragma region ��Ԃ��Ƃ̏���
	//�N�[����
	void UpdateNone(void);

	//�l����
	void UpdateThink(void);

	//�v���C���[�܂ŋ߂Â�
	void UpdateMove(void);

	//�X�e�b�v
	void UpdateStep(void);

	//�`���[�W
	void UpdateCharge(void);

	//�m�b�N�o�b�N
	void UpdateKnockBuck(void);

	//�ːi
	void UpdateNormalAttack(void);

	//�L�͈͍U��
	void UpdateWaidAttack(void);

	//�����Ă�����
	void FallUpdate(void);

	//��������
	void RevivalUpdate(void);

	//���ʂ̏�ԏ���
	void DebuffUpdate(void);

#pragma endregion
	

	

	//�����蔻��̃Q�b�^
	float GetWaidCol(void)const;
	void ChangeWaidAtkState(const SlimeBase::WAID_ATK waidAtk)override;
	
private:
	//�|�C���^�i�[�̈�
	Player* player_;
	bool isMove_;	//�����Ă邩����


	int waidChargeCnt_;	//�L�͈͍U���̗��߃J�E���g
	int waidAtkCoolTime_;	//�L�͈͍U���̃N�[���^�C��
	float waidAtkRadius_;		//�L�͈͍U���̓����蔻���傫�����Ă���
	SlimeBase::ENEMYSTATE state_;	//��ԕϐ�
	//WAID_ATK waidAtk_;
	ACT act_;			//�s���p�^�[��

	float jumpCnt_;		//�L�͈͍U���̃W�����v�J�E���g

	
	
	SunUtility::DIR_3D moveDir_;	//��������

	VECTOR moveRoute_;	//�s��̍��W
	
	//�p�����^�̏�����
	void SetParam(VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir)override;

	//�m�b�N�o�b�N����
	void KnockBack(void);




};
