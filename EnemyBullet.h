#pragma once
#include "Matrix.h"
#include <cassert>

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"

class EnemyBullet
{
public:

	// ������
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	// �X�V
	void Update();

	// �`��
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���x
	Vector3 velocity_;

	// ����
	static const int32_t kLifeTime = 60 * 3;

	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	// �f�X�t���O
	bool isDead_ = false;
};