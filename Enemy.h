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

class Enemy
{
public:
	// Timer
	static const int32_t kFireInterval = 60;
	int32_t fireCoolTime = 1000;

	enum class Phase {
		Approach,	// 接近する
		Leave,		// 離脱する
	};

	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	void DeleteBullet();

	void Fire();

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// インプット
	Input* input_ = nullptr;

	// デバックテキスト
	DebugText* debugText_ = nullptr;

	//// デバックテキスト
	//DebugText* debugText_ = nullptr;

	// マトリックス
	Matrix matrix_;



	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 弾の初期インターバル
	void Phese_FireIni();

	// 接近のとき
	void Phase_Approach();

	// 離脱のとき
	void Phase_Leave();

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// 自キャラ
	Player* player_ = nullptr;

private:
	// メンバ関数ポインタ
	static void (Enemy::*spFuncTable[])();
};

