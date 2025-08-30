#include <string>
#include <cmath>
#include "SceneGame.h"
#include "Globals.h"
#include "Level.h"
#include "Models.h"
#include "VectorFont.h"

const float MOVE_COOLDOWN_MAX = 0.125;
const float SHOOT_COOLDOWN_MAX = 0.125;
const float PLAYER_HIT_COOLDOWN_MAX = 0.5;
const long LEVEL_COMPLETE_POINTS = 100;
const long EXTRA_LIFE_POINTS = 250;

SceneGame::SceneGame() : Scene()
{    
    font = new VectorFont();    
    Init();
}

SceneGame::~SceneGame()
{
    delete font;
    for (auto iter = enemies.begin(); iter != enemies.end(); iter++)
        delete (*iter);
    enemies.clear();

    for (EnemyShot* shot : enemyShots)
        delete shot;
    enemyShots.clear();

    for (PlayerShot* shot : playerShots)
        delete shot;
    playerShots.clear();

}

void SceneGame::PlacePlayer()
{
    int idxPrev;
    int idxCurrent; 
    int pointCount = levels[levelIdx]->points.size();
    if (segmentIdx == 0)
    {
        if (levels[levelIdx]->closedShape)
        {
            idxCurrent = segmentIdx;
            idxPrev = pointCount - 1;
        }
        else
        {
            segmentIdx = 1;
            idxCurrent = segmentIdx;
            idxPrev = segmentIdx - 1;
        }
    } 
    else if (segmentIdx >= pointCount - 1)
    {
        segmentIdx = pointCount -1;
        idxCurrent = segmentIdx;
        idxPrev = segmentIdx - 1;
    }
    else
    {
        idxCurrent = segmentIdx;
        idxPrev = segmentIdx - 1;
    }

    px = ((levels[levelIdx]->points[idxPrev].x - levels[levelIdx]->points[idxCurrent].x) / 2);
    py = ((levels[levelIdx]->points[idxPrev].y - levels[levelIdx]->points[idxCurrent].y) / 2);
    float rad = atan2((float)(py), float(px));
    //rad += M_PI;
    px += levels[levelIdx]->points[idxCurrent].x;
    py += levels[levelIdx]->points[idxCurrent].y;

    player.color = YELLOW;
    player.scaleX = 2.0;
    player.scaleY = 2.0;
    player.x = px;
    player.y = py;
    player.angle = rad;
}

void SceneGame::Init()
{
    GameOver = false;
    extraLifeCountdown = EXTRA_LIFE_POINTS;
    up = down = left = right = fire = false;
    playerHitCooldown = 0.0f;
    moveCooldown = 0;
    shootCooldown = 0;
    levelIdx = 0;
    levels[levelIdx]->Init();
    segmentIdx = 0;
    for (auto iter = enemies.begin(); iter != enemies.end(); iter++)
        delete (*iter);
    enemies.clear();
    for (auto& shot : playerShots)
        delete shot;
    playerShots.clear();
    for (auto& shot : enemyShots)
        delete shot;
    enemyShots.clear();

    PlacePlayer();
    points = 0;
    playerLives = 3;
}

