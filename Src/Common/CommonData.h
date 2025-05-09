#pragma once
class SceneTitle;
class ModelManager;
class CommonData
{
public:
	//�萔
	static constexpr int TYPE_MAX = 2;


	//�񋓌^
		//�G�������
	enum class TYPE
	{
		PLAYER1
		,PLAYER2
		,ENEMY
		,MAX
	};

	//�Z���N�g���
	enum class SELECT
	{
		MODE
		,RULE
	};

	//���[�h���
	enum class MODE
	{
		PVE
		,PVP
		,MAX
	};
	//���[�����
	enum class RULE
	{
		HP
		, SCORE
	};

	//�����p�^�[��
	enum class WINPATTERN
	{
		P1WIN
		,P2WIN
		,DRAW
	};

	//����������
	bool DataInit(void);

	//���[�h�J��
	void ModeUpdate(void);

	//�����p�^�[���Z�b�^
	void SetWinPattern(WINPATTERN win);

	//�����p�^�[���Q�b�^
	WINPATTERN GetWinPattern(void);
	//�C���X�^���X�̉��
	void ReleaseData(void);

	//�V���O���g����
	//------------------------------
	static void CreateData(void);

	//�O���ŃC���X�^���X�𗘗p�\�ɂ��邽�߂�
	//�C���X�^���X�ŕԂ��֐���p��
	static CommonData& GetData(void);

	//�C���X�^���X�̍폜
	void Destroy(void);

	//�G������ʂ̃Q�b�^
	MODE GetMode(void);

	//���[���Z�b�^
	RULE GetRule(void);

	//���[�h�̃Z�b�^�[
	void SetMode(MODE value);

	//���[���̃Z�b�^
	void SetRule(RULE value);
#pragma region �X�R�A�֌W

	//�v���C���[�̃X�R�A�Z�b�^
	void SetPlayerScore(const int playerScore);

	//�G�̃X�R�A�Z�b�^
	void SetEnemyScore(const int enemyScore);

	//�v���C���[
	int GetPlayerScore(void);

	//�G
	int GetEnemyScore(void);
#pragma endregion


#pragma region HP���[���֌W

#pragma endregion

private:
	//�����o�[�ϐ�
	TYPE type_[TYPE_MAX];

	RULE rule_;

	MODE mode_;

	WINPATTERN win_;

	int playerScore_;	//�v���C���[�̃X�R�A

	int enemyScore_;	//�G�̃X�R�A



	//�|�C���^�[�錾
	SceneTitle* sceneTitle_;
	ModelManager* model_;

	//�V���O���g����
	//�f�t�H���g�R���X�g���N�^
	CommonData(void);
	//�f�X�g���N�^
	~CommonData(void);


	//�R�s�[�R���X�g���N�^�𗘗p�s�ɂ���
	CommonData(const CommonData& ins);

	//�ÓI�ȃC���X�^���X������
	static CommonData* data_;
};
