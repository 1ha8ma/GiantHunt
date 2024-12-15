#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"PlayerStateProcessBase.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
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

	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();
	nowstateKind = State::Run;

	onGround = true;

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
	//����
	inputstate = input->GetInputState();
	stickstate = input->GetStickInput();

	//���͂ɂ���ăX�e�[�g�ύX
	ChangeState();

	//�X�e�[�g�X�V
	changeStateflg = nowstate->Update(inputstate, stickstate, camera);

	//�ړ�
	moveVec = nowstate->GetmoveVec();
	position = VAdd(position, moveVec);

	//�������Ă��邩�m�F
	CheckOnGround();

	//�p�x�X�V
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	//�|�W�V�������f
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
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
	//�W�����v
	if (nowstateKind != State::Jump && nowstateKind != State::NormalAttack && (Input::InputNumber::AButton & inputstate) == Input::InputNumber::AButton)
	{
		delete nowstate;
		onGround = false;
		nowstateKind = State::Jump;
		nowstate = new PlayerJump(modelHandle, moveVec);
	}

	//����
	if (nowstateKind == State::Jump && onGround ||
		nowstateKind == State::NormalAttack && changeStateflg)
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//�ʏ�U��
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Jump && (Input::InputNumber::BButton & inputstate) == Input::InputNumber::BButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}
}

/// <summary>
/// �������Ă��邩�m�F
/// </summary>
void Player::CheckOnGround()
{
	if (position.y <= 0.0f)
	{
		onGround = true;
		position.y = 0.0f;
	}
}