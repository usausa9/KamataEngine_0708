#include "Player.h"
#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& position)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����f�[�^�������o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = textureHandle;

	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	// �������W�Ɉړ�
	worldTransform_.translation_ = position;

	velocity_ = { 0,0,-0.1f };

	Phese_FireIni();

	matrix_.UpdateMatrix(worldTransform_);

	fireCoolTime = 20;

	/*matrix_.ScaleChange(worldTransform_, 1, 1, 1, 1);
	matrix_.RotaChange(worldTransform_, 0, 0, 0);
	matrix_.ChangeTranslation(worldTransform_, 0, 3, 50);
	matrix_.UpdateMatrix(worldTransform_);*/
}

void Enemy::DeleteBullet()
{
	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
	});
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos = worldTransform_.translation_;
	return worldPos;
}

void Enemy::Fire()
{
	assert(player_);

	// �e�̑��x
	const float kBulletSpped = 1.0f;

	// �����x�N�g�����i�[����ϐ�
	Vector3 diffVec;

	// ���L�����A�G�L�����̃��[���h���W���擾
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = worldTransform_.translation_;

	// �����x�N�g�������߂�
	diffVec = playerPos - enemyPos;

	// �����x�N�g���̐��K��
	diffVec.normalize();

	// �x�N�g���̒������A�����ɍ��킹��B( ���́H )
	diffVec *= kBulletSpped;

	// �e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, diffVec);
	// �e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Enemy::Update()
{
	Enemy::DeleteBullet();
	//Enemy::Fire();

	//// ���x���ړ�
	//worldTransform_.translation_ += velocity_;

	/*switch (phase_) {
	case Phase::Approach:
	default:
		phase_Approach();
		break;
	case Phase::Leave:
		phase_Leave();
		break;
	}*/

	// �����o�֐��|�C���^�ɓ����Ă���֐����Ăяo��
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// �e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	// �s��̍X�V
	matrix_.UpdateMatrix(worldTransform_);
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	//�f�o�b�O�\��
	debugText_->SetPos(50, 190);
	debugText_->Printf(
		"fireCoolTime:(%d)",
		fireCoolTime);

}

void Enemy::Phese_FireIni()
{
	fireCoolTime = kFireInterval;
}

void Enemy::Phase_Approach()
{
	velocity_ = { 0,0,0 };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += velocity_;

	// ���˃^�C�}�[�J�E���g�_�E��
	fireCoolTime--;

	// �w�莞�ԂɒB����
	if (fireCoolTime <= 0) {
		Fire();
		// ���˃^�C�}�[�̏�����
		fireCoolTime = kFireInterval;
	}

	//// ����̈ʒu�ɓ��B�����痣�E�ɕύX
	//if (worldTransform_.translation_.z < 0.0f) {
	//	phase_ = Phase::Leave;
	//}
}

void Enemy::Phase_Leave()
{
	velocity_ = { 0.3f,0,0 };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ -= velocity_;
}

void (Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::Phase_Approach,
	&Enemy::Phase_Leave
};