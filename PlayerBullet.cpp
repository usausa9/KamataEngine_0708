#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position,float xSize, const Vector3& velocity)
{
	// NULLチェック
	assert(model);

	// ファイル名を指定してテクスチャを読み込む
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("Bullet.png");

	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();

	matrix_.ScaleChange(worldTransform_, xSize, 20.0f, 20.0f, 1);

	// 引数で受け取った初期座標のセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update()
{
	matrix_.RotaChange(worldTransform_, 0, 0, 0);

	// 座標を移動させる
	worldTransform_.translation_ += velocity_;

	// 時間経過で消える
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 移動限界
	const float kMoveLimitX = 850.0f;

	// 範囲を超えない処理
	if (worldTransform_.translation_.x > kMoveLimitX)
	{
		isDead_ = true;
	}

	// 行列を更新
	matrix_.UpdateMatrix(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::Reset()
{
	isDead_ = true;
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 PlayerBullet::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}