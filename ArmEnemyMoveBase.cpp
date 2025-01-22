#include<vector>
#include"DxLib.h"
#include"ArmEnemyMoveBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemyMoveBase::ArmEnemyMoveBase(int modelHandle,float modelScale)
{
	this->modelHandle = modelHandle;
	this->modelScale = modelScale;
}

/// <summary>
/// フレームの回転処理
/// </summary>
/// <param name="frameIndex">フレーム番号</param>
/// <param name="Xaxis">X軸回転</param>
/// <param name="Yaxis">Y軸回転</param>
/// <param name="Zaxis">Z軸回転</param>
/// <returns>回転させるための行列</returns>
MATRIX ArmEnemyMoveBase::FrameRotateProcess(int frameIndex, float Xaxis, float Yaxis, float Zaxis)
{
	//親フレームの取得
	int ParentFrame = MV1GetFrameParent(modelHandle, frameIndex);

	//モデルの拡大率に従って移動距離を補正する準備
	float correctionScale;
	if (0 != modelScale)
	{
		correctionScale = 1 / modelScale;
	}
	else
	{
		return MGetIdent();
	}

	//相対座標分の平行移動行列を取得
	MATRIX MTranslate;
	if (-2 != ParentFrame)
	{
		//親子フレームの座標の取得
		VECTOR vecParent = MV1GetFramePosition(modelHandle, ParentFrame);
		VECTOR vecChild = MV1GetFramePosition(modelHandle, frameIndex);

		//親を基準にした子の相対座標を取得
		VECTOR vecRerativPar2Chi = VSub(vecChild, vecParent);
		//モデルの拡大率によって相対距離を補正
		vecRerativPar2Chi = VScale(vecRerativPar2Chi, correctionScale);
		MTranslate = MGetTranslate(vecRerativPar2Chi);
	}
	else
	{
		MTranslate = MGetIdent();
	}

	//それぞれの軸に沿って回転する行列を取得
	MATRIX MXaxis = MGetRotX(Xaxis);
	MATRIX MYaxis = MGetRotY(Yaxis);
	MATRIX MZaxis = MGetRotZ(Zaxis);

	////遡って親フレームの回転要素の取得
	//std::vector<MATRIX> MParentsRotates;
	//while (-2 != ParentFrame && -1 != ParentFrame)
	//{
	//	//親フレーム座標を取得し、そこから回転要素を抽出
	//	MATRIX MParentFrame = MV1GetFrameLocalMatrix(modelHandle, ParentFrame);
	//	MATRIX MParentRotate = MGetRotElem(MParentFrame);
	//	//回転行列の逆行列=回転の方向を逆にする
	//	MATRIX MInvParentRotate = MInverse(MParentRotate);
	//	//順に追加
	//	MParentsRotates.push_back(MInvParentRotate);

	//	//更に親のフレームを取得
	//	ParentFrame = MV1GetFrameParent(modelHandle, ParentFrame);
	//}
	////取得した祖先たちの回転行列をより中枢の方からかけて、平行移動のベクトルを補正する
	//for (int i = MParentsRotates.size() - 1; i >= 0; i--)
	//{
	//	MTranslate = MMult(MTranslate, MParentsRotates[i]);
	//}
	////平行移動ベクトルに生じうる回転成分を消す
	//MTranslate.m[0][0] = 1;	MTranslate.m[0][1] = 0;	MTranslate.m[0][2] = 0;
	//MTranslate.m[1][0] = 0;	MTranslate.m[1][1] = 1;	MTranslate.m[1][2] = 0;
	//MTranslate.m[2][0] = 0;	MTranslate.m[2][1] = 0;	MTranslate.m[2][2] = 1;

	//軸毎に回転させてから平行移動を実行する
	MATRIX MReturn = MMult(MMult(MMult(MXaxis, MYaxis), MZaxis), MTranslate);

	return MReturn;
}