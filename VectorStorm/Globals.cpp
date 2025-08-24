#include "Globals.h"

bool running;

std::unordered_map<Scenes, Scene*> scenes = std::unordered_map<Scenes, Scene*>();
Scene* currentScene = nullptr;

SDL_Window* window;
SDL_Renderer* renderer;