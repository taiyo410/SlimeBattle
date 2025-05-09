#pragma once
#include<vector>
#include"../Utility/SunUtility.h"
#include"../Manager/SoundManager.h"
#include"../Common/Vector2.h"
#include"./SceneBase.h"
#include"../Common/CommonData.h"
#include"../Common/Parameta.h"
class SlimeBase;
class CommonData;
class RuleBase;
class Stage;
class ItemBase;
class Player;
class Player2;
class Enemy;
class SceneManager;
class SlimeManager;
class Grid;
class SceneGame :public SceneBase
{
public:
	//�萔
	//------------------------
	// �X���C���̃v���C���[�ԍ�
	static constexpr int PLAYER = 0;
	// �G�ԍ�
	static constexpr int ENEMY = 1;

	//�QP�ԍ�
	static constexpr int PLAYER2 = 1;


	//�X���C���̐�
	static constexpr int SLIME_NUM_MAX = 2;

	//�A�C�e���o���J�E���g
	static constexpr int ITEM_SPORN_CNT = SunUtility::DEFAULT_FPS * 10;

	//�A�C�e�����̍ő�
	static constexpr int ITEM_CNT_MAX = 2;

	//�񋓌^
	enum class BGM_TYPE
	{
		BGM
		,BGM2
	};

	enum class BG_CLOWD
	{
		ROBOKASS
		,RIHUJIN
		,MAX
	};

	

#pragma region �X�e�[�W�֌W
	
#pragma endregion

	

	//�f�t�H���g�R���X�g���N�^
	SceneGame(void);

	//�f�X�g���N�^
	~SceneGame(void);
	//�񋓌^
	//-------------------------------
	//�G�������
	enum class TYPE
	{
		PLAYER
		, ENEMY
	};

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Init(void)override;		

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void)override;		

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	void Draw(void)override;		

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void)override;		
	
	/// <summary>
	/// �^�C�v��ݒ肷��
	/// </summary>
	/// <param name=""></param>
	void SetType(void);

	//���[����ݒ肷��
	void SetRule(void);

	//���[���ɂ���ď�����ς���
	void DoChangeRule(void);

	bool GetIsHitItem(void);
	


	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="centerPos1">�I�u1�̒��S���W</param>
	/// <param name="size1">�I�u1�̃T�C�Y</param>
	/// <param name="centerPos2">�I�u2�̒��S���W</param>
	/// <param name="size2">�I�u2�̃T�C�Y</param>
	/// <returns></returns>
	//���̂Ƌ��̂̓����蔻��
	bool IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	//�A�C�e���̎擾
	bool IsHitItem(void);


	//�A�C�e���o��
	void ProcessItem(void);

	//�U���͂��ׂ�
	void PlAtkPowCompare(int pl1Atknum, int pl2Atknum);


#pragma region �Q�b�^�[
#pragma region �v���C���[�P
	/// <summary>
	/// �v���C���[����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SunUtility::DIR_3D GetPlayerDir(void);


	/// <summary>
	/// �v���C���[���W���Q�[���V�[������Q�b�g����Ƃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetPlayerPos(void);

	/// <summary>
	/// �v���C���[�̏�ԃQ�b�^�[
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CommonData::PLAYERSTATE GetPlayerState(void);

	//�v���C���[��HP�Q�b�^
	float GetPlayerHpPercent(void);

	//�v���C���[�̃X�R�A�Q�b�^
	int GetPlayerScore(void);

	//���G����
	int GetPlayerInvincible(void);

	bool isHitItem_;	//�A�C�e���ɓ����������ǂ���

#pragma endregion
#pragma region �v���C���[�Q
	/// <summary>
	/// �v���C���[����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SunUtility::DIR_3D GetPlayer2Dir(void);


	/// <summary>
	/// �v���C���[���W���Q�[���V�[������Q�b�g����Ƃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetPlayer2Pos(void);

	/// <summary>
	/// �v���C���[�̏�ԃQ�b�^�[
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CommonData::PLAYERSTATE GetPlayer2State(void);

	//�v���C���[2��HP�Q�b�^
	float GetPlayer2HpPercent(void);

	//�v���C���[2�̃X�R�A�Q�b�^
	int GetPlayer2Score(void);

	//���G����
	int GetPlayer2Invincible(void);

	Parameta hitEffectPar_;	//�G�t�F�N�g�̃p�����^

