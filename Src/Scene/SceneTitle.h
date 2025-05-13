//#pragma once
#include "string"
#include"../Common/Vector2.h"
#include"../Utility/SunUtility.h"
#include"SceneBase.h"
#include"../Common/CommonData.h"
class InputManager;
class CommonData;
class SoundManager;
class Grid;
class RuleBase;
class SceneTitle : public SceneBase
{
public:
	//�萔
	static constexpr int MOVE_SPEED_X = 1;
	static constexpr int KINTOUN_MOVE_SPEED_X = 10;

	//���[�h�摜�S�̃T�C�Y
	static constexpr int MODE_IMG_SIZE_X = 320;
	static constexpr int MODE_IMG_SIZE_Y = 60;
	//���[�h�摜�̕`��T�C�Y
	static constexpr int MODE_DRAW_SIZE_X = 180;
	static constexpr int MODE_DRAW_SIZE_Y = 60;

	//���[���摜�̕`��T�C�Y
	static constexpr int RULE_DRAW_SIZE_X = 180;
	static constexpr int RULE_DRAW_SIZE_Y = 60;

	//�I���摜�̑S�̃T�C�Y
	static constexpr int SELECT_SIZE_X = 240;
	static constexpr int SELECT_SIZE_Y = 60;

	static constexpr int MODE_GOAL_MAX = 272;
	static constexpr int RULE_GOAL_MAX = 275;

	//���[�h�摜�؂�ւ��X�s�[�h
	static constexpr int MODE_MOVE_SPEED = 10;

	//�^�K�������̃A�j���[�V������
	static constexpr int TAGAME_ANIME_ALL = 3;
	static constexpr int TAGAME_ANIME_DIR = 1;
	static constexpr int ARROW_SIZE_X = 80;
	static constexpr int TAGAME_SIZE_Y = 100;
	static constexpr float ANIM_SPEED_DEFAULT = 0.25f;
	static constexpr float TAGAME_MOVE_SPEED = 1.0f;
	static constexpr int ARROW_MOVE_FRAME = static_cast<int>(SunUtility::DEFAULT_FPS * 0.5f);

	//�摜
	const std::string CIRCLE_SLIME_IMG = "CircleSlime.png";
	const std::string BG_IMG = "BgImage.png";
	const std::string BG_CLOWD_IMG = "BgMoveImage.png";
	const std::string GOLD_CLOWD_IMG = "kintoun.png";
	const std::string ROGO_IMG = "Rogo.png";
	const std::string MODE2_IMG = "mode2.png";
	const std::string RULE_IMG = "rule.png";
	const std::string SELECT_IMG = "Select.png";
	const std::string ARROW_IMG = "arrow.png";

	//���̊p�x
	//�E
	static constexpr float RIGHT_DEG = 0.0;
	static constexpr float LEFT_DEG = 180.0 * DX_PI_F / 180;


	//�񋓌^
	enum class MODE
	{
		PVP
		,PVE
		,MAX
	};
	
	//�萔
	static constexpr float ROT_SPEED = 0.005f;

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�����������@�@false:�������~�܂�</returns>
	bool Init(void) override;	

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void) override;	

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	void Draw(void) override;	
	/// <summary>
	/// �J������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:����������	false:�������~�܂�</returns>
	bool Release(void) override;	

private:
	//�|�C���^�[�錾
	SoundManager* sound_;
	//RuleBase* ruleBase_;
	//�����o�[�ϐ�
	int circleSlimeImage_;		//�^�C�g���摜�̊i�[�̈�
	int bgImage_;		//�^�C�g���摜�̊i�[�̈�
	int kintounImage_;		//�^�C�g���摜�̊i�[�̈�
	int rogoImage_;		//���S�摜
	int cloudImage_;		//�_�摜
	int modeImage_;		//���[�h�I��p�摜
	int ruleImage_;		//���[�h�I��p�摜
	int selectImage_;	//�I���摜
	int tagameImg_[TAGAME_ANIME_ALL];		//�^�K������
	int arrowImg_;		//���


	CommonData::MODE mode_;		//���[�h�\���p
	CommonData::RULE rule_;				//���[���\���p

	bool moveFlg_;	//���������̃t���O	true:������

	float rot_;		//��]�p

	int cntAnim_;	//�A�j���[�V�����J�E���g
	float speedAnim_;	//�A�j���[�V�����X�s�[�h

	int moveframe_;		//�^�K�������̈ړ��J�E���g

	Vector2 cloudPos_;	//�_�摜�p
	Vector2 kintounPos_;	//�_�摜�p
	Vector2 modeImgRectPos_;	//���S��`���W
	Vector2 ruleImgRectPos_;	//���S��`���W
	Vector2 modeGoalPos_;		//�ǂ��܂œ��������̍��W
	Vector2 ruleGoalPos_;		//�ǂ��܂œ��������̍��W
	Vector2 selectPos_;			//�I���摜���W
	Vector2 startPos_;			//�^�K�������������n�߂���W

	Vector2 arrowPos_;			//�^�K�����W
	double arrowRot_;			//�^�K��

		//�Z���N�g
	CommonData::SELECT select_;

	//�Z���N�g�X�V
	void ModeUpdate(void);

	//���[�h�X�V�@
	void RuleUpdate(void);

	void ChangeSelect(CommonData::SELECT select);
	void ChangeRule(const CommonData::RULE rule);
	void ChangeMode(const CommonData::MODE mode);

	//���̈ړ�
	void MoveArrow(int move);



	/// <summary>
	/// �f�o�b�O�p�̊֐�
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);
};
