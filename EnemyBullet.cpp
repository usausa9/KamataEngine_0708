#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLチェック
	assert(model);

	// ファイル名を指定してテクスチャを読み込む
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 位置初期化
	worldTransform_.translation_ = position;

	// 速度
	velocity_ = velocity;

	matrix_.UpdateMatrix(worldTransform_);
}

void EnemyBullet::Update()
{
	worldTransform_.translation_ -= velocity_;
	matrix_.UpdateMatrix(worldTransform_);

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}