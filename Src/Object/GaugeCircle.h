#pragma once
#include<DxLib.h>
#include<vector>
#include<map>
class GaugeCircle
{
public:
	//�|���S����,�|���S���̕�����
	enum class GAUGE_TYPE
	{
		CHARGE
		,PARRY_K
		,PARRY_Y
	};
	static constexpr int DIV_NUM = 8;

	void Init(void);

	/// <summary>
	///�`��
	/// </summary>
	/// <param name="pos">�\���ʒu(�X�N���[���ʒu)</param>
	/// <param name="SIZEX">�\���T�C�YX</param>
	/// <param name="SIZEY">�\���T�C�YY</param>
	/// <param name="rate">�~�̕`��͈�(�ő�l��1.0�Ȃ̂Ŋ������v�Z���Ă���g������)</param>
	void Draw(GAUGE_TYPE type,VECTOR pos, int sizeX, int sizeY, float rate,bool isDraw);

	void Release(void);

	//�摜�n���h���Q�b�^
	int GetImg(GAUGE_TYPE type);

private:
	//�Q�[�W�摜�̃n���h��ID
	std::map<GAUGE_TYPE , int> textureGauge_;
	std::vector<VERTEX2D> vertexes_;
	std::vector<VERTEX2D> frameVertexes_;

	//�t���[���摜
	int textureFrame_;

	//�쐬�����|���S���̐�
	int polygonNum_;

	//���_�̍쐬
	void MakeCircleVertex(VECTOR pos, int sizeX, int sizeY, float rate);

	//�t���[��
	void MakeFrameVertex(VECTOR pos, int sizeX, int sizeY, float rate = 1.0f);

	//���_�ʒu�̌v�Z
	VECTOR MakeRotLocalPos(float rad, float sizeX, float sizeY);
};

