#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "WinApp.h"
#include "Matrix.h"
#include "Float3.h"
#include "Player.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ変数
// パーツID
	enum PartId {
		kRoot,	// 大元
		kSpine,	// 脊髄
		kChest,	// 胸
		kHead,	// 頭
		kArmL,	// 左腕
		kArmR,	// 右腕
		kHip,	// 尻
		kLegL,	// 左足
		kLegR,	// 右足

		kNumPartId
	};


  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_ = 0;

	uint32_t backGroundTextureHandle_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;
	Model* enemyModel_ = nullptr;

	Model* backGroundModel_ = nullptr;

	// ランダム格納
	Float3 random;

	// ワールドトランスフォーム
	WorldTransform backGroundWT[1];

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// まとりっくす
	Matrix matrix;
	Matrix backGroundMatrix;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_ = nullptr;

	// 敵の位置
	Vector3 enemyPos{ 0,0,10.0f };

	// カメラ上方向の角度
	float viewAngle = 0.0f;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
