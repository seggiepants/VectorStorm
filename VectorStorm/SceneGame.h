#pragma once
#ifndef __SCENE_GAME_H__
#include <list>
#include "Scene.h"
#include "VectorFont.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "PlayerShot.h"

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
	void PlayerHit();
	VectorFont* font;
	float moveCooldown;
	float shootCooldown;
	std::list<Enemy*> enemies;
	std::list<EnemyShot*> enemyShots;
	std::list<PlayerShot*> playerShots;
	bool up, down, left, right, fire;
	bool pause;
	float px, py;
	float segmentIdx;
	int playerLives;
	float playerHitCooldown;
	bool GameOver;
	long points;
	long extraLifeCountdown;
};
#endif