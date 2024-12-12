#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Camera.h"
#include"PlayerStateProcessBase.h"
#include"PlayerRun.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);
	position = VGet(0.0f, 0.0f, 0.0f);
	angle = 0.0f;

	nowstate = new PlayerRun(modelHandle);
	nextstate = NULL;

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(const Camera& camera)
{
	nextstate = nowstate->Update(camera);

	//�ړ�
	moveVec = nowstate->GetmoveVec();
	position = VAdd(position, moveVec);

	//�p�x�X�V
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	MV1SetPosition(modelHandle, position);

	//���̃X�e�[�g���Ⴆ�ΕύX
	if (nextstate != nowstate)
	{
		ChangeState();
	}
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	nowstate->Draw();
	//DrawFormatString(100, 100, GetColor(127, 255, 0), "X:%d Y:%d Z:%d", position.x, position.y, position.z);
}

/// <summary>
/// �p�x�X�V
/// </summary>
void Player::UpdateAngle()
{
	//�ړ������Ƀ��f���̕������߂Â���
	float targetAngle;//�ڕW�̊p�x
	float difference;//�ڕW�p�x�ƌ��݂̊p�x�̍�

	//�ڕW�̕����x�N�g������p�x�l���Z�o����
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	//�ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
	//�ŏ��͈����Z
	difference = targetAngle - angle;

	//����������炠������̍���180�x�ȏ�ɂȂ邱�Ƃ͂Ȃ��̂ō���180�x�ȏ�ɂȂ��Ă�����C������
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//�p�x�̍���0�ɋ߂Â���
	if (difference > 0.0f)//�����}�C�i�X�̏ꍇ
	{
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//�����v���X�̏ꍇ
	{
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//���f���̊p�x���X�V
	angle = targetAngle - difference;
	

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// �X�e�[�g�ύX
/// </summary>
void Player::ChangeState()
{
	delete nowstate;

	nowstate = nextstate;
	
	nextstate = NULL;
}