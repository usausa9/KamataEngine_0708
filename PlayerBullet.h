#pragma once
#include "Matrix.h"
#include <cassert>

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position, float xSize, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Reset();

	bool IsDead() const { return isDead_; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	Vector3 GetWorldPosition();

	// 速度
	Vector3 velocity_;

	float radius = 5.0f;

	// デスフラグ
	bool isDead_ = false;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// マトリックス
	Matrix matrix_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 寿命
	static const int32_t kLifeTime = 60 * 3;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;

	
};