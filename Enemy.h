#pragma once
#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"

#include <cassert>

class Enemy
{
public:
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	// �C���v�b�g
	Input* input_ = nullptr;

	//// �f�o�b�N�e�L�X�g
	//DebugText* debugText_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���x
	Vector3 velocity_;

};

