#pragma once
#include "Player.h"
class Player2 :public Player 
{
public:
	//�萔
	//�X���C���̐F
	static constexpr int SLIME_COLOR = 0xED784A;

	//�������W
	static constexpr VECTOR INIT_POS = { Stage::STAGE_ONE_SQUARE * 3,RADIUS,0.0f };

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
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void) override;

	void DrawDebug(void)override;
	
protected:
	
	void KnockBuckUpdate(void);

	void KnockBack(void)override;

	/// <summary>
	/// �p�����^�̏�����
	/// </summary>
	/// <param name=""></param>
	void SetParam(void)override;

	

private:

};

