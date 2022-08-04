#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	// NULL�`�F�b�N
	assert(model);

	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	model_ = model;

	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// ���[���h�g�����X�t�H�[��������
	worldTransform_.Initialize();

	// �����Ŏ󂯎�����������W�̃Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update()
{
	matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.UpdateMatrix(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
