#pragma once
#include<DxLib.h>
#include"../Utility/SunUtility.h"
#include"../Common/CommonData.h"
#include"./SlimeBase.h"
class SceneGame;
class Player2;

class Player:public SlimeBase
{
public:
	//�l�̏㉺���J��Ԃ�
	enum class UP_AND_DOWN
	{
		UP
		, DOWN
	};

	//�萔
	//***********************************************
	//�������W
	static constexpr VECTOR INIT_POS = { -Stage::STAGE_ONE_SQUARE * 3, RADIUS, 0.0f };
	//�N�[���^�C��
	static constexpr int COOL_TIME = 30;

	//�v���C���[�̏�Ԕԍ�
	static constexpr int STATE_ATTACK = 6;

	//�X�e�b�v��t����
	static constexpr int STEP_FRAME_MAX = 10;

	//HP�ő�l
	static constexpr int MAX_HP = 200;


	//----------------------------------------------
	//�K�[�h�֘A
	//-----------------------------------------------
	//�K�[�h�J�E���g�}�b�N�X
	static constexpr int GUARD_CNT_MAX = static_cast<int>(SunUtility::DEFAULT_FPS * 0.5f);

	//�K�[�h�N�[���^�C��
	static constexpr int GUARD_COOLTIME = SunUtility::DEFAULT_FPS * 5;

	//�K�[�h�N�[���^�C���Q�[�W�f�t�H���g�T�C�Y
	static constexpr int GUARD_GAUGE_SIZE_DEFAULT = 60;

	//�K�[�h�N�[���^�C���Q�[�W�̍ő�A�ŏ��T�C�Y�ƃf�t�H���g�T�C�Y�̍�
	static constexpr int GUARD_GAUGE_SIZE_MARGIN = 10;

	//�K�[�h�������̃N�[���^�C��
	static constexpr int GUARD_COOLTIME_SUCCESS = static_cast<int>(SunUtility::DEFAULT_FPS * 2.5f);
	//---------------------------------------------------

	//���ߍU����Ԃ̂Ƃ��̏���ʂ̔{��
	static constexpr int CHARGE_ATK_STAMINA = 2;

	//���߂Ă�Ԃ�1�t���[���ɏ����X�^�~�i�i����ʗp�j
	static constexpr float CHARGE_STAMINA_PER_FRAME = CHARGE_SPEED * CHARGE_ATK_STAMINA;

	//�p���B�̏d�ݕt��
	static constexpr int PARRY_ATK_POW = 5;

	//���ߍU���̏d�ݕt��
	static constexpr int CHARGE_ATK_POW = 2;

	//�X�e�b�v�ŏ����X�^�~�i
	static constexpr float STEP_STEMINA = FRAME_DEFAULT;

	//�`���[�W�ŏ����X�^�~�i(�Œ�l)
	static constexpr float CHARGE_STAMINA_VAL = FRAME_DEFAULT * CHARGE_ATK_STAMINA;

	//�m�b�N�o�b�N��̃N�[���^�C��
	static constexpr int KNOCKBACK_AFTER_CNT = SunUtility::DEFAULT_FPS * 1;

	//�N���e�B�J���J�E���g�ő�
	static constexpr int CRITICAL_CNT_MAX = 1;

	//�����Ă��鎞��
	static constexpr int FALL_CNT = SunUtility::DEFAULT_FPS * 2;

	//�����J�E���g
	static constexpr int REVIVAL_CNT_MAX = SunUtility::DEFAULT_FPS * 2;

	//������(�������āA�n��ɍ~�肽��̖��G����)
	static constexpr int AFTER_REVIVAL_CNT = SunUtility::DEFAULT_FPS * 3;

	//��ꂽ�\�������X�^�~�i�c�ʗ��̊
	static constexpr float STAMINA_TIRED = 0.4f;

	// �X�^�~�i�Q�[�W�̕`��Ɋւ���萔
	static constexpr int STAMINA_GAUGE_X = 15;
	static constexpr int STAMINA_GAUGE_Y = 50;
	static constexpr int STAMINA_GAUGE_WIDTH = 260; 
	static constexpr int STAMINA_GAUGE_HEIGHT = 25;

	//���̍��W
	static constexpr int STAMINA_GAUGE_WIDTH_POS_X = STAMINA_GAUGE_WIDTH + STAMINA_GAUGE_X;
	static constexpr int STAMINA_GAUGE_WIDTH_POS_Y = STAMINA_GAUGE_Y + STAMINA_GAUGE_HEIGHT;


	static constexpr int STAMINA_GAUGE_INNER_OFFSET = 1; // �w�i�Ƃ̌���
	static constexpr int STAMINA_GAUGE_BG_COLOR = 0x000000;
	static constexpr int STAMINA_GAUGE_CURRENT_COLOR = 0x9d370e;
	static constexpr int STAMINA_GAUGE_CONSUMPTION_COLOR = 0xED784A;

