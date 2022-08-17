#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
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

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void PlayerBullet::Update()
{
	matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);

	// ���W���ړ�������
	worldTransform_.translation_ += velocity_;

	// ���Ԍo�߂ŏ�����
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// �s����X�V
	matrix_.UpdateMatrix(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 PlayerBullet::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}