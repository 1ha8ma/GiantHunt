#pragma once

class ArmEnemyMove
{
public:
	//����Ă���ꏊ
	enum class RidePlace :int
	{
		None,		//����Ă��Ȃ�
		Upperarm,	//��r
		Forearm,	//�O�r
		Hand,		//��
	};

	ArmEnemyMove(int modelHandle);
	~ArmEnemyMove();

	void Initialize();
	
	void Update(RidePlace playerRidePlace);

private:


	void Idle();//�ҋ@




	int modelHandle;

};