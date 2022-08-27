#pragma once
#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "EnemyBullet.h"

#include <cassert>

// ���@�N���X�̑O���錾
class Player;

class Enemy2
{
public:
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	float radius = 20.0f;

private:
	// ���f��
	Model* model_ = nullptr;

	// �C���v�b�g
	Input* input_ = nullptr;

	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���x
	Vector3 velocity_;
	Vector3 velocity2_;
	Vector3 velocity3_;
	Vector3 velocity4_;

	int phase = 0;

	// ���L����
	Player* player_ = nullptr;

};
