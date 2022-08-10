#include "Player.h"
#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
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

	velocity_ = { 0,0,-0.1f };

	Phese_FireIni();

	matrix_.UpdateMatrix(worldTransform_);

	fireCoolTime = 20;

	/*matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, 0, 3, 50);
	matrix_.UpdateMatrix(worldTransform_);*/
}

void Enemy::DeleteBullet()
{
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
	});
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;
	return worldPos;
}

void Enemy::Fire()
{
	assert(player_);

	// 弾の速度
	const float kBulletSpped = 1.0f;

	// 差分ベクトルを格納する変数
	Vector3 diffVec;

	// 自キャラ、敵キャラのワールド座標を取得
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = worldTransform_.translation_;

	// 差分ベクトルを求める
	diffVec = playerPos - enemyPos;

	// 差分ベクトルの正規化
	diffVec.normalize();

	// ベクトルの長さを、速さに合わせる。( ←は？ )
	diffVec *= kBulletSpped;

	// 弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, diffVec);
	// 弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::Update()
{
	Enemy::DeleteBullet();
	//Enemy::Fire();

	//// 速度分移動
	//worldTransform_.translation_ += velocity_;

	/*switch (phase_) {
	case Phase::Approach:
	default:
		phase_Approach();
		break;
	case Phase::Leave:
		phase_Leave();
		break;
	}*/

	// メンバ関数ポインタに入っている関数を呼び出す
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// 弾更新
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	// 行列の更新
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	//デバッグ表示
	debugText_->SetPos(50, 190);
	debugText_->Printf(
		"fireCoolTime:(%d)",
		fireCoolTime);

}

void Enemy::Phese_FireIni()
{
	fireCoolTime = kFireInterval;
}

void Enemy::Phase_Approach()
{
	velocity_ = { 0,0,0 };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += velocity_;

	// 発射タイマーカウントダウン
	fireCoolTime--;

	// 指定時間に達した
	if (fireCoolTime <= 0) {
		Fire();
		// 発射タイマーの初期化
		fireCoolTime = kFireInterval;
	}

	//// 既定の位置に到達したら離脱に変更
	//if (worldTransform_.translation_.z < 0.0f) {
	//	phase_ = Phase::Leave;
	//}
}

void Enemy::Phase_Leave()
{
	velocity_ = { 0.3f,0,0 };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ -= velocity_;
}

void (Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::Phase_Approach,
	&Enemy::Phase_Leave
};