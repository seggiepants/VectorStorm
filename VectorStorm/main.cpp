#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_mixer.h>

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

    // Free audio samples and close audio.
    for (auto& iter : sfx)
    {
        if (iter.second != nullptr)
        {
            Mix_FreeChunk(iter.second);
            iter.second = nullptr;
        }
    }
    Mix_CloseAudio();

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
        if (currentScene != next)
            next->Init();
        currentScene = next;
    }
    
    if (!running)
        shutdown();

}

int main(int argc, char* argv[])
{

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if (result < 0)
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    result = Mix_AllocateChannels(4);
    if (result < 0)
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }

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
            Mix_Chunk* zap = Mix_LoadWAV("res/laserShoot.wav");
            if (zap != nullptr)
                sfx.emplace(AudioClips::AUDIO_ZAP, zap);
            else
                printf("Could not load wav file.");

            zap = Mix_LoadWAV("res/enemyShoot.wav");
            if (zap != nullptr)
                sfx.emplace(AudioClips::ENEMY_ZAP, zap);
            else
                printf("Could not load wav file.");

            zap = Mix_LoadWAV("res/playerExplosion.wav");
            if (zap != nullptr)
                sfx.emplace(AudioClips::PLAYER_DESTROY, zap);
            else
                printf("Could not load wav file.");

            zap = Mix_LoadWAV("res/enemyExplosion.wav");
            if (zap != nullptr)
                sfx.emplace(AudioClips::ENEMY_DESTROY, zap);
            else
                printf("Could not load wav file.");

            zap = Mix_LoadWAV("res/extraLife.wav");
            if (zap != nullptr)
                sfx.emplace(AudioClips::EXTRA_LIFE, zap);
            else
                printf("Could not load wav file.");

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