#pragma once
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <unordered_map>
#include "Scene.h"
#include "Utility.h"
#include <SDL.h>

extern bool running;

extern std::unordered_map<Scenes, Scene*> scenes;
extern Scene* currentScene;

extern SDL_Window* window;
extern SDL_Renderer* renderer;


#endif