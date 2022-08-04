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
	//速度分移動
	worldTransform_.translation_ += velocity_;

	//行列の更新
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
