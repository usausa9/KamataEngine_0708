#pragma once

#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"
#include "PlayerBullet.h"
#include "PadInput.h"

#include<memory>
#include<list>

/// <summary>
/// ���L����
/// </summary>
class Player
{
	enum BoostState
	{
		NONE,
		SELECT,
		USED,
		USEDSELECT
	};

	enum BoostName
	{
	/*	NONE,*/
		SPEEDUP,
		MISSILE,
		DOUBLE,
		LASER,
		OPTION,
		_NONE
	};
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, Model* model2, Model* model3, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Rotate();
	void Move();

	void ChangeBoost();
	void Update();

	void DeleteBullet();

	void Attack();

	void Reset();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; };

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[3];

	// ���f��
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Model* optionModel_ = nullptr;

	bool getBoost = false;

	int boostSelect = 5;
	int boost[5] = {0,0,0,0,0};

	int shotTimer = 20;

	const int lateTimer = 17;
	const int fastTimer = 10;

	const float radius = 5.0f;

	// �C���v�b�g
	Input* input_ = nullptr;
	PadInput pad_;

	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	// �}�g���b�N�X
	Matrix matrix_;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	uint32_t optionTextureHandle_ = 0u;

	// �e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};