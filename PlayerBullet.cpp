#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	// NULLチェック
	assert(model);

	// ファイル名を指定してテクスチャを読み込む
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	// 引数で受け取った初期座標のセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.UpdateMatrix(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