Scene* SceneGame::Update(float dt)
{
    Scene* scene = this;
    SDL_Event e;

    fire = false;

    // Wait indefinitely for the next available event
    while (SDL_PollEvent(&e))
    {

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                scene = scenes[Scenes::SCENE_TITLE];
                scene->Init();
                break;
/*
            case SDLK_PAGEUP:
                levelIdx--;
                if (levelIdx < 0)
                    levelIdx = levels.size() - 1;
                segmentIdx = 0;
                levels[levelIdx]->Init();
                PlacePlayer();
                break;
            case SDLK_PAGEDOWN:
                levelIdx++;
                if (levelIdx >= levels.size())
                    levelIdx = 0;
                levels[levelIdx]->Init();
                segmentIdx = 0;
                PlacePlayer();
                break;
*/
            case SDLK_SPACE:
                fire = false;
                break;
            case SDLK_UP:
                up = false;
                break;
            case SDLK_DOWN:
                down = false;
                break;
            case SDLK_LEFT:
                left = false;
                break;
            case SDLK_RIGHT:
                right = false;
                break;
            }
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_SPACE:
                fire = true;
                break;
            case SDLK_UP:
                up = true;
                break;
            case SDLK_DOWN:
                down = true;
                break;
            case SDLK_LEFT:
                left = true;
                break;
            case SDLK_RIGHT:
                right = true;
                break;
            }
        }
    }
    if (moveCooldown > 0.0)
        moveCooldown = MAX(0.0, moveCooldown - dt);

    if (shootCooldown > 0.0)
        shootCooldown = MAX(0.0, shootCooldown - dt);

    if (left && moveCooldown <= 0.0f)
    { 
        segmentIdx++;
        moveCooldown = MOVE_COOLDOWN_MAX;        
    }
    if (right && moveCooldown <= 0.0f)
    {
        segmentIdx--;
        moveCooldown = MOVE_COOLDOWN_MAX;

    }
    if (segmentIdx >= levels[levelIdx]->points.size())
    {
        if (levels[levelIdx]->closedShape)
            segmentIdx = 0;
        else
            segmentIdx = levels[levelIdx]->points.size() - 1;
    } 
    else if (segmentIdx < 0)
    {
        if (levels[levelIdx]->closedShape)
            segmentIdx = levels[levelIdx]->points.size() - 1;
        else
            segmentIdx = 0;
    }
    if ((left || right) && moveCooldown == MOVE_COOLDOWN_MAX)
        PlacePlayer();

    if (fire && shootCooldown <= 0)
    {
        if (sfx[AudioClips::AUDIO_ZAP] != nullptr)
        {
            Mix_PlayChannel(-1, sfx[AudioClips::AUDIO_ZAP], 0);
        }
        shootCooldown = SHOOT_COOLDOWN_MAX;
        PlayerShot* shot = new PlayerShot();
        shot->Init(px, py, segmentIdx);
        playerShots.push_back(shot);
    }

    std::list<Enemy*>::iterator iter = enemies.begin();
    levels[levelIdx]->Update(dt);
    // Deleting dead enemies, update the rest.
    while (iter != enemies.end()) {
        if ((*iter)->IsDead()) {
            delete *iter;
            iter = enemies.erase(iter);
            continue;
        }
        else
        {
            (*iter)->Update(dt);
            EnemyShot* shot = (EnemyShot*)(*iter)->SpawnShot();
            if (shot != nullptr)
            {
                if (sfx[AudioClips::ENEMY_ZAP] != nullptr)
                {
                    Mix_PlayChannel(-1, sfx[AudioClips::ENEMY_ZAP], 0);
                }
                enemyShots.push_back(shot);
            }
            if ((*iter)->Collide({ px, py }, player.GetRadius()))
            {
                PlayerHit();
                (*iter)->Hit();
            }
        }
        iter++;
    }

    std::list<EnemyShot*>::iterator eShot = enemyShots.begin();
    while (eShot != enemyShots.end())
    {
        if ((*eShot)->IsDead())
        {
            delete* eShot;
            eShot = enemyShots.erase(eShot);
            continue;
        }
        else
        {
            Point2Df playerPoint = { px, py };
            if ((*eShot)->Collide(playerPoint, player.GetRadius()))
            {
                PlayerHit();
                (*eShot)->Destroy();
            }
        }
        eShot++;
    }

    std::list<PlayerShot*>::iterator pShot = playerShots.begin();
    while (pShot != playerShots.end())
    {
        if ((*pShot)->IsDead())
        {
            delete* pShot;
            pShot = playerShots.erase(pShot);
            continue;
        }
        else
        {
            for (auto& enemy : enemies)
            {
                Point2Df enemyPoint = { enemy->x, enemy->y };
                if ((*pShot)->Collide(enemyPoint, enemy->GetRadius()))
                {
                    int pts = enemy->Hit();
                    points += pts;
                    extraLifeCountdown -= pts;
                    if (extraLifeCountdown <= 0)
                    {
                        playerLives++;
                        extraLifeCountdown = EXTRA_LIFE_POINTS;
                        if (sfx[AudioClips::EXTRA_LIFE] != nullptr)
                        {
                            Mix_PlayChannel(-1, sfx[AudioClips::EXTRA_LIFE], 0);
                        }
                    }
                }
            }
        }
        pShot++;
    }

    if (playerHitCooldown > 0.0f)
    {
        playerHitCooldown = MAX(0.0f, playerHitCooldown - dt);
    }

    Enemy* enemy = levels[levelIdx]->SpawnEnemy();
    if (enemy != nullptr)
        enemies.push_back(enemy);

    for (EnemyShot* shot : enemyShots)
        shot->Update(dt);

    for (PlayerShot* shot : playerShots)
        shot->Update(dt);

    // Next level?
    if (levels[levelIdx]->AllEnemiesSpawned() && enemies.size() == 0 && enemyShots.size() == 0)
    {
        points += LEVEL_COMPLETE_POINTS;
        extraLifeCountdown -= LEVEL_COMPLETE_POINTS;
        if (extraLifeCountdown <= 0)
        {
            extraLifeCountdown += EXTRA_LIFE_POINTS;
            playerLives++;
            if (sfx[AudioClips::EXTRA_LIFE] != nullptr)
            {
                Mix_PlayChannel(-1, sfx[AudioClips::EXTRA_LIFE], 0);
            }
        }

        for (auto& shot : playerShots)
            delete shot;
        playerShots.clear();

        levelIdx++;
        if (levelIdx >= levels.size())
            levelIdx = 0;
        segmentIdx = 0;
        levels[levelIdx]->Init();
        PlacePlayer();
    }

    return (GameOver ? scenes[Scenes::SCENE_TITLE] : scene);
}

