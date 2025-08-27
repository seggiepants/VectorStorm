#pragma once
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <unordered_map>
#include "Scene.h"
#include "Utility.h"
#include <SDL.h>
#include <SDL_mixer.h>

extern bool running;

extern std::unordered_map<Scenes, Scene*> scenes;
extern Scene* currentScene;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern SDL_Color BLACK;
extern SDL_Color WHITE;
extern SDL_Color RED;
extern SDL_Color GREEN;
extern SDL_Color BLUE;
extern SDL_Color CYAN;
extern SDL_Color MAGENTA;
extern SDL_Color YELLOW;

extern std::unordered_map<AudioClips, Mix_Chunk*> sfx;

#endif