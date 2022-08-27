#include "Enemy2.h"
#include "Player.h"

void Enemy2::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
{
	// NULLポインタチェック
	assert(model);

	// 引数データをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;

	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// 初期座標に移動
	worldTransform_.translation_ = position;

	velocity_ = { -3.0f,0,0 };
	velocity2_ = { -3.0f,-5.0f,0 };
	velocity3_ = { -3.0f,3.0f,0 };
	velocity4_ = { -3.0f,0,0 };

	matrix_.UpdateMatrix(worldTransform_);


	matrix_.ScaleChange(worldTransform_, 25.0f, 25.0f, 25.0f, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, position.x, position.y, position.z);
	matrix_.UpdateMatrix(worldTransform_);
}

Vector3 Enemy2::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;
	return worldPos;
}

void Enemy2::Update()
{
	Vector3 playerPos = player_->GetWorldPosition();

	if (playerPos.x > worldTransform_.translation_.x - 100 && phase == 0)
	{
		if (worldTransform_.translation_.y >= 400)
		{
			phase = 1;
		}
		else
		{
			phase = 2;
		}
	}

	if (playerPos.y >= worldTransform_.translation_.y && phase == 1)
	{
		phase = 3;
	}
	if (playerPos.y <= worldTransform_.translation_.y && phase == 2)
	{
		phase = 3;
	}

	if (phase == 0)
	{
		// 速度分移動
		worldTransform_.translation_ += velocity_;
	}
	else if (phase == 1)
	{
		// 速度分移動
		worldTransform_.translation_ += velocity2_;
	}
	else if (phase == 2)
	{
		// 速度分移動
		worldTransform_.translation_ += velocity3_;
	}
	else if (phase == 3)
	{
		// 速度分移動
		worldTransform_.translation_ += velocity4_;
	}

	// 行列の更新
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy2::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy2::OnCollision()
{
}