void SceneGame::Draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);

    // Draw the status display
    std::string text = "LEVEL " + std::to_string(levelIdx + 1);
    int textWidth, textHeight;
    font->MeasureText(text, &textWidth, &textHeight);
    float tx, ty;
    ty = textHeight * 2;
    tx = (SCREEN_WIDTH - textWidth) / 2;
    font->DrawText(text, tx, ty, WHITE);

    text = "POINTS: " + std::to_string(points);
    font->MeasureText(text, &textWidth, &textHeight);
    ty = textHeight * 2;
    tx = (SCREEN_WIDTH - textWidth - ty);
    font->DrawText(text, tx, ty, WHITE);

    text = " X " + std::to_string(playerLives);
    font->MeasureText(text, &textWidth, &textHeight);
    ty = textHeight * 2;
    float sx = player.scaleX;
    float sy = player.scaleY;
    float pa = player.angle;
    player.angle = 0.0f;
    player.scaleX = 2.0;
    player.scaleY = 2.0;

    player.x = ty;
    player.y = ty;
    player.Draw();
    tx = ty * 2;
    font->DrawText(text, tx, ty, WHITE);
    player.scaleX = sx;
    player.scaleY = sy;
    player.x = px;
    player.y = py;
    player.angle = pa;

    Level* l = levels[levelIdx];
    int width, height;

    l->Draw();
    int segment = segmentIdx - 1;
    if (segment < 0)
        segment = l->points.size() - 1;
    SDL_SetRenderDrawColor(renderer, player.color.r, player.color.g, player.color.b, player.color.a);
    SDL_RenderDrawLine(renderer, l->pointsInner[segment].x, l->pointsInner[segment].y, l->points[segment].x, l->points[segment].y);
    SDL_RenderDrawLine(renderer, l->pointsInner[segmentIdx].x, l->pointsInner[segmentIdx].y, l->points[segmentIdx].x, l->points[segmentIdx].y);    

    for (PlayerShot* shot : playerShots)
    {
        shot->Draw();
    }

    for (EnemyShot* shot : enemyShots)
    {
        shot->Draw();
    }

    for (auto iter = enemies.begin(); iter != enemies.end(); iter++)
    {
        if (!(*iter)->IsDead())
            (*iter)->Draw();
    }

    player.Draw();

    // Update screen
    SDL_RenderPresent(renderer);

}

void SceneGame::PlayerHit()
{
    if (playerHitCooldown <= 0.0f)
    {
        playerHitCooldown = PLAYER_HIT_COOLDOWN_MAX;
        playerLives--;
        if (sfx[AudioClips::PLAYER_DESTROY] != nullptr)
        {
            Mix_PlayChannel(-1, sfx[AudioClips::PLAYER_DESTROY], 0);
        }
        if (playerLives <= 0)
            GameOver = true;
    }
}