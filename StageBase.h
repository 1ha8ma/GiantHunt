#pragma once

class StageBase
{
public:
	//ポジションを押し戻し
	VECTOR PushBackPosition(VECTOR position, VECTOR moveVec);
	//描画
	void Draw();

protected:
	const VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);	//中心点
	
	int modelHandle;		//モデルハンドル
	VECTOR position;
	float circleRadius;		//円の半径
	float stageScale;
};