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
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
};