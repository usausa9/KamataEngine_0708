#include "Player.h"
#include <cassert>
#include "MathUtility.h"
using namespace MathUtility;

void Player::Initialize(Model* model,Model* model2,Model* model3,uint32_t textureHandle)
{
	// NULLチェック
	assert(model);
	assert(textureHandle);

	// ファイル名を指定してテクスチャを読み込む
	model_ = model;
	bulletModel_ = model2;
	optionModel_ = model3;
	textureHandle_ = textureHandle;

	// テクスチャ読み込み
	optionTextureHandle_ = TextureManager::Load("Option.png");

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	pad_.Initialize();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_[0].Initialize();

	worldTransform_[1].Initialize();
	worldTransform_[1].translation_ = { 0,50.0f,0 };
	worldTransform_[1].parent_ = &worldTransform_[0];

	worldTransform_[2].Initialize();
	worldTransform_[2].translation_ = { 0,-50.0f,0 };
	worldTransform_[2].parent_ = &worldTransform_[0];

	matrix_.ScaleChange(worldTransform_[0], 0.3f, 0.3f, 0.3f, 1);
	matrix_.RotaChange(worldTransform_[0], 0, 90.0f * MathUtility::PI / 180.0f, 0);
	matrix_.ChangeTranslation(worldTransform_[0], 144.0f, 360.0f, 0);
	matrix_.UpdateMatrix(worldTransform_[0]);

	matrix_.ScaleChange(worldTransform_[1], 100.3f, 100.3f, 100.3f, 1);
	matrix_.RotaChange(worldTransform_[1], 0, 90.0f * MathUtility::PI / 180.0f, 0);
	matrix_.ChangeTranslation(worldTransform_[1], 144.0f, 360.0f, 0);
	matrix_.UpdateMatrix(worldTransform_[1]);

	matrix_.ScaleChange(worldTransform_[2], 100.3f, 100.3f, 100.3f, 1);
	matrix_.RotaChange(worldTransform_[2], 0, 90.0f * MathUtility::PI / 180.0f, 0);
	matrix_.ChangeTranslation(worldTransform_[2], 144.0f, 360.0f, 0);
	matrix_.UpdateMatrix(worldTransform_[2]);
}

void Player::Rotate()
{
	//// キャラクターの旋回ベクトル
	//Vector3 rotate = { 0,0,0 };



	if (input_->PushKey(DIK_LEFT)) {
		
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		
	}
	//worldTransform_[0].rotation_ += rotate;
}

