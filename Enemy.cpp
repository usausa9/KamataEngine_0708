#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
{
	//NULLポインタチェック
	assert(model);

	//引数データをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	//初期座標に移動
	worldTransform_.translation_ = position;

	velocity_ = { 0,0,-0.1f };

	/*matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, 0, 3, 50);
	matrix_.UpdateMatrix(worldTransform_);*/
}

void Enemy::Update()
{
	//// 速度分移動
	//worldTransform_.translation_ += velocity_;

	switch (phase_) {
	case Phase::Approach:
	default:
		phase_Approach();
		break;
	case Phase::Leave:
		phase_Leave();
		break;
	}

	// 行列の更新
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::phase_Approach()
{
	velocity_ = { 0,0,-0.3f };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += velocity_;

	// 既定の位置に到達したら離脱に変更
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::phase_Leave()
{
	velocity_ = { 0.3f,0,0 };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ -= velocity_;
}