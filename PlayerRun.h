#pragma once
#include"PlayerStateProcessBase.h"

class PlayerRun :public PlayerStateProcessBase
{
public:
	PlayerRun(int modelHandle,VECTOR prevtargetLookDirection);
	~PlayerRun()override;

	//������
	void Initialize()override {};
	//�X�V
	bool Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)override;

private:
	const float Speed = 20.0f;      //�X�s�[�h

	//�ړ�����
	void Move(UsePlayerData playerData,Camera camera);

	bool moveflg;	//�ړ����Ă��邩
};