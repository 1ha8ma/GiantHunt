#pragma once

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//‰Šú‰»
	void Initialize();
	//XV
	void Update();
	//•`‰æ
	void Draw();

	VECTOR GetPosition() { return position; }
private:
	int modelHandle;
	VECTOR position;
};