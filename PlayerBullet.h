#pragma once
#include "Matrix.h"
#include <cassert>

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position, float xSize, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Reset();

	bool IsDead() const { return isDead_; }

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	Vector3 GetWorldPosition();

	// ���x
	Vector3 velocity_;

	float radius = 5.0f;

	// �f�X�t���O
	bool isDead_ = false;

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ����
	static const int32_t kLifeTime = 60 * 3;

	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	
};