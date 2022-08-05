#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULL�`�F�b�N
	assert(model);

	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	model_ = model;

	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// ���[���h�g�����X�t�H�[��������
	worldTransform_.Initialize();

	// �ʒu������
	worldTransform_.translation_ = position;

	// ���x
	velocity_ = velocity;

	matrix_.UpdateMatrix(worldTransform_);
}

void EnemyBullet::Update()
{
	worldTransform_.translation_ -= velocity_;
	matrix_.UpdateMatrix(worldTransform_);

	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}