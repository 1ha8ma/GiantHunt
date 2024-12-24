#include"DxLib.h"
//#include"CollisionData.h"
#include"CollisionManager.h"

//������
CollisionManager* CollisionManager::collisionManager = nullptr;
std::vector<CollisionData*> CollisionManager::collisionDataList;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
	collisionDataList.clear();
}

/// <summary>
/// ������
/// </summary>
void CollisionManager::Initialize()
{

}

/// <summary>
/// �C���X�^���X�Q�b�g
/// </summary>
/// <returns>�C���X�^���X</returns>
CollisionManager* CollisionManager::GetInstance()
{
	if (collisionManager == nullptr)
	{
		collisionManager = new CollisionManager();
	}

	return collisionManager;
}

/// <summary>
/// �����蔻����ǉ�
/// </summary>
/// <param name="data">�f�[�^</param>
void CollisionManager::AddCollisionData(CollisionData* data)
{
	collisionDataList.push_back(data);
}

/// <summary>
/// �S�Ă̓����蔻�菈��
/// </summary>
void CollisionManager::Update()
{
	for (int i = 0; i < collisionDataList.size(); i++)
	{
		for (int j = 0; j < collisionDataList.size(); j++)
		{
			//�������̂�������X�L�b�v
			if (i == j)
			{
				continue;
			}

			//�ǂ̃^�C�v�̓����蔻����s�������ׂ�
			CollisionData data1 = *collisionDataList[i];
			CollisionData data2 = *collisionDataList[j];

			//�����蔻����s���ė~�������m�F
			if (data1.isCollisionActive && data2.isCollisionActive)
			{
				//�v���C���[�Ɩ�
				if (data1.tag == ObjectTag::Player && data2.tag == ObjectTag::Wood1 || data1.tag == ObjectTag::Player && data2.tag == ObjectTag::Wood2)
				{
					bool hit = CapsuleWithCapsule(data1.startPosition, data1.endPosition, data1.radius, data2.startPosition, data2.endPosition, data2.radius);

					if (hit)
					{
						data1.HitProcess(data2);
						data2.HitProcess(data1);
					}
				}
			}
		}
	}
}

/// <summary>
/// �J�v�Z���ǂ����̓����蔻��
/// </summary>
/// <param name="capsuleStart1">�J�v�Z��1�n�_</param>
/// <param name="capsuleEnd1">�J�v�Z��1�I�_</param>
/// <param name="capsuleRadius1">�J�v�Z��1���a</param>
/// <param name="capsuleStart2">�J�v�Z��2�n�_</param>
/// <param name="capsuleEnd2">�J�v�Z��2�I�_</param>
/// <param name="capsuleRadius2">�J�v�Z��2���a</param>
/// <returns>�������Ă��邩</returns>
bool CollisionManager::CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2)
{
	bool hit = false;

	//�J�v�Z���Ԃ̍ŒZ����
	float length = Segment_Segment_MinLength(capsuleStart1, capsuleEnd1, capsuleStart2, capsuleEnd2);

	//����
	if (length < capsuleRadius1 + capsuleRadius2)
	{
		hit = true;
	}

	return hit;
}