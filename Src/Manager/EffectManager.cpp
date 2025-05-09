#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include "../Common/Parameta.h"
#include"../Application.h"
#include "EffectManager.h"


//�V���O���g����
//-----------------------------------
//input_�̏���������
EffectManager* EffectManager::effect_ = nullptr;


//
//void EffectManager::PlayEffect(EFF_TYPE effect, Parameta par)
//{
//	EFF_DATA data;
//	//�G�t�F�N�g�̍Đ�
//	int resID = data.resId_;
//	int hitResId = effDatas_[EFF_TYPE::HIT].resId_;
//	int effHandle = PlayEffekseer3DEffect(hitResId);	// �G�t�F�N�g�n���h��
//
//	// pushBack�̌��͂�������1����Ȃ��H
//	//effDatas_[effect].playIds_.emplace_back(PlayEffekseer3DEffect(effDatas_[effect].resId_));
//	effDatas_[effect].playIds_.emplace_back(effHandle);
//
//	// data.playIds_.push_back(data.resId_)(PlayEffekseer3DEffect(effDatas_[EFF_TYPE::HIT].resId_));
//
//	//�ȍ~�A�Đ�����G�t�F�N�g�̐���͕K���v���C�n���h��ID���g�p����
//	//�G�t�F�N�g�̑傫����ݒ�
//	SetScalePlayingEffekseer3DEffect(effDatas_[effect].playIds_.back(), par.scl.x, par.scl.y, par.scl.z);
//	//�p�x��ݒ�
//	SetRotationPlayingEffekseer3DEffect(effDatas_[effect].playIds_.back(), par.rot.x, par.rot.y, par.rot.z);
//	//�G�t�F�N�g�̈ʒu��ݒ�
//	SetPosPlayingEffekseer3DEffect(effDatas_[effect].playIds_.back(), par.pos.x, par.pos.y, par.pos.z);
//}

void EffectManager::LoadEffect(void)
{

	EFF_DATA data;
	//�q�b�g�G�t�F�N�g�̃��[�h
	data.resId_ = LoadEffekseerEffect((Application::PATH_EFFECT + "Tktk03/ToonHit.efkefc").c_str());
	effDatas_.emplace(EFF_TYPE::HIT, data);

	data.resId_ = LoadEffekseerEffect((Application::PATH_EFFECT + "MaterialBasic/Falloff.efkefc").c_str());
	effDatas_.emplace(EFF_TYPE::SHIELD, data);

	data.resId_ = LoadEffekseerEffect((Application::PATH_EFFECT + "Pierre01/PhantasmMeteor_Single.efkefc").c_str());
	effDatas_.emplace(EFF_TYPE::WAIDCHARGE, data);

	data.resId_ = LoadEffekseerEffect((Application::PATH_EFFECT + "Suzuki/aura.efkefc").c_str());
	effDatas_.emplace(EFF_TYPE::WAIDATK, data);

	data.resId_= LoadEffekseerEffect((Application::PATH_EFFECT + "MAGICALxSPIRAL/MagicArea.efkefc").c_str());
	effDatas_.emplace(EFF_TYPE::ITEMGET, data);

	for (auto& data : effDatas_)
	{
		data.first;//KEY = EFF_TYPE
		data.second;//VALUE = EFF_DATA
	}

}

void EffectManager::PlayEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par)
{


	if (effDatas_.count(effect) == 0)
	{
		return;
	}

	auto& data = effDatas_[effect];

	//�G�t�F�N�g�̍Đ�
	int resID = data.resId_;
	int effHandle = PlayEffekseer3DEffect(resID);	// �G�t�F�N�g�n���h��

	// pushBack�̌��͂�������1����Ȃ��H
	//effDatas_[effect].playIds_.emplace_back(PlayEffekseer3DEffect(effDatas_[effect].resId_));

	EFF_USER play;
	play.user_ = slime;
	play.playId_ = effHandle;
	play.par = par;

	// data.playIds_.push_back(data.resId_)(PlayEffekseer3DEffect(effDatas_[EFF_TYPE::HIT].resId_));
	effDatas_[effect].playIds_.emplace_back(play);


	//�ȍ~�A�Đ�����G�t�F�N�g�̐���͕K���v���C�n���h��ID���g�p����
	//�G�t�F�N�g�̑傫����ݒ�
	SetScalePlayingEffekseer3DEffect(effHandle, par.scl.x, par.scl.y, par.scl.z);
	//�p�x��ݒ�
	SetRotationPlayingEffekseer3DEffect(effHandle, par.rot.x, par.rot.y, par.rot.z);
	//�G�t�F�N�g�̈ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(effHandle, par.pos.x, par.pos.y, par.pos.z);

}

