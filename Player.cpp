#include "Player.h"
#include <cassert>
using namespace MathUtility;

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLチェック
	assert(model);
	assert(textureHandle);

	// ファイル名を指定してテクスチャを読み込む
	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//matrix_.ScaleChange(worldTransform_, 0.1f, 0.1f, 7.0f, 1);
	//matrix_.RotaChange(worldTransform_, 0, 0, 0);
	//matrix_.ChangeTranslation(worldTransform_, -5, 0, 0);
	//matrix_.UpdateMatrix(worldTransform_);
}

void Player::Rotate()
{
	//// キャラクターの旋回ベクトル
	//Vector3 rotate = { 0,0,0 };

	const float kRotateSpd = 0.02f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= kRotateSpd;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.rotation_.y += kRotateSpd;
	}
	//worldTransform_.rotation_ += rotate;
}

void Player::Move()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	const float kMoveSpd = 0.5f;

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
	}
	else if (input_->PushKey(DIK_S)) {
		move.y = -kMoveSpd;
	}

	worldTransform_.translation_ += move;

	//移動限界
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		// 弾生成、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾を登録
		bullet_ = newBullet;
	}
}

void Player::Update()
{
	Player::Rotate();
	Player::Move();
	Player::Attack();

	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}

	matrix_.UpdateMatrix(worldTransform_);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}

	debugText_->SetPos(50, 130);
	debugText_->Printf(
		"pos:%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}