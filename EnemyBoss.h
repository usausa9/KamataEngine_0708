#pragma once

#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "EnemyBullet.h"
#include "Audio.h"

#include <cassert>

// 自機クラスの前方宣言
class Player;

class EnemyBoss
{
public:
	//// Timer
	//static const int32_t kFireInterval = 60;
	//int32_t fireCoolTime = 1000;

	//enum class Phase {
	//	Approach,	// 接近する
	//	Leave,		// 離脱する
	//};

	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	void DeleteBullet();

	void Fire();

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	bool IsDead() const { return isDead_; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド変換データ
	WorldTransform worldTransform_;

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };

	float radius = 80.0f;

	// デスフラグ
	bool isDead_ = false;

	bool clear = false;
private:

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

	Audio* breakAudio_ = nullptr;
	uint32_t breakDataHandle_ = 0;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;
	Vector3 velocity2_;
	Vector3 velocity3_;
	Vector3 velocity4_;

	int phase = 0;

	int HP = 150;
	

	//// フェーズ
	//Phase phase_ = Phase::Approach;

	//// 弾の初期インターバル
	//void Phese_FireIni();

	//// 接近のとき
	//void Phase_Approach();

	//// 離脱のとき
	//void Phase_Leave();

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// 自キャラ
	Player* player_ = nullptr;



	//private:
	//	// メンバ関数ポインタ
	//	static void (Enemy::*spFuncTable[])();
	//

};