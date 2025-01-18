#pragma once

class StageBase
{
public:
	StageBase() {};
	virtual ~StageBase() {};

	//ポジションを押し戻し
	VECTOR PushBackPosition(VECTOR position, VECTOR moveVec);

	//更新
	virtual void Update()abstract;
	//描画
	virtual void Draw()abstract;

protected:
	const VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);	//中心点
	
	int modelHandle;		//モデルハンドル
	VECTOR position;
	float circleRadius;		//円の半径
	float stageScale;
};