#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete bulletModel_;
	delete enemyModel_;
	delete backGroundSprite_;
	delete groundSprite_;
	delete debugCamera_;
	delete player_;
	delete enemy_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("tex.jpg");
	enemyTextureHandle_ = TextureManager::Load("enemy.jpg");
	bulletModelTextureHandle_ = TextureManager::Load("uvChecker.png");
	backGroundTextureHandle_ = TextureManager::Load("backGround.png");
	groundTextureHandle_ = TextureManager::Load("Ground.png");

	// 3Dモデル.スプライトの生成
	model_ = Model::CreateFromOBJ("vicviper");
	bulletModel_ = Model::Create();
	enemyModel_ = Model::Create();

	backGroundSprite_ = Sprite::Create(backGroundTextureHandle_, { 0,0 });
	groundSprite_ = Sprite::Create(groundTextureHandle_, { 0,0 });

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, bulletModel_, textureHandle_);

	// 敵キャラを生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(enemyModel_, enemyTextureHandle_, enemyPos = {10.0f,0,0});

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

#pragma region ビュー変換行列
	// カメラ視点座標を設定
	// viewProjection_.eye = { 0,0,-10 };

	// カメラ注視点座標を設定
	// viewProjection_.target = { 10,0,0 };

	// カメラ上方向ベクトルを設定(右上45度指定)
	// viewProjection_.up = { cosf(XM_PI / 4.0f), sinf(XM_PI / 4.0f), 0.0f };
#pragma endregion
#pragma region 射影変換行列
	// カメラ垂直方向視野角を設定
	/*viewProjection_.fovAngleY = 10.0f * (XM_PI / 180);*/

	// アスペクト比を設定(1.0fであると、画面比1:1のときに正常な大きさになる)
	// viewProjection_.aspectRatio = 1.0f;

	// ニアクリップ、ファークリップを設定
	/*viewProjection_.nearZ = 52.0f;
	viewProjection_.farZ = 53.0f;*/

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
#pragma endregion

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);

	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//&debugCamera_->GetViewProjection()

	// ライン描画が参照するビュープロジェクションを指定する (アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_P))
	{
		if (isDebugCameraActive_ == true)
		{
			isDebugCameraActive_ = false;
		}
		else if (isDebugCameraActive_ == false)
		{
			isDebugCameraActive_ = true;
		}
	}
#endif 

#pragma region ビュー変換行列
	//	// 視点移動処理
	//	{
	//		// 視点の移動ベクトル
	//		Vector3 move = { 0,0,0 };
	//
	//		// 視点移動の速さ
	//		const float kEyeSpeed = 0.2f;
	//
	//		// 押した方向で移動ベクトルを変更
	//		if (input_->PushKey(DIK_W))
	//		{
	//			move.z += kEyeSpeed;
	//		}
	//		else if (input_->PushKey(DIK_S))
	//		{
	//			move.z -= kEyeSpeed;
	//		}
	//
	//		// 視点移動(ベクトル加算)
	//		viewProjection_.eye += move;
	//
	//		// 行列の再計算
	//		viewProjection_.UpdateMatrix();
	//
	//		// デバッグ用表示
	//		debugText_->SetPos(50, 50);
	//		debugText_->Printf(
	//			"eye:(%f,%f,%f)",
	//			viewProjection_.eye.x,
	//			viewProjection_.eye.y,
	//			viewProjection_.eye.z);
	//	}
	//
	//	// 注視点移動処理
	//	{
	//		// 注視点の移動ベクトル
	//		Vector3 move = { 0,0,0 };
	//
	//		// 注視点移動の速さ
	//		const float kTargetSpeed = 0.2f;
	//
	//		// 押した方向で移動ベクトルを変更
	//		if (input_->PushKey(DIK_LEFT))
	//		{
	//			move.x -= kTargetSpeed;
	//		}
	//		else if (input_->PushKey(DIK_RIGHT))
	//		{
	//			move.x += kTargetSpeed;
	//		}
	//
	//		// 注視点移動(ベクトルの加算)
	//		viewProjection_.target += move;
	//
	//		// 行列の再計算
	//		viewProjection_.UpdateMatrix();
	//
	//		// デバッグ用表示
	//		debugText_->SetPos(50, 70);
	//		debugText_->Printf(
	//			"target:(%f,%f,%f)",
	//			viewProjection_.target.x,
	//			viewProjection_.target.y,
	//			viewProjection_.target.z);
	//	}
	//
	//	// 上方向回転処理
	//	{
	//		// 上方向の回転速さ[ラジアン/フレーム]
	//		const float kUpRotSpeed = 0.05f;
	//
	//		// 押した方向で移動ベクトルを変更
	//		if (input_->PushKey(DIK_SPACE))
	//		{
	//			viewAngle += kUpRotSpeed;
	//			
	//			// 2πを越えたら0にする
	//			viewAngle = fmodf(viewAngle, XM_PI * 2.0f);
	//		}
	//
	//		// 上方向ベクトルを計算(半径1の演習場)
	//		viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};
	//
	//		// 行列の再計算
	//		viewProjection_.UpdateMatrix();
	//
	//		// デバッグ用表示
	//		debugText_->SetPos(50, 90);
	//		debugText_->Printf(
	//			"up:(%f,%f,%f)",
	//			viewProjection_.up.x,
	//			viewProjection_.up.y,
	//			viewProjection_.up.z);
	//	}
