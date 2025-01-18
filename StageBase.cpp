#include<math.h>
#include"DxLib.h"
#include"Loader.h"
#include"StageBase.h"

/// <summary>
/// 移動ベクトルの押し戻し
/// </summary>
/// <param name="position">現在のポジション</param>
/// <param name="moveVec">移動ベクトル</param>
/// <returns>押し戻し量</returns>
VECTOR StageBase::PushBackPosition(VECTOR position, VECTOR moveVec)
{
	VECTOR backVec = VGet(0, 0, 0);
	VECTOR nextPos = VAdd(position, moveVec);//移動後
	nextPos.y = 0.0f;

	//中心からの距離を取る
	float calc = pow((nextPos.x - centerPosition.x), 2.0f) + pow((nextPos.z - centerPosition.z), 2.0f);
	float distance = sqrtf(calc);

	//距離が半径以上なら
	if (distance > circleRadius)
	{
		while (1)
		{
			backVec = VAdd(backVec, VGet(0.1f, 0.0f, 0.1f));//戻す量を加算
			VECTOR backafterPos = VSub(nextPos, backVec);

			//中心からの距離を取る
			float calc = pow((backafterPos.x - centerPosition.x), 2.0f) + pow((backafterPos.z - centerPosition.z), 2.0f);
			float distance = sqrtf(calc);

			//半径以内まで戻す
			if (distance < circleRadius)
			{
				break;
			}
		}
	}

	return backVec;
}

/// <summary>
/// 描画
/// </summary>
//void StageBase::Draw()
//{
//	MV1DrawModel(modelHandle);
//}