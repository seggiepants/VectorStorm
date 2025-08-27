#pragma once
#ifndef __SCENE_GAME_H__
#include "Scene.h"
#include "VectorFont.h"

class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Init() override;
	Scene* Update(float dt) override;
	void Draw() override;
private:
	void PlacePlayer();
	VectorFont* font;
	float moveCooldown;
	float shootCooldown;
	bool up, down, left, right, fire;
	bool pause;
	float px, py;
	float segmentIdx;
};
#endif