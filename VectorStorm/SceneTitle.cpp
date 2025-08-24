#include "SceneTitle.h"
#include "Globals.h"

SceneTitle::SceneTitle() : Scene()
{
    up = down = left = right = false;
    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
    squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

    // Square position: In the middle of the screen
    squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
    squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;

}

Scene* SceneTitle::Update(float dt)
{
    SDL_Event e;

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
#ifndef __EMSCRIPTEN__
                running = false;
#endif
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

    if (up)
        squareRect.y = MAX(0, squareRect.y - 5);
    if (down)
        squareRect.y = MIN(SCREEN_HEIGHT - squareRect.h - 1, squareRect.y + 5);
    if (left)
        squareRect.x = MAX(0, squareRect.x - 5);
    if (right)
        squareRect.x = MIN(SCREEN_WIDTH - squareRect.w - 1, squareRect.x + 5);

    return this;
}

void SceneTitle::Draw()
{
    // Initialize renderer color white for the background
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Clear screen
    SDL_RenderClear(renderer);

    // Set renderer color red to draw the square
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    // Draw filled square
    SDL_RenderFillRect(renderer, &squareRect);

    // Update screen
    SDL_RenderPresent(renderer);

}