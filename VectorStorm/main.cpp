#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

#include "Globals.h"
#include "Utility.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "Level.h"
#include "Models.h"

// Event loop exit flag

long last = 0;
float deltaTime = 0.0;


void shutdown()
{
    LevelDestroy();
    scenes.clear();

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();  /* this should "kill" the app. */
#else
    exit(0);
#endif
}

static void loop(void)
{
    long now = SDL_GetTicks();
    //deltatime is in seconds
    if (now > last) {
        deltaTime = ((float)(now - last)) / 1000;
        last = now;
    }

    if (currentScene != nullptr)
    {
        Scene* next = currentScene->Update(deltaTime);
        currentScene->Draw();
        currentScene = next;
    }
    
    if (!running)
        shutdown();

}

int main(int argc, char* argv[])
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
            "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    window = SDL_CreateWindow("Vector Storm",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    if (!window)
    {
        printf("Window could not be created!\n"
            "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer)
        {
            printf("Renderer could not be created!\n"
                "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {   
            LevelInit();
            ModelInit();
            scenes.emplace(Scenes::SCENE_TITLE, new SceneTitle());
            scenes.emplace(Scenes::SCENE_GAME, new SceneGame());
            currentScene = scenes[Scenes::SCENE_TITLE];
            currentScene->Init();

            running = true;

            // Event loop
#ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(loop, 0, 1);
#else
            while (running) { loop(); }
#endif
            
        }
    }
    return 0;
}