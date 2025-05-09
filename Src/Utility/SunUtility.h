#pragma once
#include<DxLib.h>
#include<string>
#include<vector>

class Vector2;
class Vector2F;
class SunUtility
{
	//�����o�[�ϐ�
public:
	//�萔
	static constexpr int DEFAULT_FPS = 60;

	//�p�[�Z���g
	static constexpr int PERCENT_MAX = 100;
	static constexpr float PERCENT_MAX_F = 1.0f;

	//�f���^�^�C��
	static constexpr float DELTA_TIME = 1.0f / SunUtility::DEFAULT_FPS;

	//���W�[��
	static constexpr VECTOR VECTOR_ZERO = { 0.0f,0.0f,0.0f };
	//2D����
	enum class DIR_2D
	{
		UP
		,DOWN
		,LEFT
		,RIGHT
		,MAX
	};

	//3D����
	enum class DIR_3D
	{
		FLONT
		,BACK
		,RIGHT
		,LEFT
		,MAX
	};

	

	/// <summary>
	/// ������̕���
	/// </summary>
	/// <param name="line"></param>
	/// <param name="delimiter"></param>
	/// <returns></returns>
	static std::vector<std::string>Split(std::string& line, char delimiter);

	//�l�̌ܓ�
	static int Round(float value);
	//�l�̌ܓ��p�̊֐�(Vector2)
	static Vector2 Round(Vector2F value);

	//���̂Ƌ��̂̓����蔻��
	bool IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	

	//�����ɂ����������4�����ɕς���
	static DIR_3D ToDirection(VECTOR dir);

	//�I���W�i���x�N�g����������ׂ��Ƃ�ɕς���
	static VECTOR ToDirection(DIR_3D dir);

	//��r
	static bool EqualsVZero(const VECTOR& v1);
private:

};
