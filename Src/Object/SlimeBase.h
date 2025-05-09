#pragma once
#include<DxLib.h>
#include<map>
#include"./Stage.h"
#include"../Common/Vector2.h"
#include"../Common/CommonData.h"
#include"../Common/Parameta.h"
#include"../Manager/SoundManager.h"
#include"../Manager/ModelManager.h"
#include"../Utility/SunUtility.h"
class SceneGame;
class SoundManager;
class ModelManager;
class ItemBase;
class Player;
class GaugeCircle;
class SlimeBase
{
public:
	//�A�j���[�V�����̏I���
	static constexpr float ANIM_END = 59.0f;

	//�ړ����
	static constexpr float MOVE_LIMIT = Stage::STAGE_ONE_SQUARE * 5.8 - Stage::STAGE_ONE_SQUARE / 2;
	enum class SLIME_FACE
	{
		NORMAL
		, DAMAGE
		, TIRED
		, CHARGE
		, ATTACK
	};
	//�萔
	//--------------------------------------
	
	// 
	//���a
	static constexpr float RADIUS = 25.0f;
	//�d��
	static constexpr float DEFAULT_GRAVITY = 0.25f;

	//�ő�W�����v�p���[
	static constexpr float MAX_JUMP_POWER =10.0f;

	//�ړ��W�����v�p���[
	static constexpr float STEP_JUMP_POWER = 0.4;

	//�t���[������
	static constexpr float FLAME_TIME = 1 / 60;

	//�X�s�[�h
	static constexpr float SPEED = 15.0f;

	//�N���e�B�J���_���[�W
	static constexpr int CRITICAL_DAMAGE = 5;

	//�ʏ�_���[�W
	static constexpr int NORMAL_DAMAGE = 2;

	//�t���[����l
	static constexpr float FRAME_DEFAULT = 4.0f;

	//�t���[���ő�l
	static constexpr float FRAME_MAX = 12.0f;

	//�X�^�~�i�ő�l
	static constexpr float STAMINA_MAX = 60.0f;

	//�X�^�~�i�񕜃X�s�[�h(�P�t���[���ɉ񕜂����)
	static constexpr float STAMINA_RECOVE_SPEED = 0.25f;

	//�X�^�~�i�񕜗ʍő�l
	static constexpr float STAMINA_RECOV_MAX = 1.0f;

	//�`���[�W�X�s�[�h
	static constexpr float CHARGE_SPEED = 0.2f;

	////������ԃt���[����
	static constexpr int KNOCKBUCK_FRAME = 12;

	//�v���C���[���p���B�����Ƃ��ɐ�����ԃt���[����
	static constexpr int KNOCKBACK_PARRY = 5;

	//�X�e�b�v��SE�̉���
	static constexpr int STEP_VOL = SoundManager::VOLUME_MAX * 50 / 100;

	//���G����
	static constexpr int INVINCIBLE_TIME = SunUtility::DEFAULT_FPS * 1;
	
	//�G�ƃv���C���[�̍��W�}�[�W��
	static constexpr float POS_MARGIN = 5.0f;

	//�A�j���[�V�����ő厞��
	static constexpr float ANIM_CNT_MAX = 60;

	//�A�j���[�V�����f�t�H���g�̑��x
	static constexpr float ANIM_SPEED_DEFAULT = SunUtility::DEFAULT_FPS;



	//�L�͈͍U���W�����v�p���[
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//�L�͈͍U���N�[���^�C��
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//�L�͈͍U���`���[�W�ő�l
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 0.5;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//�L�͈͍U���̗������p�̏d��
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;

	//�L�͈͍U�������蔻�蒲���p
	static constexpr float WAID_ATK_COLMARGIN = 1.3f;

	//�L�͈͍U�����߂̃G�t�F�N�g�̑傫��
	static constexpr float WAID_CHARGE_EFFECT_SCL = 30;

	//�A�C�e���Ď擾�܂ł̎���
	static constexpr int ITEM_REGET_CNT = 2;

	//���������̃_���[�W�̑�����
	static constexpr int FALL_DMG_INCREASE = 10;

	//���������̃_���[�W�f�t�H���g
	static constexpr int FALL_DMG_DEFAULT = 20;

	//���������̃X�R�A���Z�f�t�H���g
	static constexpr int FALL_SCORE_DEFAULT = 100;

	//���������̃X�R�A���Z������
	static constexpr int FALL_SCORE_INCREASE = 50;

	//SE�̉���
	static constexpr int SE_VOL = 50;

	//�񋓌^
	enum class PLAYERSTATE
	{
		COOL
		, DEBUFF
		, ACTIONABLE
		, STEPKEEP
		, STEP
		, CHARGE
		, NORMALATTACK
		, CRITICALATTACK
		, KNOCKBACK
		, GUARD
		, WAIDATTACK
		, FALL
		, REVIVAL

	};

