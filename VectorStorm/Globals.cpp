#include "Globals.h"

bool running;

std::unordered_map<Scenes, Scene*> scenes = std::unordered_map<Scenes, Scene*>();
Scene* currentScene = nullptr;

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Color BLACK = { 0, 0, 0, 255 };
SDL_Color WHITE = { 255, 255, 255, 255 };
SDL_Color RED = { 255, 0, 0, 255 };
SDL_Color GREEN = { 0, 255, 0, 255 };
SDL_Color BLUE = { 0, 0, 255, 255 };
SDL_Color CYAN = { 0, 255, 255, 255 };
SDL_Color MAGENTA = { 255, 0, 255, 255 };
SDL_Color YELLOW = { 255, 255, 0, 255 };