#pragma once

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	VECTOR GetPosition() { return position; }
private:
	int modelHandle;
	VECTOR position;
};