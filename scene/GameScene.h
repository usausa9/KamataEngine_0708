#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "MyViewProjection.h"
#include "WorldTransform.h"
#include "TimeBaseLoopExecuter.h"

#include <sstream>

#include "DebugCamera.h"
#include "WinApp.h"
#include "Matrix.h"
#include "Float3.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "EnemyBoss.h"


#include "PadInput.h"

#include "Collision.h"

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

	enum Scene {
		MENU,
		PLAY,
		GAMECLEAR,
		GAMEOVER
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

	void GameReset();

	/// <summary>
	/// 敵の発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();


	/// <summary>
	/// 敵の発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void UpdateScene();

	

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

	void CheckAllCollisions(Player* player, Enemy* enemy);
	void CheckAllCollisions2(Player* player, Enemy2* enemy);
	void CheckAllCollisions3(Player* player, Enemy3* enemy);
	void CheckAllCollisions4(Player* player, Enemy4* enemy);
	void CheckAllCollisions5(Player* player, EnemyBoss* enemy);

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;

	Input* input_ = nullptr;
	PadInput pad_;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t bulletModelTextureHandle_ = 0;
	uint32_t optionTextureHandle_ = 0;
	uint32_t backGroundTextureHandle_ = 0;
	uint32_t groundTextureHandle_ = 0;
	uint32_t groundUseTextureHandle_ = 0;

	uint32_t menuTextureHandle_ = 0;
	uint32_t gameOverTextureHandle_ = 0;
	uint32_t gameClearTextureHandle_ = 0;

	uint32_t enemy1TextureHandle_ = 0;
	uint32_t enemy2TextureHandle_ = 0;
	uint32_t enemy3TextureHandle_ = 0;
	uint32_t enemy4TextureHandle_ = 0;
	uint32_t enemyBossTextureHandle_ = 0;

	uint32_t blueBer1TH = 0;
	uint32_t blueBer2TH = 0;
	uint32_t blueBer3TH = 0;
	uint32_t blueBer4TH = 0;
	uint32_t blueBer5TH = 0;
	uint32_t blueBer7TH = 0;

	uint32_t orangeBer1TH = 0;
	uint32_t orangeBer2TH = 0;
	uint32_t orangeBer3TH = 0;
	uint32_t orangeBer4TH = 0;
	uint32_t orangeBer5TH = 0;
	uint32_t orangeBer7TH = 0;

	// 3Dモデル.スプライト
	Model* model_ = nullptr;
	Model* optionModel_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* enemy1Model_ = nullptr;
	Model* enemy2Model_ = nullptr;
	Model* enemy3Model_ = nullptr;
	Model* enemy4Model_ = nullptr;
	Model* enemyBossModel_ = nullptr;

	Sprite* gameClearSprite_ = nullptr;
	Sprite* gameOverSprite_ = nullptr;
	Sprite* menuSprite_ = nullptr;

	Sprite* backGroundSprite_ = nullptr;
	Sprite* groundSprite_ = nullptr;
	Sprite* groundUseSprite_ = nullptr;

	Sprite* blueBer1Sprite_ = nullptr;
	Sprite* blueBer2Sprite_ = nullptr;
	Sprite* blueBer3Sprite_ = nullptr;
	Sprite* blueBer4Sprite_ = nullptr;
	Sprite* blueBer5Sprite_ = nullptr;
	Sprite* blueBer7Sprite_[5] = { nullptr,nullptr,nullptr,nullptr,nullptr};

	Sprite* orange1Sprite_ = nullptr;
	Sprite* orange2Sprite_ = nullptr;
	Sprite* orange3Sprite_ = nullptr;
	Sprite* orange4Sprite_ = nullptr;
	Sprite* orange5Sprite_ = nullptr;
	Sprite* orange7Sprite_[5] = { nullptr,nullptr,nullptr,nullptr,nullptr};

	// ランダム格納
	Float3 random;

	// ワールドトランスフォーム

	// ビュープロジェクション
	MyViewProjection viewProjection_;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	TimeBaseLoopExecuter timeBase;

	// まとりっくす
	Matrix matrix;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_ = nullptr;

	std::list<std::unique_ptr<Enemy>> enemys_;
	std::list<std::unique_ptr<Enemy2>> enemys2_;
	std::list<std::unique_ptr<Enemy3>> enemys3_;
	std::list<std::unique_ptr<Enemy4>> enemys4_;

	std::list<std::unique_ptr<EnemyBoss>> enemysBoss_;

	// 敵の位置
	Vector3 enemyPos{ -300,1000300,0 };

	// スクロール変換
	Vector2 backGroundPos{ 0,0 };
	Vector2 backGroundVelocity{ -2.0f,0 };

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	int scene = MENU;
	bool isClear = false;

	int clearTimer = 240;
	int deadTimer = 240;

	bool isDeadPlayer = false;

	// 待機中フラグ
	bool isWait = false;
	// 待機タイマー
	int waitTimer = 0;

	// カメラ上方向の角度
	float viewAngle = 0.0f;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};