void EffectManager::SyncEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par)
{

	if (effDatas_.count(effect) == 0)
	{
		return;
	}

	auto& data = effDatas_[effect];

	for (auto& play : data.playIds_)
	{

		if (play.user_ == slime)
		{

			//�ȍ~�A�Đ�����G�t�F�N�g�̐���͕K���v���C�n���h��ID���g�p����
			//�G�t�F�N�g�̑傫����ݒ�
			SetScalePlayingEffekseer3DEffect(play.playId_, par.scl.x, par.scl.y, par.scl.z);
			//�p�x��ݒ�
			SetRotationPlayingEffekseer3DEffect(play.playId_, par.rot.x, par.rot.y, par.rot.z);
			//�G�t�F�N�g�̈ʒu��ݒ�
			SetPosPlayingEffekseer3DEffect(play.playId_, par.pos.x, par.pos.y, par.pos.z);

		}

	}

}

void EffectManager::StopEffect(void)
{
	for (auto& data : effDatas_)
	{
		for (auto& play : data.second.playIds_)
		{
			StopEffekseer3DEffect(play.playId_);
		}
	}
}

void EffectManager::StopEffect(EFF_TYPE type)
{

	if (effDatas_.count(type) == 0)
	{
		return;
	}

	auto& plays = effDatas_[type].playIds_;
	for (auto& play : plays)
	{
		StopEffekseer3DEffect(play.playId_);
	}

}

void EffectManager::StopEffect(EFF_TYPE type, SlimeBase* slime)
{
	if (effDatas_.count(type) == 0)
	{
		return;
	}

	auto& plays = effDatas_[type].playIds_;
	for (auto& play : plays)
	{
		if (play.user_ == slime)
		{
			StopEffekseer3DEffect(play.playId_);
			play.par.isStop = true;
		}
	}
}

void EffectManager::DeleteEffect(void)
{
	//SetSpeedPlayingEffekseer3DEffect(effectPlayId_, 4000);
}

//bool EffectManager::IsPlayEffectEnd(void)
//{
//	if (IsEffekseer3DEffectPlaying(effectPlayId_) == -1)
//	{
//		return false;
//	}
//	return true;
//}

bool EffectManager::IsPlayEffectEnd(EFF_TYPE type, SlimeBase* slime)
{
	if (effDatas_.count(type) == 0)
	{
		return true;
	}

	auto& plays = effDatas_[type].playIds_;
	for (auto& play : plays)
	{
		if (play.user_ == slime)
		{
			if (IsEffekseer3DEffectPlaying(play.playId_) == -1)
			{
				// ��ł���~���Ă������~����
				return true;
			}
		}
	}

	return false;

}

//void EffectManager::ChangeEffect(EFF_TYPE effect,Parameta par)
//{
//	effectEnum_ = effect;
//	PlayEffect(effect,par);
//}

EffectManager::EffectManager(void)
{
}

EffectManager::~EffectManager(void)
{
}

void EffectManager::Init(void)
{
	
}

void EffectManager::Update(void)
{

	for (auto& data : effDatas_)
	{
		for (auto& play : data.second.playIds_)
		{
			if (play.par.isLoop&&!play.par.isStop)
			{
				if (IsEffekseer3DEffectPlaying(play.playId_) == -1)
				{
					play.playId_ = PlayEffekseer3DEffect(data.second.resId_);	// �G�t�F�N�g�n���h��
					//�ȍ~�A�Đ�����G�t�F�N�g�̐���͕K���v���C�n���h��ID���g�p����
					//�G�t�F�N�g�̑傫����ݒ�
					SetScalePlayingEffekseer3DEffect(play.playId_, play.par.scl.x, play.par.scl.y, play.par.scl.z);
					//�p�x��ݒ�
					SetRotationPlayingEffekseer3DEffect(play.playId_, play.par.rot.x, play.par.rot.y, play.par.rot.z);
					//�G�t�F�N�g�̈ʒu��ݒ�
					SetPosPlayingEffekseer3DEffect(play.playId_, play.par.pos.x, play.par.pos.y, play.par.pos.z);
				}
			}
		}
	}

}

void EffectManager::Draw(void)
{
}

void EffectManager::Release(void)
{
}

void EffectManager::Destroy(void)
{
	delete effect_;		//�C���X�^���X���폜
	effect_ = nullptr;	//�C���X�^���X�̈��������
}

void EffectManager::ReleaseEffect(void)
{
	//�V���O���g����
	Destroy();
}

void EffectManager::CreateEffect(void)
{
	if (effect_ == nullptr)
	{
		effect_ = new EffectManager();
	}
	effect_->InitEffect();
}

bool EffectManager::InitEffect(void)
{
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	LoadEffect();
}

EffectManager& EffectManager::GetEffect(void)
{
	return *effect_;
}
