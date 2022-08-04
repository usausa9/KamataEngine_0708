#include "Player.h"
#include <cassert>
using namespace MathUtility;

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�`�F�b�N
	assert(model);
	assert(textureHandle);

	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	model_ = model;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//matrix_.ScaleChange(worldTransform_, 0.1f, 0.1f, 7.0f, 1);
	//matrix_.RotaChange(worldTransform_, 0, 0, 0);
	//matrix_.ChangeTranslation(worldTransform_, -5, 0, 0);
	//matrix_.UpdateMatrix(worldTransform_);
}

void Player::Rotate()
{
	//// �L�����N�^�[�̐���x�N�g��
	//Vector3 rotate = { 0,0,0 };

	const float kRotateSpd = 0.02f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= kRotateSpd;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.rotation_.y += kRotateSpd;
	}
	//worldTransform_.rotation_ += rotate;
}

void Player::Move()
{
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	const float kMoveSpd = 0.5f;

	if (input_->PushKey(DIK_A)) {
		move.x = -kMoveSpd;
	}
	else if (input_->PushKey(DIK_D)) {
		move.x = kMoveSpd;
	}

	/*if (input_->PushKey(DIK_W)) {
		move.z = kMoveSpd;
	}
	else if (input_->PushKey(DIK_S)) {
		move.z = -kMoveSpd;
	}*/

	if (input_->PushKey(DIK_W)) {
		move.y = kMoveSpd;
	}
	else if (input_->PushKey(DIK_S)) {
		move.y = -kMoveSpd;
	}

	worldTransform_.translation_ += move;

	//�ړ����E
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		// �e�����A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// �e��o�^
		bullet_ = newBullet;
	}
}

void Player::Update()
{
	Player::Rotate();
	Player::Move();
	Player::Attack();

	// �e�X�V
	if (bullet_) {
		bullet_->Update();
	}

	matrix_.UpdateMatrix(worldTransform_);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// �e�`��
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}

	debugText_->SetPos(50, 130);
	debugText_->Printf(
		"pos:%f,%f,%f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
}