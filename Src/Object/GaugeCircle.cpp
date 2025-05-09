#include"../Application.h"
#include "GaugeCircle.h"

void GaugeCircle::Init(void)
{
	textureGauge_[GAUGE_TYPE::CHARGE] = LoadGraph((Application::PATH_IMAGE + "Circle.png").c_str());
	textureGauge_[GAUGE_TYPE::PARRY_K] = LoadGraph((Application::PATH_IMAGE + "ParryK.png.").c_str());
	textureGauge_[GAUGE_TYPE::PARRY_Y] = LoadGraph((Application::PATH_IMAGE + "ParryY.png.").c_str());

	textureFrame_ = LoadGraph((Application::PATH_IMAGE + "CircleFrame.png").c_str());
	
}

void GaugeCircle::Draw(GAUGE_TYPE type, VECTOR pos, int sizeX, int sizeY, float rate,bool isDraw)
{
	if (isDraw)
	{
		//�|���S�����쐬(�t���[��)
		MakeFrameVertex(pos, sizeX, sizeY);
	}
	
	//�|���S���̍쐬(�Q�[�W)
	MakeCircleVertex(pos, sizeX, sizeY, rate);
	
	

	//�r���{�[�h�̂悤�ɕ`�悷��(�Q�[�W)
	DrawPolygon2D(vertexes_.data(), polygonNum_, textureGauge_[type], true);

	if (isDraw)
	{
		//�r���{�[�h�̂悤�ɕ`�悷��(�t���[��)
		DrawPolygon2D(frameVertexes_.data(), 8, textureFrame_, true);
	}


	
	
	
}

void GaugeCircle::Release(void)
{

}

int GaugeCircle::GetImg(GAUGE_TYPE type)
{
	return textureGauge_[type];
}

void GaugeCircle::MakeCircleVertex(VECTOR pos, int sizeX, int sizeY, float rate)
{

	vertexes_.clear();

	//�����p�x(3.14*2/8=�ŃO���[�ł�����45�x)
	float divRad = DX_TWO_PI_F / static_cast<float>(DIV_NUM);

	//�쐬����ő�p�x(360���̎�rate=1�A180���̂Ƃ�rate=0.5)
	float endRad = DX_TWO_PI_F * rate;

	//�|���S�����̃��Z�b�g
	polygonNum_ = 0;

	float rad = 0.0f;
	float sizeXF = static_cast<float>(sizeX);
	float sizeYF = static_cast<float>(sizeY);

	//���[�v�Ń|���S��(���_)�����
	while (polygonNum_ < DIV_NUM)
	{
		VECTOR pos1 = MakeRotLocalPos(rad, sizeXF, sizeYF);
		rad += divRad;
		//����l
		if (rad > endRad)
		{
			rad = endRad;
		}
		VECTOR pos2 = MakeRotLocalPos(rad, sizeXF, sizeYF);


		VERTEX2D vertex = VERTEX2D();

		//���S���W
		vertex.pos = pos;
		vertex.pos.z = 0.0f;
		vertex.u = 0.5f;
		vertex.v = 0.5f;
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);

		//���̒��_

		vertex.pos = VAdd(pos, pos1);
		vertex.pos.z = 0.0f;
		vertex.u = (pos1.x + sizeXF) / (sizeXF + sizeXF);
		vertex.v = (pos1.y + sizeYF) / (sizeYF + sizeYF);
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);


		vertex.pos = VAdd(pos, pos2);
		vertex.pos.z = 0.0f;
		vertex.u = (pos2.x + sizeXF) / (sizeXF + sizeXF);
		vertex.v = (pos2.y + sizeYF) / (sizeYF + sizeYF);
		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;
		vertexes_.emplace_back(vertex);

		//�|���S�����̑���
		polygonNum_++;
		if (rad >= endRad)
		{
			//�쐬����ő�p�x�܂œ��B�����̂ŏ����I��
			break;
		}

	}


}

void GaugeCircle::MakeFrameVertex(VECTOR pos, int sizeX, int sizeY, float rate)
{
		frameVertexes_.clear();

		//�����p�x(3.14*2/8=�ŃO���[�ł�����45�x)
		float divRad = DX_TWO_PI_F / static_cast<float>(DIV_NUM);

		//�쐬����ő�p�x(360���̎�rate=1�A180���̂Ƃ�rate=0.5)
		float endRad = DX_TWO_PI_F * rate;

		//�|���S�����̃��Z�b�g
		int polygonNum = 0;

		float rad = 0.0f;
		float sizeXF = static_cast<float>(sizeX);
		float sizeYF = static_cast<float>(sizeY);

		//���[�v�Ń|���S��(���_)�����
		while (polygonNum < DIV_NUM)
		{
			VECTOR pos1 = MakeRotLocalPos(rad, sizeXF, sizeYF);
			rad += divRad;
			//����l
			if (rad > endRad)
			{
				rad = endRad;
			}
			VECTOR pos2 = MakeRotLocalPos(rad, sizeXF, sizeYF);


			VERTEX2D vertex = VERTEX2D();

			//���S���W
			vertex.pos = pos;
			vertex.pos.z = 0.0f;
			vertex.u = 0.5f;
			vertex.v = 0.5f;
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);

			//���̒��_

			vertex.pos = VAdd(pos, pos1);
			vertex.pos.z = 0.0f;
			vertex.u = (pos1.x + sizeXF) / (sizeXF + sizeXF);
			vertex.v = (pos1.y + sizeYF) / (sizeYF + sizeYF);
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);


			vertex.pos = VAdd(pos, pos2);
			vertex.pos.z = 0.0f;
			vertex.u = (pos2.x + sizeXF) / (sizeXF + sizeXF);
			vertex.v = (pos2.y + sizeYF) / (sizeYF + sizeYF);
			vertex.dif = GetColorU8(255, 255, 255, 255);
			vertex.rhw = 1.0f;
			frameVertexes_.emplace_back(vertex);

			//�|���S�����̑���
			polygonNum++;
			if (rad >= endRad)
			{
				//�쐬����ő�p�x�܂œ��B�����̂ŏ����I��
				break;
			}

		}
	
}

VECTOR GaugeCircle::MakeRotLocalPos(float rad, float sizeX, float sizeY)
{
	VECTOR ret = VECTOR();

	float dirX = sinf(rad);
	float dirY = -cosf(rad);

	//��������Εӂ̒���
	float len = sqrtf(sizeX * sizeX + sizeY * sizeY);

	ret.x = dirX * len;
	ret.y = dirY * len;
	
	//��`�Ɏ��߂�
	if (ret.x > sizeX)
	{
		ret.x = sizeX;
	}
	if (ret.x < -sizeX)
	{
		ret.x = -sizeX;
	}
	if (ret.y > sizeY)
	{
		ret.y = sizeY;
	}
	if (ret.y < -sizeY)
	{
		ret.y = -sizeY;
	}
	return ret;
}
