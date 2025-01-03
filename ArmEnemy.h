#pragma once

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	VECTOR GetPosition() { return position; }
private:
	int modelHandle;
	VECTOR position;
};