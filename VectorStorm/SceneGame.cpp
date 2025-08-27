#include <string>
#include <cmath>
#include "SceneGame.h"
#include "Globals.h"
#include "Level.h"
#include "Models.h"
#include "VectorFont.h"

SceneGame::SceneGame() : Scene()
{    
    font = new VectorFont();    
    Init();
}

SceneGame::~SceneGame()
{
    delete font;
}

void SceneGame::Init()
{
    up = down = left = right = fire = false;

    player.color = YELLOW;
    player.scaleX = 2.0;
    player.scaleY = 2.0;
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.angle = 0.0f;

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

    if (l->closedShape)
    {    
        SDL_RenderDrawLine(renderer, l->pointsInner[l->pointsInner.size() - 1].x, l->pointsInner[l->pointsInner.size() - 1].y, l->pointsInner[0].x, l->pointsInner[0].y);
        SDL_RenderDrawLine(renderer, l->pointsInner[0].x, l->pointsInner[0].y, l->points[0].x, l->points[0].y);
        SDL_RenderDrawLine(renderer, l->points[l->points.size() - 1].x, l->points[l->points.size() - 1].y, l->points[0].x, l->points[0].y);
    }
    for (int i = 1; i < l->points.size(); i++)
    {
        SDL_RenderDrawLine(renderer, l->pointsInner[i - 1].x, l->pointsInner[i - 1].y, l->pointsInner[i].x, l->pointsInner[i].y);
        SDL_RenderDrawLine(renderer, l->pointsInner[i].x, l->pointsInner[i].y, l->points[i].x, l->points[i].y);
        SDL_RenderDrawLine(renderer, l->points[i - 1].x, l->points[i - 1].y, l->points[i].x, l->points[i].y);
    }

    player.Draw();

    // Update screen
    SDL_RenderPresent(renderer);

}