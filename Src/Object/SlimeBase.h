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

	//�萔
	//--------------------------------------
	//�ړ����
	static constexpr float MOVE_LIMIT = Stage::STAGE_ONE_SQUARE * 5.8 - Stage::STAGE_ONE_SQUARE / 2;

	//�X���C���̐F 
	static constexpr int BLUE_SLIME_COLOR = 0x5195E1;
	static constexpr int ORANGE_SLIME_COLOR = 0xED784A;

	//���a
	static constexpr float RADIUS = 25.0f;

	//���������Ƃ��̍���
	static constexpr float REVIVAL_HEIGHT_POS_Y = RADIUS * 5.0f;

	//�������W
	//����
	static constexpr VECTOR INIT_LEFT_POS = { -Stage::STAGE_ONE_SQUARE * 3, RADIUS, 0.0f };

	static constexpr VECTOR INIT_RIGHT_POS = { Stage::STAGE_ONE_SQUARE * 3,RADIUS,0.0f };
	//�d��
	//�d��
	static constexpr float DEFAULT_GRAVITY = 0.25f;

	//�ő�W�����v�p���[
	static constexpr float MAX_JUMP_POWER =10.0f;

	//�ړ��W�����v�p���[
	static constexpr float STEP_JUMP_POWER = 0.4f;

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


	//�L�͈͍U���W�����v�p���[
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//�L�͈͍U���N�[���^�C��
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//�L�͈͍U���`���[�W�ő�l
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 0.5f;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3f;
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

	//�O�p�`��Y�̍���
	static constexpr float HIGH = 12.5f;

	//���_���W
	static constexpr float VERTEX = 60.0f;

	//�`��֌W
	//*********************************************************

	//�`���[�W�Q�[�W
	//----------------------------------------------
	//���΍��W
	static constexpr VECTOR LOCAL_GAUGE_POS = { 0.0f,0.0f,50.0f };
	//�T�C�Y
	static constexpr int GAUGE_SIZE = 46;
	//----------------------------------------------

	//�p���B�N�[���^�C���Q�[�W
	static constexpr VECTOR PARRY_POS_BLUE = { -400.0f,50.0f,40.0f };
	static constexpr VECTOR PARRY_POS_ORANGE = { 400.0f,50.0f,40.0f };

	//�V�[���h�G�t�F�N�g
	static constexpr float SHIELD_SCALE = 10.0f;

	//�X���C�����f���̓_�ŃJ�E���g
	static constexpr int BLINK_INTERVAL = 3;
	static constexpr int BLINK_PATTERN = 2;

	//�X���C���̏�ԉ摜
	const std::string BLUE_NORMAL_FACE = "NormalK.png";
	const std::string BLUE_TIRED_FACE = "Tukare.png";
	const std::string BLUE_DAMAGE_FACE = "DamageK.png";
	const std::string BLUE_CHARGE_FACE = "ChargeK.png";
	const std::string BLUE_ATTACK_FACE = "AttackK.png";

	//�I�����W�X���C����ԉ摜
	const std::string ORANGE_NORMAL_FACE = "NormalY.png";
	const std::string ORANGE_TIRED_FACE = "TukareY.png";
	const std::string ORANGE_DAMAGE_FACE = "DamageY.png";
	const std::string ORANGE_CHARGE_FACE = "ChargeY.png";
	const std::string ORANGE_ATTACK_FACE = "AttackY.png";

	//�X���C���w�i�̉_�摜
	const std::string CLOWD_IMG = "Clowd.png";
	static constexpr double CLOWD_SCL = 1.5;

	//�X���C����ԉ摜�̍��W
	static constexpr int BLUE_SLIME_FACE_POS_X = 130;
	static constexpr int BLUE_SLIME_FACE_POS_Y = 144;

	//�I�����W�X���C����ԉ摜
	static constexpr int ORANGE_SLIME_FACE_POS_X = 1070;
	static constexpr int ORANGE_SLIME_FACE_POS_Y = 144;



	//�񋓌^
	enum class SLIME_FACE
	{
		NORMAL
		, DAMAGE
		, TIRED
		, CHARGE
		, ATTACK
		, MAX
	};


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
	virtual bool Init(SceneGame* _sceneGame,VECTOR _initPos,int _padNum,int _enemyNum,ModelManager::MODEL_TYPE _modelType,SunUtility::DIR_3D _dir);

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

	
	//�Q�b�^
	//********************************************************
	// �G�ƃv���C���[�̍��W�Q�b�^
	VECTOR GetPos(void);


	// �v���C���[�̕����Q�b�^�[
	SunUtility::DIR_3D GetDir(void);

	//�m�b�N�o�b�N�J�E���g�̃Z�b�^
	void SetKnockBack(const int knockBackCnt);

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="dmg">�_���[�W</param>
	/// <param name="invincibleCnt">���G����</param>
	void Damage(const int dmg, const int invincibleCnt);

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

	//�d�͂̃Z�b�^(�L�͈͍U���p)
	void SetGravityPow(const float gravityPow);

	//��̏�Ԃ̃Z�b�^
	void SetIsWeak(bool isWeak);


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

	//�v���C���[���A�C�e���̃|�C���^�[�������Ă��邩
	bool IsGetItemPtr(void);	

	//�v���C���[�̃A�C�e�����������Ă��邩�ǂ����̃Q�b�^
	bool IsItemAtk(void);

	//�U����ԏd�ݕt���Q�b�^
	int GetAtkPow(void);

	//�X�R�A���Z����
	void AddScore(const int score);

	//�v���C���[�̏�ԃQ�b�^
	PLAYERSTATE GetPlayerState(void) { return pState_; }

	//------------------------------------------------
	//�G�t�F�N�g���Đ��Z�b�^
	void SetIsItemGetEffect(const bool isItemGetEff);

	// �W�����v�͂̐ݒ�
	void SetJumpPower(float power);

	void SetGuardCoolTime(const int guardCooltime);

	//�v���C���[�̏�ԕύX(�Q�[���V�[���Ōp���X���C���z��ŕύX�ł���悤��)
	virtual void ChangePlayerState(PLAYERSTATE _pState);

	//CPU�̏�ԕύX
	virtual void ChangeEnemyState(ENEMYSTATE _state);

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
	std::map<SLIME_FACE, int>slimeFaceImgs_;	//�摜�i�[
	SLIME_FACE face_;	//�X���C�����
	Vector2 facePos_;	//��ԉ摜�̍��W

	//��ԉ摜�̔w�i
	int backSlimefaceImg_;	//�摜
	Vector2 backSlimefacePos_;	//���W

	//�`���[�WSE
	int hp_;			//�̗�
	int score_;			//�X�R�A
	float chargePer_;	//����
	float jumpPower_;	//�W�����v��
	bool isJump_;	//�W�����v������
	float gravityPow_;	//�d�͕ϐ�
	int atkPow_;	//��Ԃ��Ƃ̏d�˂�
	SunUtility::DIR_3D dir_;//�v���C���[�̕���

	int textureFrame_;	 //�t���[���g�摜

	bool isWeak_;	//��̏�ԃt���O

	bool isItemUse_;	//�A�C�e���g�p�t���O

	float hpPercent_;	//Hp�̊���

	float stamina_;		//�v���C���[�̃X�^�~�i

	int coolTime_;		//�N�[���^�C��

	//������֌W
	int fallCnt_;		//�����Ă��鎞�Ԃ̃J�E���g
	int fallDmg_;		//���������̃_���[�W
	int fallScore_;		//�������Ƃ��̃X�R�A���Z
	int revivalCnt_;	//�������J�E���g


	SunUtility::DIR_3D knockBackDir_;//�m�b�N�o�b�N����


	//�X�^�~�i����������
	bool isStaminaRecov_;

	//�X�^�~�i�񕜗�
	float staminaRecov_;

	//���G����
	int invincibleCnt_;

	//�L�͈͍U��
	int waidChargeCnt_;	//�L�͈͍U���̗��߃J�E���g
	WAID_ATK waidAtk_;	//�L�͈͍U�����
	int waidAtkCoolTime_;	//�L�͈͍U���̃N�[���^�C��
	float jumpCnt_;		//�L�͈͍U���̃W�����v�J�E���g

	//�t���[���J�E���g
	//----------------------------------------
	float frame_;
	int knockBackCnt_;	//�m�b�N�o�b�N�J�E���g
	float frameNum_;	//���߂��I�������̃t���[���ۊǗp
	bool isUseItem_;	//�A�C�e���g�p���

	//�v���C���[�֘A
	int enemyNum_;		//�e�X���C���ɂƂ��ēG�ł���X���C���̔ԍ�



	SlimeBase::PLAYERSTATE pState_;		//�v���C���[�̏��
	int guardCoolTime_;					//�K�[�h�N�[���^�C��

	//����������
	virtual void SetParam(VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir);

	/// <summary>
	/// �W�����v����
	/// </summary>
	void ProcessJump(void);

	

	//��Ԃ��Ƃ̍X�V
	virtual void StateUpdate(void);

	//�L�͈͍U���p�̏�ԕω��p
	virtual void ChangeWaidAtkState(const WAID_ATK waidAtk);

	//�W�����v
	void Jump(void);

	/// <summary>
	/// �N���e�B�J�������Ƃ��̊֐�
	/// </summary>
	//void CriticalAttack(void);

	/// <summary>
	/// �ʏ�_���[�W
	/// </summary>
	/// <param name=""></param>
	//void NormalAttack(void);

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

	//������\���O�p�`�`��
	void DrawDirTriangle(VECTOR _pos,SunUtility::DIR_3D _dir,int _color);

	//���ʂ̏�ԏ���
	//�A�C�e���Ď擾�܂ł̃J�E���g
	int itemReGetCnt_;
	
	Parameta itemGetPar_;	//�A�C�e���Q�b�g�����Ƃ�
	bool itemGetEffPlay_;
private:
};