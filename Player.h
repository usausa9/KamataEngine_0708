#pragma once

#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "PlayerBullet.h"
#include "PadInput.h"

#include<memory>
#include<list>

/// <summary>
/// 自キャラ
/// </summary>
class Player
{
	enum BoostState
	{
		NONE,
		SELECT,
		USED,
		USEDSELECT
	};

	enum BoostName
	{
	/*	NONE,*/
		SPEEDUP,
		MISSILE,
		DOUBLE,
		LASER,
		OPTION,
		_NONE
	};
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, Model* model2, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Rotate();
	void Move();

	void ChangeBoost();
	void Update();

	void DeleteBullet();

	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; };

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;


	int boostSelect = 5;
	int boost[5] = {0,0,0,0,0};

	int shotTimer = 12;

	// インプット
	Input* input_ = nullptr;
	PadInput pad_;

	// デバックテキスト
	DebugText* debugText_ = nullptr;

	// マトリックス
	Matrix matrix_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};