	//�񋓌^
	enum class ENEMYSTATE
	{
		NONE
		, THINK
		, DEBUFF
		, MOVE
		, STEP
		, CHARGE
		, KNOCKBACK
		, KNOCKBACkSMALL
		, NORMALATTACK
		, WAIDATTACK
		, CRITICALATTACK
		, FALL
		, REVIVAL
	};




	//�L�͈͍U��
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};

	//�񋓌^
	enum class ANIM
	{
		IDLE
		,STEP
		,CHARGE
		,ATTACK
		,MAX
	};

	enum class P_OR_E
	{
		PLAYER
		,ENEMY
	};
	

	

	//�f�t�H���g�R���X�g���N�^
	SlimeBase(void);

	//�f�X�g���N�^
	~SlimeBase(void);

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	virtual bool Init(SceneGame* _sceneGame);

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
	/// <returns></returns>
	virtual bool Release(void);

	//�v���C���[�̍��W�̍��W�Q�b�^�[

	/// <summary>
	/// �G�ƃv���C���[�̍��W�Q�b�^
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetPos(void);

	/// <summary>
	/// �v���C���[�̕����Q�b�^�[
	/// </summary>
	/// <param name=""></param>
	/// <returns>�v���C���[�̕���</returns>
	SunUtility::DIR_3D GetDir(void);

	//�m�b�N�o�b�N�J�E���g�̃Z�b�^
	void SetKnockBack(const int knockBackCnt);

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="dmg">�_���[�W</param>
	/// <param name="invincibleCnt">���G����</param>
	void Damage(const int dmg, const int invincibleCnt);

	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump(void);

	//�\���p�X�R�A�Q�b�^
	int GetScore(void);

	//���G���ԃZ�b�^
	void SetInvincible(const int invincibleCnt);
	//���G���ԃQ�b�^�[
	int GetInvincibleCnt(void);

	//�N�[���^�C���̃Z�b�^
	void SetCoolTime(const int coolTime);

	//���W�Z�b�^
	void SetPos(const VECTOR pos);

	//HP�Q�b�^
	float GetHpPercent(void);

	//��̏�Ԃ̃Q�b�^
	bool GetIsWeak(void);

	//�X���C���ԍ��̎擾
	int GetSlimeNum(void);

	//�d�͂̃Z�b�^(�L�͈͍U���p)
	void SetGravityPow(const float gravityPow);

	//��̏�Ԃ̃Z�b�^
	void SetIsWeak(bool isWeak);

	/// <summary>
	/// �W�����v�͂̐ݒ�
	/// </summary>
	/// <param name="power"></param>
	void SetJumpPower(float power);

	/// <summary>
	/// �d�͂�������
	/// </summary>
	void AddGravity(float gravityPow);

	//�A�C�e���̃|�C���^�̃Z�b�g
	void SetItem(ItemBase* item);

	//�A�C�e���g�p��ԃZ�b�^
	void SetIsUse(const bool isUseItem);


	//�A�C�e���Ď擾�J�E���g�Q�b�^
	int GetItemReGetCnt(void);

	

	//�L�͈͍U���`���[�W�J�E���g�Q�b�^
	int GetChargeCnt(void);

	//�L�͈͍U���`���[�W�J�E���g�Z�b�^
	void SetChargeCnt(int cnt);

	WAID_ATK GetWaidAtkState(void);

	bool GetIsUse(void);

	//�L�͈͍U���̔��a�Q�b�^
	float GetWaidCol(void);

	//�v���C���[���A�C�e���̃|�C���^�[�������Ă��邩
	bool IsGetItemPtr(void);	

	//�v���C���[�̃A�C�e�����������Ă��邩�ǂ����̃Q�b�^
	bool IsItemAtk(void);

	//�U����ԏd�ݕt���Q�b�^
	int GetAtkPow(void);

	/// <summary>
	/// ��ԕω��֐�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual void ChangeState(PLAYERSTATE state);

	//�X�R�A���Z����
	void Score(const int score);

	//�G�t�F�N�g���Đ��Z�b�^
	void SetIsItemGetEffect(const bool isItemGetEff);

	ModelManager::MODEL_TYPE GetModelType(void);




protected:
	//�|�C���^
	//SlimeManager& slimeMng_;
	SceneGame* sceneGame_;
	ItemBase* item_;
	GaugeCircle* gaugeCircle_;
	SoundManager* sound_;
	ModelManager* model_;
	ModelManager::MODEL_TYPE modelType_;


	VECTOR pos_;			//���W

	VECTOR rot_;			//�p�x

	VECTOR scale_;			//�傫���ݒ�

	VECTOR revivalPos_;		//����������W
	//���f���t�@�C����
	std::string modelFileName_;

	int modelHandle_;	//���f���n���h��

	//�X���C���̏�ԉ摜
	std::map<SLIME_FACE, int>slimeFaceImg_;
	SLIME_FACE face_;	//�X���C�����
	Vector2 facePos_;	//��ԉ摜�̍��W

	//��ԉ摜�̔w�i
	int backSlimefaceImg_;	//�摜
	Vector2 backSlimefacePos_;	//���W

	//�A�j���[�V�����̃A�^�b�`�ԍ�
	int animAttachNo_;

	//�A�j���ԍ�
	int animNo_;

	//�A�j���J�ڗp
	ANIM anim_;

	//�A�j���[�V�����̑��Đ�����
	float animTotalTime_;

	//�Đ����̃A�j���[�V��������
	float stepAnim_;

	//�A�j���[�V�������x
	float speedAnim_;

	//�A�j���I���������
	bool endAnim_;


	//�X�e�b�vSE�̊i�[
	int stepSE_;

	//�U��SE
	int attackSE_;

	//�`���[�WSE
	int chargeSE_;
	//�L�͈͍U���̃p�����^



	//���ߊ���
	float chargePer_;
	float gaugeRate_;	//�f�o�b�O�p�̃Q�[�W�ω�

	int atkPow_;	//��Ԃ��Ƃ̏d�˂�

	int textureFrame_;	 //�t���[���g�摜

	//�W�����v��
	float jumpPower_;

	float gravityPow_;	//�d�͕ϐ�

	//�W�����v������
	bool isJump_;

	bool isWeak_;	//��̏�ԃt���O

	bool isItemUse_;	//�A�C�e���g�p�t���O

	//�̗�
	int hp_;

	//�X�R�A
	int score_;
	//Hp�̊���
	float hpPercent_;	

	//�v���C���[�̃X�^�~�i
	float stamina_;

	//�N�[���^�C��
	int coolTime_;

	//�����Ă��鎞�Ԃ̃J�E���g
	int fallCnt_;

	//���������̃_���[�W
	int fallDmg_;

	//�������Ƃ��̃X�R�A���Z
	int fallScore_;

	//�������J�E���g
	int revivalCnt_;

	P_OR_E judge_;		//�v���C���[���G�l�~�[��


	//�v���C���[�̕���
	SunUtility::DIR_3D dir_;

	//�m�b�N�o�b�N����
	SunUtility::DIR_3D knockBackDir_;


	

	//�X�^�~�i����������
	bool isStaminaRecov_;

	//�X�^�~�i�񕜗�
	float staminaRecov_;

	//���G����
	int invincibleCnt_;


	int waidChargeCnt_;	//�L�͈͍U���̗��߃J�E���g
	

	WAID_ATK waidAtk_;
	//�L�͈͍U��
	


	int waidAtkCoolTime_;	//�L�͈͍U���̃N�[���^�C��
	int slimeNum_;		//�X���C���ԍ�
	
	float jumpCnt_;		//�L�͈͍U���̃W�����v�J�E���g




	//�t���[���J�E���g
	//----------------------------------------
	//�t���[��
	float frame_;

	//�m�b�N�o�b�N�J�E���g
	int knockBackCnt_;	

	//���߂��I�������̃t���[���ۊǗp
	float frameNum_;

	bool isUseItem_;	//�A�C�e���g�p���

	//����������
	virtual void SetParam(void);

	/// <summary>
	/// �W�����v����
	/// </summary>
	void ProcessJump(void);

	

	//��Ԃ��Ƃ̍X�V
	virtual void StateUpdate(void);

	//�L�͈͍U���p�̏�ԕω��p
	virtual void ChangeWaidAtkState(const WAID_ATK waidAtk);

	


	

	/// <summary>
	/// �N���e�B�J�������Ƃ��̊֐�
	/// </summary>
	void CriticalAttack(void);

	/// <summary>
	/// �ʏ�_���[�W
	/// </summary>
	/// <param name=""></param>
	void NormalAttack(void);

	/// <summary>
	/// �������Ƃ̏���
	/// </summary>
	/// <param name=""></param>
	void DirUpdate(SunUtility::DIR_3D dir);


	//�t���[�����
	void FrameLimit(void);

	//�L�͈͍U���p�����^
	Parameta waidAtkPar_;

	//�L�͈͍U���`���[�W�p�G�t�F�N�g
	Parameta waidChargePar_;

	//�ړ������@
	bool MoveLimit(void);

	//���G���Ԍ��Z����
	void InvincibleConsum(void);

	//���G���ԃQ�b�^
	int GetInvincible(void);

	//�n��
	void Ground(void);
	//�X�e�[�W��ɂ��邩�ǂ���
	bool isInStage_;

	//�A�j���[�V��������
	void Animation(void);
	
	//�A�j���[�V�������I��������̏���
	void EndAnimation(void);
	
	//������\���O�p�`�`��
	void DrawDirTriangle(VECTOR _pos,SunUtility::DIR_3D _dir,int _color);

	//���ʂ̏�ԏ���
	//�A�C�e���Ď擾�܂ł̃J�E���g
	int itemReGetCnt_;
	
	Parameta itemGetPar_;	//�A�C�e���Q�b�g�����Ƃ�
	bool itemGetEffPlay_;

	

private:
	


};