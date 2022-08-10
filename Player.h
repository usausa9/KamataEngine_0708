#pragma once

#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "PlayerBullet.h"

#include<memory>
#include<list>

/// <summary>
/// 自キャラ
/// </summary>
class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Rotate();
	void Move();
	void Update();

	void DeleteBullet();

	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールド変換データ
	WorldTransform worldTransform_;

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

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};