#pragma once

class ArmEnemyMove
{
public:
	//æ‚Á‚Ä‚¢‚éêŠ
	enum class RidePlace :int
	{
		None,		//æ‚Á‚Ä‚¢‚È‚¢
		Upperarm,	//ã˜r
		Forearm,	//‘O˜r
		Hand,		//è
	};

	ArmEnemyMove(int modelHandle);
	~ArmEnemyMove();

	void Initialize();
	
	void Update(RidePlace playerRidePlace);

private:


	void Idle();//‘Ò‹@




	int modelHandle;

};