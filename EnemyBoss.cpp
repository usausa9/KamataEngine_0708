#include "Player.h"
#include "EnemyBoss.h"

void EnemyBoss::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����f�[�^�������o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = textureHandle;

	debugText_ = DebugText::GetInstance();
	breakAudio_ = Audio::GetInstance();

	breakDataHandle_ = breakAudio_->LoadWave("PlayerBreak.wav");
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	// �������W�Ɉړ�
	worldTransform_.translation_ = position;

	velocity_ = { -5.0f,0,0 };
	velocity2_ = { 0,-7.0f,0 };
	velocity3_ = { 0,7.0f,0 };
	velocity4_ = { +10.0f,0,0 };

	//Phese_FireIni();

	matrix_.UpdateMatrix(worldTransform_);

	//fireCoolTime = 20;

	matrix_.ScaleChange(worldTransform_, 85.0f, 85.0f, 49.0f, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, position.x, position.y, position.z);
	matrix_.UpdateMatrix(worldTransform_);
}

void EnemyBoss::DeleteBullet()
{
	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
}

Vector3 EnemyBoss::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;
	return worldPos;
}

void EnemyBoss::Fire()
{
	assert(player_);

	// �e�̑��x
	const float kBulletSpped = 1.0f;

	// �����x�N�g�����i�[����ϐ�
	Vector3 diffVec;

	// ���L�����A�G�L�����̃��[���h���W���擾
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 EnemyBossPos = worldTransform_.translation_;

	// �����x�N�g�������߂�
	diffVec = playerPos - EnemyBossPos;

	// �����x�N�g���̐��K��
	diffVec.normalize();

	// �x�N�g���̒������A�����ɍ��킹��B( ���́H )
	diffVec *= kBulletSpped;

	//// �e�𐶐����A������
	//std::unique_ptr<EnemyBossBullet> newBullet = std::make_unique<EnemyBossBullet>();
	//newBullet->Initialize(model_, worldTransform_.translation_, diffVec);
	//// �e��o�^����
	//bullets_.push_back(std::move(newBullet));
}

void EnemyBoss::Update()
{
	EnemyBoss::DeleteBullet();
	//EnemyBoss::Fire();

	Vector3 playerPos = player_->GetWorldPosition();

	if (worldTransform_.translation_.x <= 700 && phase == 0)
	{
		phase = 1;
	}

	if (worldTransform_.translation_.y <= 180 && phase == 1)
	{
		phase = 2;
	}
	if (worldTransform_.translation_.y >= 530 && phase == 2)
	{
		phase = 1;
	}
	/*if (playerPos.y >= worldTransform_.translation_.y && phase == 1)
	{
		phase = 3;
	}
	if (playerPos.y <= worldTransform_.translation_.y && phase == 2)
	{
		phase = 3;
	}*/

	if (phase == 0)
	{
		// ���x���ړ�
		worldTransform_.translation_ += velocity_;
	}
	else if (phase == 1)
	{
		// ���x���ړ�
		worldTransform_.translation_ += velocity2_;
	}
	else if (phase == 2)
	{
		// ���x���ړ�
		worldTransform_.translation_ += velocity3_;
	}
	else if (phase == 3)
	{
		// ���x���ړ�
		worldTransform_.translation_ += velocity4_;
	}

	// �͈͂𒴂��Ȃ�����
	if (worldTransform_.translation_.x < 0)
	{
		isDead_ = true;
	}

	/*switch (phase_) {
	case Phase::Approach:
	default:
		phase_Approach();
		break;
	case Phase::Leave:
		phase_Leave();
		break;
	}*/

	//// �����o�֐��|�C���^�ɓ����Ă���֐����Ăяo��
	//(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// �e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	// �s��̍X�V
	matrix_.UpdateMatrix(worldTransform_);
}

void EnemyBoss::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// �e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void EnemyBoss::OnCollision()
{
	HP--;

	if (HP <= 0)
	{
		isDead_ = true;
		clear = true;

		breakAudio_->PlayWave(breakDataHandle_, false, 2.0f);
		HP = 150;
	}
}

//void EnemyBoss::Phese_FireIni()
//{
//	fireCoolTime = kFireInterval;
//}
//
//void EnemyBoss::Phase_Approach()
//{
//	velocity_ = { 0,0,0 };
//
//	// �ړ��i�x�N�g�������Z�j
//	worldTransform_.translation_ += velocity_;
//
//	// ���˃^�C�}�[�J�E���g�_�E��
//	fireCoolTime--;
//
//	// �w�莞�ԂɒB����
//	if (fireCoolTime <= 0) {
//		//Fire();
//		// ���˃^�C�}�[�̏�����
//		fireCoolTime = kFireInterval;
//	}
//
//	//// ����̈ʒu�ɓ��B�����痣�E�ɕύX
//	//if (worldTransform_.translation_.z < 0.0f) {
//	//	phase_ = Phase::Leave;
//	//}
//}
//
//void EnemyBoss::Phase_Leave()
//{
//	velocity_ = { 0.3f,0,0 };
//
//	// �ړ��i�x�N�g�������Z�j
//	worldTransform_.translation_ -= velocity_;
//}
//
//void (EnemyBoss::* EnemyBoss::spFuncTable[])() = {
//	&EnemyBoss::Phase_Approach,
//	&EnemyBoss::Phase_Leave
//};