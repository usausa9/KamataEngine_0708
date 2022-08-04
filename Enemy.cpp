#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����f�[�^�������o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = textureHandle;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�������W�Ɉړ�
	worldTransform_.translation_ = position;

	velocity_ = { 0,0,-0.1f };

	/*matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, 0, 3, 50);
	matrix_.UpdateMatrix(worldTransform_);*/
}

void Enemy::Update()
{
	//// ���x���ړ�
	//worldTransform_.translation_ += velocity_;

	switch (phase_) {
	case Phase::Approach:
	default:
		phase_Approach();
		break;
	case Phase::Leave:
		phase_Leave();
		break;
	}

	// �s��̍X�V
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::phase_Approach()
{
	velocity_ = { 0,0,-0.3f };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += velocity_;

	// ����̈ʒu�ɓ��B�����痣�E�ɕύX
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::phase_Leave()
{
	velocity_ = { 0.3f,0,0 };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ -= velocity_;
}