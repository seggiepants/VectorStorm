#include <string>
#include <cmath>
#include "SceneGame.h"
#include "Globals.h"
#include "Level.h"
#include "Models.h"
#include "VectorFont.h"

const float MOVE_COOLDOWN_MAX = 0.125;
const float SHOOT_COOLDOWN_MAX = 0.125;

SceneGame::SceneGame() : Scene()
{    
    font = new VectorFont();    
    Init();
}

SceneGame::~SceneGame()
{
    delete font;
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
    up = down = left = right = fire = false;
    moveCooldown = 0;
    shootCooldown = 0;
    levelIdx = 0;
    segmentIdx = 0;
    PlacePlayer();
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
            shootCooldown = SHOOT_COOLDOWN_MAX;
        }
    }

    return scene;
}

void SceneGame::Draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);

    Level* l = levels[levelIdx];
    int width, height;
    SDL_SetRenderDrawColor(renderer, l->color.r, l->color.g, l->color.b, l->color.a);

    SDL_RenderDrawLine(renderer, l->pointsInner[0].x, l->pointsInner[0].y, l->points[0].x, l->points[0].y);
    if (l->closedShape)
    {   
        SDL_RenderDrawLine(renderer, l->pointsInner[l->pointsInner.size() - 1].x, l->pointsInner[l->pointsInner.size() - 1].y, l->pointsInner[0].x, l->pointsInner[0].y);
        SDL_RenderDrawLine(renderer, l->points[l->points.size() - 1].x, l->points[l->points.size() - 1].y, l->points[0].x, l->points[0].y);
    }
    for (int i = 1; i < l->points.size(); i++)
    {
        SDL_RenderDrawLine(renderer, l->pointsInner[i - 1].x, l->pointsInner[i - 1].y, l->pointsInner[i].x, l->pointsInner[i].y);
        SDL_RenderDrawLine(renderer, l->pointsInner[i].x, l->pointsInner[i].y, l->points[i].x, l->points[i].y);
        SDL_RenderDrawLine(renderer, l->points[i - 1].x, l->points[i - 1].y, l->points[i].x, l->points[i].y);
    }

    int segment = segmentIdx - 1;
    if (segment < 0)
        segment = l->points.size() - 1;
    SDL_SetRenderDrawColor(renderer, player.color.r, player.color.g, player.color.b, player.color.a);
    SDL_RenderDrawLine(renderer, l->pointsInner[segment].x, l->pointsInner[segment].y, l->points[segment].x, l->points[segment].y);
    SDL_RenderDrawLine(renderer, l->pointsInner[segmentIdx].x, l->pointsInner[segmentIdx].y, l->points[segmentIdx].x, l->points[segmentIdx].y);


    player.Draw();

    // Update screen
    SDL_RenderPresent(renderer);

}