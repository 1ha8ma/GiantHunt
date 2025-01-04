#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"CollisionManager.h"
#include"CollisionData.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
#include"PlayerClimb.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);
	position = VGet(0.0f, 0.0f, 0.0f);
	drawPosition = position;
	angle = 0.0f;

	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();
	nowstateKind = State::Run;
	collisionManager = collisionManager->GetInstance();

	//private�ϐ�������
	onGround = true;
	isCatch = false;
	isStand = false;
	fallSpeed = 0.0f;
	hitObjectCapStart = VGet(0.0f, 0.0f, 0.0f);
	hitObjectCapEnd = VGet(0.0f, 0.0f, 0.0f);
	runPlace = PlayerStateProcessBase::RunPlaceKind::ground;

	//�����蔻��
	//�Փˌ�̏�����n��
	collisionData.HitProcess = std::bind(&Player::OnHitObject, this, std::placeholders::_1);
	//�����蔻��ɕK�v�ȃf�[�^��n��
	collisionManager->AddCollisionData(&collisionData);

	//�|�W�V�������f
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	delete nowstate;
	delete input;
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
	changeStateflg = nowstate->Update(position, inputstate, stickstate, camera, hitObjectCapStart, hitObjectCapEnd);

	//�ړ�
	moveVec = nowstate->GetmoveVec();
	//�������Ă��邩�m�F
	CheckOnGround();
	//�������x�ǉ�
	moveVec = VSub(moveVec, VGet(0.0f, fallSpeed, 0.0f));
	//�|�W�V�������f
	position = VAdd(position, moveVec);

	//�`��ʒu�C��
	CorrectionDrawPosition();
	
	//�p�x�X�V
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	nowstate->SetRunPlace(runPlace);

	//�|�W�V�������X�V
	UpdateCapsule();
	UpdateCollisionData();

	//�t���O������
	isCatch = false;
	isStand = false;
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1SetPosition(modelHandle, drawPosition);
	MV1DrawModel(modelHandle);

	DrawCapsule3D(capStart, capEnd, CapsuleRadius, 8, GetColor(220, 20, 60),GetColor(220,20,60), FALSE);
}

/// <summary>
/// �Փ˂������̏���
/// </summary>
/// <param name="hitObjectData">�Փ˂�������</param>
void Player::OnHitObject(CollisionData hitObjectData)
{
	hitObjectCapStart = hitObjectData.startPosition;
	hitObjectCapEnd = hitObjectData.endPosition;

	//�Փ˂����I�u�W�F�N�g���Ƃɏ�����ύX
	//�G�̍U��
	if (hitObjectData.tag == ObjectTag::Attack_E1 ||
		hitObjectData.tag == ObjectTag::Attack_E2)
	{
		//HP����
		HP -= hitObjectData.attackPower;
	}

	//�J�v�Z��
	if (hitObjectData.tag == ObjectTag::Wood1 || hitObjectData.tag == ObjectTag::Wood2 ||	//��
		hitObjectData.tag == ObjectTag::Upperarm_E1 || hitObjectData.tag == ObjectTag::Forearm_E1 || hitObjectData.tag == ObjectTag::Hand_E1)	//�r�̓G
	{
		if (nowstateKind != State::Climb)
		{
			CollisionPushBack(hitObjectData);
		}
		//�I�u�W�F�N�g�̔�������ɂ�����

		isCatch = true;
		runPlace= PlayerStateProcessBase::RunPlaceKind::capsule;
	}
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

	//���f
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

	//�o�胂�[�V�����̎��͔��]
	if (nowstateKind == State::Climb)
	{
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle, 0.0f));
	}
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
		nowstateKind == State::NormalAttack && changeStateflg ||
		nowstateKind == State::Climb && changeStateflg || nowstateKind == State::Climb && !isCatch)
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//�ʏ�U��
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Jump && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}

	//�͂܂�
	if (nowstateKind != State::Climb && isCatch&& (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1)
	{
		delete nowstate;
		nowstateKind = State::Climb;
		nowstate = new PlayerClimb(modelHandle,targetLookDirection);
	}
}

/// <summary>
/// �������Ă��邩�m�F
/// </summary>
void Player::CheckOnGround()
{
	//���n�����Ƃ�
	if (!onGround && position.y < 0.0f || !onGround && isCatch)
	{
		onGround = true;
		moveVec.y = 0.0f;

		//�U��
		StartJoypadVibration(DX_INPUT_PAD1, 500, 100, -1);
	}

	//���Ă��邩
	if (position.y > 0.0f && !isCatch)
	{
		onGround = false;
		runPlace = PlayerStateProcessBase::RunPlaceKind::air;
	}

	//�������Ă��Ȃ���Η���
	if (!onGround)
	{
		fallSpeed += Gravity;
	}
	else
	{
		fallSpeed = 0.0f;
	}

	//���܂ōs���Ȃ��悤��
	if (position.y < 0.0f)
	{
		runPlace = PlayerStateProcessBase::RunPlaceKind::ground;
		position.y = 0.0f;
	}
}

/// <summary>
/// �J�v�Z���X�V
/// </summary>
void Player::UpdateCapsule()
{
	capStart = VAdd(position, VGet(0.0f, 100.0f, 0.0f));
	capEnd = VAdd(position, VGet(0.0f, 50.0f, 0.0f));
}

/// <summary>
/// �����蔻����X�V
/// </summary>
void Player::UpdateCollisionData()
{
	collisionData.tag = ObjectTag::Player;
	collisionData.position = position;
	collisionData.startPosition = capStart;
	collisionData.endPosition = capEnd;
	collisionData.radius = CapsuleRadius;
	collisionData.attackPower = AttackPower;
	collisionData.isCollisionActive = true;
}

/// <summary>
/// �`��ʒu�C��
/// </summary>
void Player::CorrectionDrawPosition()
{
	//��{
	drawPosition = position;

	//�W�����v
	if (nowstateKind == State::Jump)
	{
		drawPosition.y -= 60.0f;
	}

	//�o��
	if (nowstateKind == State::Climb)
	{
		drawPosition.y -= 90.0f;
		drawPosition.x -= cos(angle) * 100.0f;
		drawPosition.z -= sin(-angle) * 100.0f;
	}
}

/// <summary>
/// �Փˌ�̉����߂�
/// </summary>
void Player::CollisionPushBack(CollisionData hitObjectData)
{
	//���a�̍��v
	float radiusSum = hitObjectData.radius + collisionData.radius;

	//�x�N�g���̃T�C�Y���v�Z
	//2�̐����̍ŒZ���������߂�
	float len = Segment_Segment_MinLength(capStart, capEnd, hitObjectData.startPosition, hitObjectData.endPosition);
	float distance = radiusSum - len;

	//�Փ˂������̂ƃv���C���[�̌����̃x�N�g�������
	VECTOR dir = VSub(hitObjectData.position, position);

	//�����߂�
	dir = VNorm(dir);
	VECTOR pushBackVec = VScale(dir, -distance);

	position = VAdd(position, pushBackVec);

	if (position.y < 0.0f)
	{
		position.y = 0.0f;
	}
}