#pragma endregion


#pragma region �G
	/// <summary>
	/// �G���W���Q�[���V�[������Q�b�g����Ƃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetEnemyPos(void);

	/// <summary>
	/// �G����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SunUtility::DIR_3D GetEnemyDir(void);

	/// <summary>
	/// /�������Ă��邩�ǂ����̃Q�b�^�[
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetIsCollision(void);


	/// <summary>
	/// �G�̏�ԃQ�b�^
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CommonData::ENEMYSTATE GetEnemyState(void);

	//�G��HP�Q�b�^
	float GetEnemyHpPercent(void);

	//�G�̃X�R�A�Q�b�^
	int GetEnemyScore(void);

	//�G�̖��G����
	int GetEnemyInvincible(void);

	int itemCnt_;		//�A�C�e���̌�

	ItemBase* GetValidItem(void);
#pragma endregion

	
	

#pragma endregion







private:
	//�|�C���^�[�錾
	RuleBase* ruleBase_;
	SlimeBase* slime_[SLIME_NUM_MAX];
	SlimeBase* slimes_;
	SlimeManager* slimeMng_;
	Stage* stage_;
	Player* player_;
	Player2* player2_;
	Enemy* enemy_;
	std::vector<ItemBase*> items_;
	Grid* grid_;
	SoundManager* sound_;
	//�����o�[�ϐ�
	//-------------------------
	//�w�i
	int bgImage_;		//�w�i�摜�i�[

	int roboKass_;		//���{�J�X�摜

	int cloudImage_;		//�_�摜
	Vector2 cloudPos_;	//�_�摜�p

	BG_CLOWD bgClowd_;	//�_�ɏ������̉摜�̎��

	Vector2 bgClowdPos_;	//���W

	//�G�t�F�N�g
	int hitEffectId_;	//�q�b�g�G�t�F�N�g��Id

	int itemSpornCnt_;		//�A�C�e���o���J�E���g

	int hitSE_;			//������������SE

	int gamebgm_;		//BGM�i�[
	int gamebgm2_;		//�ǂ��炩�̗̑͂������ȉ��ɂȂ�����

	//�v���C���[�����ԍ�
	int slimeWinNum_;

	//�����ԍ�
	int slimeLoseNum_;	



	VECTOR hitEffectPos_;	//�q�b�g�G�t�F�N�g�̍��W
	VECTOR hitEffectscl_;	//�q�b�g�G�t�F�N�g�̑傫��
	VECTOR hitEffectRot_;	//�q�b�g�G�t�F�N�g�̊p�x
	//�G�������
	CommonData::TYPE type_[SLIME_NUM_MAX];

	//���[��
	CommonData::RULE rule_;

	//BGM�؂�ւ��p
	BGM_TYPE bgm_;

	//BGM�؂�ւ��t���O
	bool bgmFlg_;
	

	//�������Ă��邩
	bool isCollision_;
	/// <summary>
	/// �f�o�b�O�p�֐�
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);

	/// <summary>
	/// PVE�p�̃m�b�N�o�b�N����
	/// </summary>
	/// <param name="playerDir">�v���C���[�̕���</param>
	/// <param name="playerState">�v���C���[�̏��</param>
	/// <param name="enemyDir">�G�̕���</param>
	/// <param name="enemyState">�G�̏��</param>
	void PVEKnockBack(SunUtility::DIR_3D playerDir, CommonData::PLAYERSTATE playerState
		, SunUtility::DIR_3D enemyDir, CommonData::ENEMYSTATE enemyState);

	/// <summary>
	/// PVP�p�̃m�b�N�o�b�N
	/// </summary>
	/// <param name="plLoseNum">�������ق��̔ԍ�</param>
	void PVPKnockBack(int plLoseNum);

	//BGM�؂�ւ�
	void ChangeBgm(BGM_TYPE bgm);
};
