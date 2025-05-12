#include <DxLib.h>
#include"./InputManager.h"

//シングルトン化
//-----------------------------------
//input_の初期化処理
InputManager* InputManager::input_ = nullptr;

//デフォルトコンストラクタ
InputManager::InputManager(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf_[index] = '\0';
		preKeyBuf_[index] = '\0';
	}
	//入力制御の初期化
	for (int n = 0; n < PAD_NUM; n++)
	{
		currentPadBuf_[n] = 0;
		prePadBuf_[n] = 0;
	}
}

//デストラクタ
InputManager::~InputManager(void)
{

}



//入力制御初期化
void InputManager::InitInput(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf_[index] = '\0';
		preKeyBuf_[index] = '\0';
	}
	//入力制御の初期化
	for (int n = 0; n < PAD_NUM; n++)
	{
		currentPadBuf_[n] = 0;
		prePadBuf_[n] = 0;
	}
}

//入力制御ステップ
//他のStepよりより早く呼ぶ
void InputManager::StepInput(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
 		preKeyBuf_[index] = currentKeyBuf_[index];
	}

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf_);
}

//単純に押されているか
bool InputManager::IsKeyDown(int key_code)
{
	//現フレームで押されている(前フレームの状態は関係なし)
	if (currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//今押された判定
bool InputManager::IsKeyPush(int key_code)
{
	//前フレームで押されてない　かつ　現フレームで押されている
	if (preKeyBuf_[key_code] == 0 && currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//長押し判定
bool InputManager::IsKeyKeep(int key_code)
{
	//前フレームで押されている　かつ　現フレームでも押されている
	if (preKeyBuf_[key_code] == 1 && currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//今離された判定
bool InputManager::IsKeyRelease(int key_code)
{
	//前フレームで押されている　かつ　現フレームで押されていない
	if (preKeyBuf_[key_code] == 1 && currentKeyBuf_[key_code] == 0)
	{
		return true;
	}
	return false;
}

void InputManager::StepPadInput(void)
{
	//現在のコントローラー接続数
	int padNumber = GetJoypadNum();
	for (int n = 0; n < PAD_NUM; n++)
	{
		//前フレームのキー情報変数に記憶しておく
		prePadBuf_[n] = currentPadBuf_[n];

		//パッドが一つも繋がってないとき
		if (padNumber == 0)
		{
			//配列0番目にキーボードの現在のキー情報を取得
			currentPadBuf_[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		}
		else
		{
			//現在のキー情報を取得
			currentPadBuf_[n] = GetJoypadInputState(n + 1);
		}
	}
}

bool InputManager::IsPadDown(int padNum, int key_code)
{
	//コントローラーの番号合わせ用
	int padNumber;

	//コントローラーとキーボード用
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//１番に合わせる
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//配列用に数字を合わせる
		padNumber = padNum - 1;
	}
	//現フレームで押されている(前フレームの状態は関係なし)
	if ((currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}

bool InputManager::IsPadPush(int padNum, int key_code)
{
	//コントローラーの番号合わせ用
	int padNumber;

	//コントローラーとキーボード用
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//１番に合わせる
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//配列用に数字を合わせる
		padNumber = padNum - 1;
	}
	//前フレームで押されてない　かつ　現フレームで押されている
	if ((prePadBuf_[padNumber]&key_code )== 0 && (currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}

bool InputManager::IsPadKeep(int padNum, int key_code)
{
	//コントローラーの番号合わせ用
	int padNumber;

	//コントローラーとキーボード用
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//１番に合わせる
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//配列用に数字を合わせる
		padNumber = padNum - 1;
	}
	//前フレームで押されてる　かつ　現フレームで押されてる
	if ((prePadBuf_[padNumber] & key_code) != 0 && (currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}


bool InputManager::IsPadRelease(int padNum, int key_code)
{
	//コントローラーの番号合わせ用
	int padNumber;

	//コントローラーとキーボード用
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//１番に合わせる
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//配列用に数字を合わせる
		padNumber = padNum - 1;
	}
	//前フレームで押されてる　かつ　現フレームで押されてない
	if ((prePadBuf_[padNumber] & key_code) != 0 && (currentPadBuf_[padNumber] & key_code) == 0)
	{
		return true;
	}
	return false;
}

//操作制御インスタンスの開放
void InputManager::ReleaseInput(void)
{
	//シングルトン化
	Destroy();
}

void InputManager::CreateInput(void)
{
	if (input_ == nullptr)
	{
		input_ = new InputManager();
	}
	input_->InitInput();
}

//インスタンスを外部に呼び出せるようにする
InputManager& InputManager::GetInput(void)
{
	return *input_;
}

void InputManager::Destroy(void)
{
	delete input_;		//インスタンスを削除
	input_ = nullptr;	//インスタンス領域を初期化
}