	//�A�C�e���̑傫��
	static constexpr int ITEM_SCL = 60;



	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	//bool Init(SceneGame* parent) override;		

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void) override;	

	//�`�揈��
	virtual void Draw(void)override;

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void) override;		

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name=""></param>
	virtual void ProcessMove(void);

	/// <summary>
	/// ��ԕω��֐�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	void ChangePlayerState(SlimeBase::PLAYERSTATE state)override;

	/// <summary>
	/// �`���[�W�J�n
	/// </summary>
	/// <param name=""></param>
	virtual void ChargeStart(void);




	//�v���C���[���W�̃Q�b�^�[
	const VECTOR GetPos(void)const;

	/// <summary>
	/// �v���C���[��Ԃ̃Z�b�^�[
	/// </summary>
	/// <param name="playerState"></param>
	void SetPlayerState(const SlimeBase::PLAYERSTATE playerState);

	//�K�[�h�N�[���^�C���̃Z�b�^
	void SetGuardCoolTime(const int guardCooltime);

	//���W�Z�b�^
	void SetPos(const VECTOR pos) { pos_ = pos; }

	//�v���C���[�ƓG���������Ă��Ȃ��Ƃ��ɓ������Ă���Ƃ��ɁA������Ȃ��悤�ɂ���
	void SetMarginPos(SunUtility::DIR_3D marginDir);
	
	//�A�C�e���Ƃ������̍L�͈͍U����ԑJ��
	void ChangeWaidAtkState(const WAID_ATK waidAtk)override;
	
	


protected:

/// <summary>
/// ���W�̏�����
/// </summary>
	void SetParam(VECTOR _initPos,int _padNum,int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir) override;

	//�X�e�b�v�t���[���J�E���g
	int stepFrame_;

	//�X�e�b�v�����͂��̔���
	bool isStep_;

	//�K�[�h�J�E���g
	int guardCnt_;


	//�K�[�h�N�[���^�C������
	float guardCoolTimePercent_;	

	//�K�[�h�N�[���^�C���Q�[�W�̃T�C�Y
	int guardCoolTimeGaugeSize_;

	//�X�^�~�i�����
	float staminaConsum_;

	//����ʊ���
	float staminaConsumPercent_;

	//�X�^�~�i����
	float staminaPercent_;

	//�N���e�B�J���J�E���g
	int criticalCnt_;


	//�������ĂȂ��Ƃ��̍��W�����߂�p��Dir
	SunUtility::DIR_3D dirMargin_;

	int padNum_;		//�Q�[���p�b�h�̔ԍ�

	VECTOR shieldPos_;	//�K�[�h�G�t�F�N�g���W
	VECTOR shieldRot_;	//�K�[�h�G�t�F�N�g�p�x
	VECTOR shieldScl_;	//�K�[�h�G�t�F�N�g�傫��

	Parameta shieldPar_;	//�V�[���h�G�t�F�N�g�p�����^
	
	/// <summary>
	/// �f�o�b�O�p�֐�
	/// </summary>
	/// <param name=""></param>
	virtual void DrawDebug(void);

	/// <summary>
	/// �t���[���X�V����
	/// </summary>
	/// <param name=""></param>
	void FrameUpdate(void);


	/// <summary>
	/// �X�^�~�i�񕜏���
	/// </summary>
	void StaminaRecovery(void);

	/// <summary>
	/// �`���[�W���X�e�b�v�����߂鏈��
	/// </summary>
	/// <param name=""></param>
	void MoveDecide(void);
	/// <summary>
	/// �m�b�N�o�b�N����鑤�̏���
	/// </summary>
	/// <param name="attackDir"></param>
	virtual void KnockBack(void);

	/// <summary>
	/// �X�^�~�i�̉���
	/// </summary>
	/// <param name="staminaConsumPerFrame">1�t���[���̃X�^�~�i������</param>
	void StaminaLowLimit(float staminaConsumPerFrame);

	//��Ԃ��Ƃ̍X�V
	void StateUpdate(void)override;


#pragma region �񋓌^�̍X�V����
	//�N�[���^�C�����̏���
	void CoolUpdate(void);

	//�X�e�b�v��t���
	void ActionableUpdate(void);

	/// �X�e�b�v���̗͂P�\
	void StepKeepUpdate(void);

	/// <summary>
	/// �m�b�N�o�b�N����
	/// </summary>
	/// <param name=""></param>
	void KnockBuckUpdate(void);

	//�K�[�h����
	void GuardUpdate(void);

	//�A�C�e���i�L�͈͍U���j
	void WaidAtkUpdate(void);

	//�X�e�b�v����
	void StepUpdate(void);

	//���ߏ��
	void ChargeUpdate(void);

	//�U��
	void NormalAttackUpdate(void);

	//�N���e�B�J��
	void CriticalUpdate(void);

	//�K�[�h�N�[���^�C��
	void GuardCoolTimeConsum(void);

	//�A�C�e���̖��t���[������
	void ItemUpdate(void);

	//�A�C�e�����肵�Ă���̍X�V
	void GetItemUpdate(void);

	/// <summary>
	/// �l�̐U�ꕝ�����߂ď㉺������
	/// </summary>
	/// <param name="cnt">�㉺������J�E���g</param>
	/// <param name="moveNum">�㉺���������l</param>
	/// <param name="defaultNum">�����l</param>
	/// <param name="rangeNum">�U�ꕝ</param>
	/// <param name="speedNum">�㉺������X�s�[�h</param>
	void ShakeNum(int moveNum, int defaultNum, int rangeNum, int speedNum);

	UP_AND_DOWN updown_;

	//�����Ă�����
	void FallUpdate(void);

	//��������
	void RevivalUpdate(void);

	SlimeBase::PLAYERSTATE colState_;	//�v���C���[�������������̕ۊǗp�ϐ�

#pragma endregion

private:
};

