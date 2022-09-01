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

class Enemy3
{
public:
	//// Timer
	//static const int32_t kFireInterval = 60;
	//int32_t fireCoolTime = 1000;

	//enum class Phase {
	//	Approach,	// �ڋ߂���
	//	Leave,		// ���E����
	//};

	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	void DeleteBullet();

	void Fire();

	

	Vector3 GetWorldPosition();

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }

	bool IsDead() const { return isDead_; }

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };

	float radius = 20.0f;

	// �f�X�t���O
	bool isDead_ = false;

private:

	// ���f��
	Model* model_ = nullptr;

	// �C���v�b�g
	Input* input_ = nullptr;

	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	//// �f�o�b�N�e�L�X�g
	//DebugText* debugText_ = nullptr;

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

	//// �t�F�[�Y
	//Phase phase_ = Phase::Approach;

	//// �e�̏����C���^�[�o��
	//void Phese_FireIni();

	//// �ڋ߂̂Ƃ�
	//void Phase_Approach();

	//// ���E�̂Ƃ�
	//void Phase_Leave();

	// �e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// ���L����
	Player* player_ = nullptr;


	//private:
	//	// �����o�֐��|�C���^
	//	static void (Enemy::*spFuncTable[])();
	//

};