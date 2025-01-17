#include"DxLib.h"
#include"Input.h"
#include"Camera.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"PlayerPiercing.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="prevtargetLookDirection">�O�̃L�����N�^�[�̌���</param>
PlayerPiercing::PlayerPiercing(int modelHandle, VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Squat);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	targetLookDirection = prevtargetLookDirection;

	//private�ϐ�������
	changeState = false;
	attackPower = 0;
	attackCapsuleStart = VGet(0.0f, -1000.0f, 0.0f);
	attackCapsuleEnd = VGet(0.0f, -1000.0f, 0.0f);
	attackChargeFlame = 0;
	attackEnd = false;
	rotate = VGet(0, 0, 0);
	attack = false;
	canInputX = false;
	attackHit = false;

	//�����蔻����
	collisionManager = collisionManager->GetInstance();
	attackCollisionData.HitProcess = std::bind(&PlayerPiercing::OnHitObject, this, std::placeholders::_1);
	collisionManager->AddCollisionData(&attackCollisionData);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerPiercing::~PlayerPiercing()
{
	//�����蔻�����菜��
	collisionManager->RemoveCollisionData(&attackCollisionData);
	//�t���[��������
	MV1ResetFrameUserLocalMatrix(modelHandle, RightArmFrameNumber);
	//�A�j���[�V�����I��
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="angle">�p�x</param>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˃I�u�W�F�N�g���</param>
/// <returns>�X�e�[�g�ύX</returns>
bool PlayerPiercing::Update(VECTOR position,float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)
{
	moveVec = VGet(0, 0, 0);

	//�A�����͖h�~
	if (!canInputX && (Input::InputNumber::XButton & inputstate) != Input::InputNumber::XButton)
	{
		canInputX = true;
	}

	PiercingAttack(inputstate);
	UpdateCollisionData();

	//�����ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1 || attackEnd)
	{
		changeState = true;
	}

	return changeState;
}

void PlayerPiercing::Draw()
{
	DrawCapsule3D(attackCapsuleStart, attackCapsuleEnd, AttackCapsuleRadius, 8, GetColor(255, 105, 180), GetColor(255, 105, 180), false);
}

/// <summary>
/// �˂��h���U��
/// </summary>
void PlayerPiercing::PiercingAttack(int inputstate)
{
	if (!attack)
	{
		//�t���[�����Z
		attackChargeFlame++;

		//�r���グ��
		if (rotate.z < MaxSwingUp)
		{
			rotate.z += SwingUpSpeed;
		}
	}

	//X�{�^�����������ƍU��
	if (canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		attackPower = LowestAttackPower + attackChargeFlame / 5;

		attack = true;
	}

	//�U���J�v�Z���ݒ�
	if (attack)
	{
		VECTOR capsuleCenter = MV1GetFramePosition(modelHandle, RightHandFrameNumber);
		attackCapsuleStart = VAdd(capsuleCenter, VGet(0.0f, -50.0f, 0.0f));
		attackCapsuleEnd = VAdd(capsuleCenter, VGet(0.0f, 0.0f, 0.0f));
	}

	//�r��U�艺�낷
	if (attack)
	{
		rotate.z -= SwingDownSpeed;

		if (rotate.z < 0.0f)
		{
			attackEnd = true;
		}
	}

	//�U�����������Ă�����
	if (attackHit)
	{
		attack = false;
	}

	//�r�t���[����]
	MV1SetFrameUserLocalMatrix(modelHandle, RightArmFrameNumber, MGetRotZ(rotate.z));
}

/// <summary>
/// �Փˌ㏈��
/// </summary>
/// <param name="objectData">�Փ˂����I�u�W�F�N�g</param>
void PlayerPiercing::OnHitObject(CollisionData objectData)
{
	if (/*�r�̓G*/
		objectData.tag == ObjectTag::Upperarm_E1 ||
		objectData.tag == ObjectTag::Forearm_E1 ||
		objectData.tag == ObjectTag::Hand_E1)
	{
		attackHit = true;
	}
}

/// <summary>
/// �����蔻����X�V
/// </summary>
void PlayerPiercing::UpdateCollisionData()
{
	attackCollisionData.tag = ObjectTag::Attack_P;
	attackCollisionData.startPosition = attackCapsuleStart;
	attackCollisionData.endPosition = attackCapsuleEnd;
	attackCollisionData.radius = AttackCapsuleRadius;
	attackCollisionData.attackPower = attackPower;
	attackCollisionData.isCollisionActive = attack;
}