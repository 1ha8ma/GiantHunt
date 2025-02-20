#pragma once
#include"SceneBase.h"

class Input;
class Loader;

class DemoScene :public SceneBase
{
public:
	DemoScene();
	~DemoScene()override;

	void Initialize()override;
	SceneBase* Update()override;
	void Draw()override;

private:
	Loader* loader;
	Input* input;

	int movieHandle;
};