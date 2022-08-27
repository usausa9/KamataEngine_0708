#pragma once
#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "EnemyBullet.h"

#include <cassert>

// 自機クラスの前方宣言
class Player;

class Enemy2
{
public:
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド変換データ
	WorldTransform worldTransform_;

	float radius = 20.0f;

private:
	// モデル
	Model* model_ = nullptr;

	// インプット
	Input* input_ = nullptr;

	// デバックテキスト
	DebugText* debugText_ = nullptr;

	// マトリックス
	Matrix matrix_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;
	Vector3 velocity2_;
	Vector3 velocity3_;
	Vector3 velocity4_;

	int phase = 0;

	// 自キャラ
	Player* player_ = nullptr;

};