#pragma endregion
#pragma region 射影変換行列
	//// FoV変更処理
	//{
	//	const float angleChangeSpeed = 0.05f;
	//	// 上キーで視野角が広がる 下キーで視野角が狭まる
	//	if (input_->PushKey(DIK_UP)) {
	//		if (viewProjection_.fovAngleY < XM_PI) {
	//			viewProjection_.fovAngleY += angleChangeSpeed;
	//		}
	//	}
	//	else if (input_->PushKey(DIK_DOWN)) {
	//		if (viewProjection_.fovAngleY > 0.05f) {
	//			viewProjection_.fovAngleY -= angleChangeSpeed;
	//		}
	//	}
	//	// 行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	// デバッグ用表示
	//	debugText_->SetPos(50, 110);
	//	debugText_->Printf(
	//		"fovAnglrY(Degree):%f",
	//		(viewProjection_.fovAngleY) / (XM_PI / 180));
	//}
//
//// クリップ距離変更処理
//	{
//		const float nearChangeSpeed = 0.05f;
//		// 上キーで視野角が広がる 下キーで視野角が狭まる
//		if (input_->PushKey(DIK_UP)) {
//			viewProjection_.nearZ += nearChangeSpeed;
//		}
//		else if (input_->PushKey(DIK_DOWN)) {
//			viewProjection_.nearZ -= nearChangeSpeed;
//		}
//		// 行列の再計算
//		viewProjection_.UpdateMatrix();
//
//		// デバッグ用表示
//		debugText_->SetPos(50, 130);
//		debugText_->Printf("nearZ:%f",viewProjection_.nearZ);
//	}

#pragma endregion

	if (isDebugCameraActive_) {
		//デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		for (float i = 0; i < 21; i++)
		{
			PrimitiveDrawer::GetInstance()->DrawLine3d({ -20, -20 + (i * 2), 0 }, { 20, -20 + (i * 2), 0 }, { 1,0,0,1 });
			PrimitiveDrawer::GetInstance()->DrawLine3d({ -20 + (i * 2), -20, 0 }, { -20 + (i * 2), 20, 0 }, { 0,1,0,1 });
			PrimitiveDrawer::GetInstance()->DrawLine3d({ -20 + (i * 2), 0, -20 }, { -20 + (i * 2) ,0 ,20, }, { 0,0,1,1 });
		}
	}
	else {
		viewProjection_.UpdateMatrixAsOrtho();
		viewProjection_.TransferMatrix();
	}

	// 自キャラの更新
	player_->Update();

	if (enemy_) {
		enemy_->Update();
	}

	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	backGroundSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region オブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	// 自キャラの描画
	player_->Draw(viewProjection_);

	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	groundSprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

	// ライン描画が参照するビュープロジェクションを指定する (アドレス渡し)
	
	
}

void GameScene::CheckAllCollisions()
{
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	// 敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定

	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets)
	{
		posB = enemyBullet->GetWorldPosition();

		float len = ((posB.x - posA.x) * (posB.x - posA.x)) + ((posB.y - posA.y) * (posB.y - posA.y)) + ((posB.z - posA.z) * (posB.z - posA.z));

		if (len <= 0.5f)
		{
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();

			// 敵弾の衝突時コールバックを呼び出す
			enemyBullet->OnCollision();

		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	posA = enemy_->GetWorldPosition();

	for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets)
	{
		posB = playerBullet->GetWorldPosition();

		float len = ((posB.x - posA.x) * (posB.x - posA.x)) + ((posB.y - posA.y) * (posB.y - posA.y)) + ((posB.z - posA.z) * (posB.z - posA.z));

		if (len <= 6.0f)
		{
			// 自キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();

			// 敵弾の衝突時コールバックを呼び出す
			playerBullet->OnCollision();

		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets)
	{
		posA = enemyBullet->GetWorldPosition();

		for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets)
		{
			posB = playerBullet->GetWorldPosition();

			float len = ((posB.x - posA.x) * (posB.x - posA.x)) + ((posB.y - posA.y) * (posB.y - posA.y)) + ((posB.z - posA.z) * (posB.z - posA.z));

			if (len <= 6.0f)
			{
				// 自キャラの衝突時コールバックを呼び出す
				enemyBullet->OnCollision();

				// 敵弾の衝突時コールバックを呼び出す
				playerBullet->OnCollision();

			}
		}
	}
#pragma endregion
}