void Player::Move()
{
	pad_.Update();

	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	float kMoveSpd = 5.0f;

	if (boost[SPEEDUP] == USED || boost[SPEEDUP] == USEDSELECT)
	{
		kMoveSpd = 7.5f;
	}

	move.x = pad_.GetLStick().x * kMoveSpd;
	move.y = pad_.GetLStick().y * kMoveSpd;
	
	if (input_->PushKey(DIK_A)) {
		move.x = -kMoveSpd;
	}
	else if (input_->PushKey(DIK_D)) {
		move.x = kMoveSpd;
	}

	/*if (input_->PushKey(DIK_W)) {
		move.z = kMoveSpd;
	}
	else if (input_->PushKey(DIK_S)) {
		move.z = -kMoveSpd;
	}*/

	if (input_->PushKey(DIK_W)) {
		move.y = kMoveSpd;

		if (worldTransform_[0].rotation_.z <= 0.5f)
		{
			worldTransform_[0].rotation_.z += 0.05f;
		}
		
	}
	else if (input_->PushKey(DIK_S)) {
		move.y = -kMoveSpd; 
		if (worldTransform_[0].rotation_.z >= -0.5f)
		{
			worldTransform_[0].rotation_.z -= 0.05f;
		}
	}
	else if (worldTransform_[0].rotation_.z != 0.0f)
	{
		if (worldTransform_[0].rotation_.z <= -0.05f && worldTransform_[0].rotation_.z >= -0.05f)
		{
			worldTransform_[0].rotation_.z = 0.0f;
		}
		else if (worldTransform_[0].rotation_.z < -0.05f)
		{
			worldTransform_[0].rotation_.z += 0.03f;
		}
		else if (worldTransform_[0].rotation_.z > 0.05f)
		{
			worldTransform_[0].rotation_.z -= 0.03f;
		}	
	}
	else if (worldTransform_[0].rotation_.z = 0.0f)
	{

	}

	if (pad_.GetLStick().y < 0) {
		pad_.GetLStick().y * kMoveSpd;

		if (worldTransform_[0].rotation_.z <= 0.5f)
		{
			worldTransform_[0].rotation_.z += 0.05f;
		}

	}
	else if (pad_.GetLStick().y > 0) {
		pad_.GetLStick().y* kMoveSpd;
		if (worldTransform_[0].rotation_.z >= -0.5f)
		{
			worldTransform_[0].rotation_.z -= 0.05f;
		}
	}
	else if (worldTransform_[0].rotation_.z != 0.0f)
	{
		if (worldTransform_[0].rotation_.z <= -0.05f && worldTransform_[0].rotation_.z >= -0.05f)
		{
			worldTransform_[0].rotation_.z = 0.0f;
		}
		else if (worldTransform_[0].rotation_.z < -0.05f)
		{
			worldTransform_[0].rotation_.z += 0.03f;
		}
		else if (worldTransform_[0].rotation_.z > 0.05f)
		{
			worldTransform_[0].rotation_.z -= 0.03f;
		}
	}
	else if (worldTransform_[0].rotation_.z = 0.0f)
	{

	}

	worldTransform_[0].translation_ += move;

	// 移動限界
	const float kMoveLimitX = 790.0f;
	const float kMoveLimitY = 635.0f;

	// 範囲を超えない処理
	worldTransform_[0].translation_.x = max(worldTransform_[0].translation_.x, 75);
	worldTransform_[0].translation_.x = min(worldTransform_[0].translation_.x, kMoveLimitX);
	worldTransform_[0].translation_.y = max(worldTransform_[0].translation_.y, 100);
	worldTransform_[0].translation_.y = min(worldTransform_[0].translation_.y, kMoveLimitY);
}

