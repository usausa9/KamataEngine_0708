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
	//���x���ړ�
	worldTransform_.translation_ += velocity_;

	//�s��̍X�V
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
