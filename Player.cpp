#include"DxLib.h"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"CollisionManager.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
#include"PlayerClimb.h"
#include"PlayerSquat.h"
#include"PlayerPiercing.h"
#include"PlayerFallDown.h"
#include"PlayerIdle.h"
#include"PlayerFalling.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);

	InitializeStartScene();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	collisionManager->RemoveCollisionData(&bodyCollisionData);
	collisionManager->RemoveCollisionData(&footCollisionData);
	delete input;
	delete nowstate;
}

/// <summary>
/// �X�^�[�g�V�[��������
/// </summary>
void Player::InitializeStartScene()
{
	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	position = VGet(3000.0f, 0.0f, -1000.0f);
	drawPosition = position;
	angle = 0.0f;
}

/// <summary>
/// �Q�[���V�[��������
/// </summary>
void Player::InitializeGame()
{
	//�C���X�^���X��
	nowstate = new PlayerIdle(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();

	//�ϐ�������
	nowstateKind = State::Run;
	position = VGet(3000.0f, 0.0f, -1000.0f);
	drawPosition = position;
	angle = 0.0f;
	HP = MaxHP;
	gripPoint = MaxGripPoint;
	onGround = true;
	isCatch = false;
	fallSpeed = 0.0f;
	fallFrame = 0;
	runPlace = PlayerStateProcessBase::RunPlaceKind::ground;
	gameOverflg = false;
	canInputX = false;
	onFootObject = true;
	cameraZoom = 0.0f;
	piercingArmRotateZ = 0.0f;
	onPiercingGauge = false;
	putCloseVec = VGet(0, 0, 0);

	//�����蔻��
	collisionManager = collisionManager->GetInstance();
	//�Փˌ�̏�����n��
	bodyCollisionData.HitProcess = std::bind(&Player::BodyOnHitObject, this, std::placeholders::_1);
	bodyCollisionData.WallHitProcess = std::bind(&Player::WallHitProcess, this, std::placeholders::_1);
	footCollisionData.HitProcess = std::bind(&Player::FootOnHitObject, this, std::placeholders::_1);
	//�����蔻��ɕK�v�ȃf�[�^��n��
	collisionManager->AddCollisionData(&bodyCollisionData);
	collisionManager->AddCollisionData(&footCollisionData);

	//�|�W�V�������f
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="camera">�J����</param>
/// <returns>�Q�[���I�[�o�[</returns>
bool Player::UpdateGame(Camera* camera)
{
	//����
	inputstate = input->GetInputState();
	stickstate = input->GetStickInput();

	//���͂ɂ���ăX�e�[�g�ύX
	ChangeState();

	//�X�e�[�g�X�V�ɕK�v�ȏ���n��
	if (nowstateKind == State::Climb)
	{
		hitObjectData = collisionManager->GetCollisionData(hitObjectDataPointer);
		float length = Segment_Segment_MinLength(wholebodyCapStart, wholebodyCapEnd, hitObjectData.startPosition, hitObjectData.endPosition);
		float distance = (WholeBodyCapsuleRadius + hitObjectData.radius) - length;
		//�Փ˂������̂ƃv���C���[�̌����̃x�N�g�������
		VECTOR dir = VSub(hitObjectData.position,position);
		//�߂Â���
		dir = VNorm(dir);
		putCloseVec = VScale(dir, distance);
	}
	MoveUseDataSet();
	//�X�e�[�g�X�V
	changeStateflg = nowstate->Update(moveUseData, *camera, hitObjectData);

	//�ړ�
	moveVec = nowstate->GetmoveVec();
	//�������x�ǉ�
	moveVec = VSub(moveVec, VGet(0.0f, fallSpeed, 0.0f));
	//�|�W�V�������f
	position = VAdd(position, moveVec);
	//�������Ă��邩�m�F
	CheckOnGround(camera);

	//�`��ʒu�C��
	CorrectionDrawPosition();
	
	//�p�x�X�V
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	//�A�����͖h�~
	PreventionContinuousInput();

	//����
	if (nowstateKind == State::Climb)
	{
		gripPoint -= MinusGripPoint;
	}
	else
	{
		gripPoint += MinusGripPoint;
		if (gripPoint > MaxGripPoint)
		{
			gripPoint = MaxGripPoint;
		}
	}

	//�Q�[���I�[�o�[�m�F
	if (HP <= 0)
	{
		gameOverflg = true;
	}

	//�˂��h���U����
	if (nowstateKind == State::Piercing)
	{
		onPiercingGauge = true;
		cameraZoom = nowstate->GetCameraZoom();
		piercingArmRotateZ = nowstate->GetArmRotateZ();
	}
	else
	{
		onPiercingGauge = false;
		cameraZoom = 0.0f;
	}
	//�W�����v��
	if (nowstateKind == State::Jump && !jumpAfterLeaveFoot && !onFootObject)
	{
		jumpAfterLeaveFoot = true;
	}

	//�|�W�V�������X�V
	UpdateCapsule();
	UpdateCollisionData();

	//�ϐ�������
	isCatch = false;
	onFootObject = false;
	putCloseVec = VGet(0, 0, 0);

	return gameOverflg;
}

/// <summary>
/// �Q�[���I�[�o�[�V�[��������
/// </summary>
void Player::InitializeGameOver()
{
	delete nowstate;
	nowstateKind = State::FallDown;
	nowstate = new PlayerFallDown(modelHandle);
}

/// <summary>
/// �Q�[���I�[�o�[�V�[���X�V
/// </summary>
void Player::UpdateGameOver()
{
	nowstate->UpdateGameOver();
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1SetPosition(modelHandle, drawPosition);
	MV1DrawModel(modelHandle);

	//�m�F�p
	//DrawCapsule3D(bodyCollisionData.startPosition, bodyCollisionData.endPosition, WholeBodyCapsuleRadius, 8, GetColor(220, 20, 60),GetColor(220,20,60), FALSE);
	//DrawCapsule3D(footCapStart, footCapEnd, FootCapsuleRadius, 8, GetColor(220, 20, 60), GetColor(220, 20, 60), FALSE);
	//nowstate->Draw();
}

/// <summary>
/// �Փˎ��̏���
/// </summary>
/// <param name="hitObjectData">�Փ˂����I�u�W�F�N�g</param>
void Player::BodyOnHitObject(CollisionData* hitObjectData)
{
	//�Փ˂����I�u�W�F�N�g���Ƃɏ�����ύX
	//�G�̍U��
	if (hitObjectData->tag == ObjectTag::EnemyAttack)
	{
		//HP����
		HP -= hitObjectData->attackPower;

		if (HP < 0)
		{
			HP = 0;
		}
	}

	//�J�v�Z��
	if (hitObjectData->tag == ObjectTag::StageObject ||
		hitObjectData->tag == ObjectTag::EnemyParts)
	{
		//�f�[�^�R�s�[
		hitObjectDataPointer = hitObjectData;
		this->hitObjectData = *hitObjectData;

		//�����߂�
		if (nowstateKind != State::Climb)
		{
			CollisionPushBack(bodyCollisionData, *hitObjectData);
		}
		isCatch = true;
		runPlace = PlayerStateProcessBase::RunPlaceKind::capsule;
	}
}

/// <summary>
/// �I�u�W�F�N�g�Փˎ��̏���(��)
/// </summary>
/// <param name="hitObjectData">�Փ˂����I�u�W�F�N�g</param>
void Player::FootOnHitObject(CollisionData* hitObjectData)
{
	if (hitObjectData->tag == ObjectTag::StageObject ||		//��
		hitObjectData->tag == ObjectTag::EnemyParts)	//�r�̓G
	{
		onFootObject = true;
		runPlace = PlayerStateProcessBase::RunPlaceKind::capsule;
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
	//�ҋ@
	if (nowstateKind == State::Run && (stickstate.X == 0.0f && stickstate.Y == 0.0f) ||
		nowstateKind == State::Jump && onGround ||
		nowstateKind == State::NormalAttack && changeStateflg ||
		nowstateKind == State::Climb && changeStateflg || nowstateKind == State::Climb && gripPoint <= 0 ||
		nowstateKind == State::Squat && changeStateflg ||
		nowstateKind == State::Piercing && changeStateflg ||
		nowstateKind == State::Falling && onGround)
	{
		delete nowstate;
		nowstateKind = State::Idle;
		nowstate = new PlayerIdle(modelHandle, targetLookDirection);
	}

	//����
	if (nowstateKind != State::Run && nowstateKind != State::Climb && nowstateKind != State::NormalAttack && nowstateKind != State::Piercing && nowstateKind != State::Squat && onGround && (stickstate.X != 0.0f || stickstate.Y != 0.0f))
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//�W�����v
	if (nowstateKind != State::Jump && nowstateKind != State::NormalAttack && (Input::InputNumber::AButton & inputstate) == Input::InputNumber::AButton)
	{
		delete nowstate;
		onGround = false;
		jumpAfterLeaveFoot = false;
		nowstateKind = State::Jump;
		nowstate = new PlayerJump(modelHandle, moveVec);
	}

	//�˂��h���U��
	if (nowstateKind == State::Squat && canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::Piercing;
		nowstate = new PlayerPiercing(modelHandle, targetLookDirection);
	}

	//�ʏ�U���@(�˂��h���U���̌�ɔ��肵�Ȃ��ƈ�x�ʏ�U���ɓ����Ă��܂�)
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Piercing && nowstateKind != State::Jump && nowstateKind != State::Squat && canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}

	//�͂܂�
	if (nowstateKind != State::Climb && isCatch && !onGround && (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1 && gripPoint > 20)
	{
		delete nowstate;
		nowstateKind = State::Climb;
		nowstate = new PlayerClimb(modelHandle, targetLookDirection);
	}

	//���Ⴊ��
	if (onGround && nowstateKind != State::Piercing && nowstateKind != State::Squat && nowstateKind != State::Climb && !isCatch && (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1)
	{
		delete nowstate;
		nowstateKind = State::Squat;
		nowstate = new PlayerSquat(modelHandle, targetLookDirection);
	}

	//����
	if (fallFrame > 25 && !onGround && nowstateKind != State::Falling && nowstateKind != State::Jump && nowstateKind != State::Climb)
	{
		delete nowstate;
		nowstateKind = State::Falling;
		nowstate = new PlayerFalling(modelHandle, targetLookDirection);
	}
}

/// <summary>
/// ���������Ă��邩�m�F
/// </summary>
/// <param name="camera">�J����</param>
void Player::CheckOnGround(Camera* camera)
{
	//���n�����Ƃ�
	if ((nowstateKind == State::Jump && jumpAfterLeaveFoot && (!onGround && position.y < 0.0f || !onGround && onFootObject)) ||
		nowstateKind != State::Jump && (!onGround && position.y < 0.0f || !onGround && onFootObject))
	{
		onGround = true;
		moveVec.y = 0.0f;

		//��莞�ԗ������Ă����痎���_���[�W
		if (fallFrame >= 100)
		{
			HP -= fallFrame / 10;
			//�J�����U��
			camera->PlayShakingVertical(0.8f, 10, 20);
			//�U��
			StartJoypadVibration(DX_INPUT_PAD1, 500, 100, -1);
		}
	}

	//���Ă��Ȃ����
	if (position.y > 0.0f && !onFootObject)
	{
		onGround = false;
		runPlace = PlayerStateProcessBase::RunPlaceKind::air;
	}

	//�������Ă��Ȃ���Η���
	if (!onGround && nowstateKind != State::Climb)
	{
		fallFrame++;
		fallSpeed += Gravity;
	}
	else
	{
		fallFrame = 0;
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
	//�S�g
	wholebodyCapStart = VAdd(position, VGet(0.0f, 100.0f, 0.0f));
	wholebodyCapEnd = VAdd(position, VGet(0.0f, 50.0f, 0.0f));

	//��
	footCapStart = VAdd(position, VGet(0.0f, 10.0f, 0.0f));
	footCapEnd = VAdd(position, VGet(0.0f, 10.0f, 0.0f));
}

/// <summary>
/// �����蔻����X�V
/// </summary>
void Player::UpdateCollisionData()
{
	//�S�g
	bodyCollisionData.tag = ObjectTag::PlayerWholeBody;
	bodyCollisionData.position = position;
	bodyCollisionData.startPosition = wholebodyCapStart;
	bodyCollisionData.endPosition = wholebodyCapEnd;
	bodyCollisionData.radius = WholeBodyCapsuleRadius;
	bodyCollisionData.isCollisionActive = true;

	//��
	footCollisionData.tag = ObjectTag::PlayerFoot;
	footCollisionData.position = position;
	footCollisionData.startPosition = footCapStart;
	footCollisionData.endPosition = footCapEnd;
	footCollisionData.radius = FootCapsuleRadius;
	footCollisionData.isCollisionActive = true;
}

/// <summary>
/// �`��ʒu�C��(�A�j���[�V�����̎�ނɂ���Ă͍��W������Ă�������)
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
void Player::CollisionPushBack(CollisionData partsData, CollisionData hitObjectData)
{
	//���a�̍��v
	float radiusSum = hitObjectData.radius + partsData.radius;

	//�x�N�g���̃T�C�Y���v�Z
	//2�̐����̍ŒZ���������߂�
	float length = Segment_Segment_MinLength(partsData.startPosition, partsData.endPosition, hitObjectData.startPosition, hitObjectData.endPosition);
	float distance = radiusSum - length;

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

/// <summary>
/// �ǏՓˎ��̏���
/// </summary>
/// <param name="sinkIntoDepth">�߂荞�ݗ�</param>
void Player::WallHitProcess(VECTOR sinkIntoDepth)
{
	position = VAdd(position, sinkIntoDepth);
}

/// <summary>
/// �����Ɏg���f�[�^�̃Z�b�g
/// </summary>
void Player::MoveUseDataSet()
{
	moveUseData.inputState = inputstate;
	moveUseData.stickState = stickstate;
	moveUseData.position = position;
	moveUseData.capsuleStart = wholebodyCapStart;
	moveUseData.capsuleEnd = wholebodyCapEnd;
	moveUseData.capsuleRadius = WholeBodyCapsuleRadius;
	moveUseData.angle = angle;
	moveUseData.runPlace = runPlace;
	moveUseData.onFoot = onFootObject;
	moveUseData.putCloseVec = putCloseVec;
}

/// <summary>
/// �A�����͖h�~
/// </summary>
void Player::PreventionContinuousInput()
{
	//�A�����͖h�~
	if (canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		canInputX = false;
	}
	if (!canInputX && (Input::InputNumber::XButton & inputstate) != Input::InputNumber::XButton)
	{
		canInputX = true;
	}
}