void Player::ChangeBoost()
{
	if (getBoost == true)
	{
		if (boostSelect != _NONE)
		{
			boostSelect++;
			getBoost = false;
		}
		else
		{
			boostSelect = SPEEDUP;
			getBoost = false;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (boost[DOUBLE] == USED && boost[LASER] == SELECT)
		{
			if (input_->TriggerKey(DIK_M) || pad_.IsButtonTrigger(XINPUT_GAMEPAD_B))
			{
				boost[DOUBLE] = NONE;
				boost[LASER] = USED;
				boostSelect = _NONE;
			}
		}
		else if (boost[DOUBLE] == SELECT && boost[LASER] == USED)
		{
			if (input_->TriggerKey(DIK_M) || pad_.IsButtonTrigger(XINPUT_GAMEPAD_B))
			{
				boost[DOUBLE] = USED;
				boost[LASER] = NONE;
				boostSelect = _NONE;
			}
		}
		else if (boost[i] == SELECT)
		{
			if (input_->TriggerKey(DIK_M) || pad_.IsButtonTrigger(XINPUT_GAMEPAD_B))
			{
				boost[i] = USED;
				boostSelect = _NONE;
			}
		}
	}
	
	if (boostSelect == SPEEDUP)
	{
		if (boost[SPEEDUP] == NONE)
		{
			boost[SPEEDUP] = SELECT;
		}
		else if (boost[SPEEDUP] == USED)
		{
			boost[SPEEDUP] = USEDSELECT;
		}
	}
	if (boostSelect == MISSILE)
	{
		if (boost[MISSILE] == NONE)
		{
			boost[MISSILE] = SELECT;
		}
		else if (boost[MISSILE] == USED)
		{
			boost[MISSILE] = USEDSELECT;
		}

		if (boost[SPEEDUP] == SELECT)
		{
			boost[SPEEDUP] = NONE;
		}
		else if (boost[SPEEDUP] == USEDSELECT)
		{
			boost[SPEEDUP] = USED;
		}
	}
	if (boostSelect == DOUBLE)
	{
		if (boost[DOUBLE] == NONE)
		{
			boost[DOUBLE] = SELECT;
		}
		else if (boost[DOUBLE] == USED)
		{
			boost[DOUBLE] = USEDSELECT;
		}

		if (boost[MISSILE] == SELECT)
		{
			boost[MISSILE] = NONE;
		}
		else if (boost[MISSILE] == USEDSELECT)
		{
			boost[MISSILE] = USED;
		}
	}
	if (boostSelect == LASER)
	{
		if (boost[LASER] == NONE)
		{
			boost[LASER] = SELECT;
		}
		else if (boost[LASER] == USED)
		{
			boost[LASER] = USEDSELECT;
		}

		if (boost[DOUBLE] == SELECT)
		{
			boost[DOUBLE] = NONE;
		}
		else if (boost[DOUBLE] == USEDSELECT)
		{
			boost[DOUBLE] = USED;
		}
	}
	if (boostSelect == OPTION)
	{
		if (boost[OPTION] == NONE)
		{
			boost[OPTION] = SELECT;
		}
		else if (boost[OPTION] == USED)
		{
			boost[OPTION] = USEDSELECT;
		}

		if (boost[LASER] == SELECT)
		{
			boost[LASER] = NONE;
		}
		else if (boost[LASER] == USEDSELECT)
		{
			boost[LASER] = USED;
		}
	}
	if (boostSelect == _NONE)
	{
		if (boost[OPTION] == SELECT)
		{
			boost[OPTION] = NONE;
		}
		else if (boost[OPTION] == USEDSELECT)
		{
			boost[OPTION] = USED;
		}
	}
}

void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE) || pad_.IsButtonDown(XINPUT_GAMEPAD_A))
	{
		shotTimer--;

		if (shotTimer == 0 || input_->TriggerKey(DIK_SPACE) || pad_.IsButtonTrigger(XINPUT_GAMEPAD_A))
		{
			// 弾の速度
			const float kBulletSpeed = 15.0f;
			Vector3 velocity(kBulletSpeed, 0, 0);

			Vector3 velocity2(kBulletSpeed, kBulletSpeed / 2, 0);

			Vector3 velocity3(2.5f, -6.7f, 0);

			//// 速度ベクトルを自機の向きに合わせて回転させる
			//velocity = Vector3MultiMatrix4(velocity, worldTransform_[0].matWorld_);

			Vector3 bulletPrefab = { worldTransform_[0].translation_.x + 45.0f,worldTransform_[0].translation_.y + 2.0f,worldTransform_[0].translation_.z };
			Vector3 bulletPrefab2 = { worldTransform_[0].translation_.x + 45.0f,worldTransform_[0].translation_.y + 52.0f,worldTransform_[0].translation_.z };
			Vector3 bulletPrefab3 = { worldTransform_[0].translation_.x + 45.0f,worldTransform_[0].translation_.y - 48.0f,worldTransform_[0].translation_.z };

			Vector3 bulletPrefab4 = { worldTransform_[0].translation_.x + 145.0f,worldTransform_[0].translation_.y + 52.0f,worldTransform_[0].translation_.z };
			Vector3 bulletPrefab5 = { worldTransform_[0].translation_.x + 145.0f,worldTransform_[0].translation_.y - 48.0f,worldTransform_[0].translation_.z };

			// 弾生成、初期化

			
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(bulletModel_, bulletPrefab, 20.0f, velocity);
			// 弾を登録
			bullets_.push_back(std::move(newBullet));

			if (boost[OPTION] == USED || boost[OPTION] == USEDSELECT)
			{
				// 弾生成、初期化
				std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
				newBullet->Initialize(bulletModel_, bulletPrefab2, 20.0f, velocity);

				// 弾を登録
				bullets_.push_back(std::move(newBullet));

				// 弾生成、初期化
				std::unique_ptr<PlayerBullet> newBullet2 = std::make_unique<PlayerBullet>();
				newBullet2->Initialize(bulletModel_, bulletPrefab3, 20.0f, velocity);

				// 弾を登録
				bullets_.push_back(std::move(newBullet2));
			}

			if (boost[DOUBLE] == USED || boost[DOUBLE] == USEDSELECT)
			{
				// 弾生成、初期化
				std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
				newBullet->Initialize(bulletModel_, bulletPrefab, 20.0f, velocity2);

				// 弾を登録
				bullets_.push_back(std::move(newBullet));

				if (boost[OPTION] == USED || boost[OPTION] == USEDSELECT)
				{
					// 弾生成、初期化
					std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
					newBullet->Initialize(bulletModel_, bulletPrefab2, 20.0f, velocity2);

					// 弾を登録
					bullets_.push_back(std::move(newBullet));

					// 弾生成、初期化
					std::unique_ptr<PlayerBullet> newBullet2 = std::make_unique<PlayerBullet>();
					newBullet2->Initialize(bulletModel_, bulletPrefab3, 20.0f, velocity2);

					// 弾を登録
					bullets_.push_back(std::move(newBullet2));
				}
			}

			if (boost[MISSILE] == USED || boost[MISSILE] == USEDSELECT)
			{
				// 弾生成、初期化
				std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
				newBullet->Initialize(bulletModel_, bulletPrefab, 20.0f, velocity3);

				// 弾を登録
				bullets_.push_back(std::move(newBullet));

				if (boost[OPTION] == USED || boost[OPTION] == USEDSELECT)
				{
					// 弾生成、初期化
					std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
					newBullet->Initialize(bulletModel_, bulletPrefab2, 20.0f, velocity3);

					// 弾を登録
					bullets_.push_back(std::move(newBullet));

					// 弾生成、初期化
					std::unique_ptr<PlayerBullet> newBullet2 = std::make_unique<PlayerBullet>();
					newBullet2->Initialize(bulletModel_, bulletPrefab3, 20.0f, velocity3);

					// 弾を登録
					bullets_.push_back(std::move(newBullet2));
				}
			}

			if (boost[LASER] == USED || boost[LASER] == USEDSELECT)
			{
				shotTimer = fastTimer;
			}
			else if (boost[LASER] == NONE || boost[LASER] == SELECT)
			{
				shotTimer = lateTimer;
			}
		}


	}
	else
	{
		if (boost[LASER] == USED || boost[LASER] == USEDSELECT)
		{
			shotTimer = fastTimer;
		}
		else if (boost[LASER] == NONE || boost[LASER] == SELECT)
		{
			shotTimer = lateTimer;
		}
	}
}

void Player::DeleteBullet()
{
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
	});
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos = worldTransform_[0].translation_;
	return worldPos;
}

void Player::OnCollision()
{
}

void Player::Update()
{
	
	Player::Rotate();
	Player::Move();
	Player::Attack();
	Player::ChangeBoost();

	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	matrix_.UpdateMatrix(worldTransform_[0]);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_[0], viewProjection);

	if (boost[OPTION] == USED || boost[OPTION] == USEDSELECT)
	{
		optionModel_->Draw(worldTransform_[1], viewProjection, optionTextureHandle_);
		optionModel_->Draw(worldTransform_[2], viewProjection, optionTextureHandle_);
	}

	// 弾描画
	for (std::unique_ptr<PlayerBullet>&bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	/*debugText_->SetPos(50, 130);
	debugText_->Printf(
		"pos:%f,%f,%f", worldTransform_[0].translation_.x, worldTransform_[0].translation_.y, worldTransform_[0].translation_.z);*/
}

void Player::Reset()
{
	boostSelect = 5;
	boost[0] = { 0 };
	boost[1] = { 0 };
	boost[2] = { 0 };
	boost[3] = { 0 };
	boost[4] = { 0 };

	shotTimer = 12;
}