#include <string>
#include "SceneTitle.h"
#include "Globals.h"
#include "Models.h"
#include "VectorFont.h"

SceneTitle::SceneTitle() : Scene()
{
    font = new VectorFont();

    menuItems.clear();
    menuItems.push_back("PLAY");
#ifndef __EMSCRIPTEN__
    menuItems.push_back("EXIT");
#endif
    menuIndex = 0;
    Init();
}

void SceneTitle::Init()
{
    up = down = left = right = false;

    player.color = YELLOW;
    player.scaleX = 10.0;
    player.scaleY = 10.0;
    player.x = SCREEN_WIDTH / 2;
    player.y = 5 * (SCREEN_HEIGHT / 6);
    player.angle = 0.0f;
}

SceneTitle::~SceneTitle()
{
    menuItems.clear();
    delete font;
}

Scene* SceneTitle::Update(float dt)
{
    SDL_Event e;
    Scene* scene = this;

    up = down = left = right = false;
    bool fire = false;

    // Wait indefinitely for the next available event
    while (SDL_PollEvent(&e))
    {

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        /*
        else if (e.type == SDL_CONTROLLERDEVICEADDED)
        {

        }
        else if (e.type == SDL_CONTROLLERDEVICEREMOVED)
        {

        }
        */
        else if (e.type == SDL_CONTROLLERBUTTONDOWN)
        {
            switch (e.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_A:
            case SDL_CONTROLLER_BUTTON_B:
            case SDL_CONTROLLER_BUTTON_X:
            case SDL_CONTROLLER_BUTTON_Y:
            case SDL_CONTROLLER_BUTTON_START:
                fire = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                left = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                right = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                up = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                down = true;
                break;
            }
        }
        else if (e.type == SDL_CONTROLLERBUTTONUP)
        {
            switch (e.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_A:
            case SDL_CONTROLLER_BUTTON_B:
            case SDL_CONTROLLER_BUTTON_X:
            case SDL_CONTROLLER_BUTTON_Y:
            case SDL_CONTROLLER_BUTTON_START:
                fire = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                left = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                right = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                up = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                down = false;
                break;
            case SDL_CONTROLLER_BUTTON_BACK:
                running = false;
                break;
            }
        }
        else if (e.type == SDL_CONTROLLERAXISMOTION)
        {
            if (e.caxis.which == 0) // first gamepad
            {
                if (e.caxis.axis == 0) // X?
                {
                    left = false;
                    right = false;
                    if (e.caxis.value < -JOYSTICK_DEAD_ZONE)
                        left = true;
                    else if (e.caxis.value > JOYSTICK_DEAD_ZONE)
                        right = true;
                }
                else if (e.caxis.axis == 1) // Y?
                {
                    up = false;
                    down = false;
                    if (e.caxis.value < -JOYSTICK_DEAD_ZONE)
                        up = true;
                    else if (e.caxis.value > JOYSTICK_DEAD_ZONE)
                        down = true;
                }
            }
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
            case SDLK_RETURN:
            case SDLK_RETURN2:
            case SDLK_KP_ENTER:
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

    if (fire)
    {
        if (menuItems[menuIndex] == "PLAY")
        {
            scene = scenes[Scenes::SCENE_GAME];
            scene->Init();
        }
        else if (menuItems[menuIndex] == "EXIT")
        {
            running = false;
        }
    }

    if (up)
        menuIndex = MAX(0, menuIndex - 1);
        
    if (down)
        menuIndex = MIN(menuItems.size() - 1, menuIndex + 1);

    player.angle += (0.5 * M_PI * dt);
    if (player.angle > (2.0 * M_PI))
        player.angle -= (2.0 * M_PI);

    return scene;
}

void SceneTitle::Draw()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    font->Construct(5.0, 5.0);
    std::string message = "VECTOR STORM";
    int width, height;
    font->MeasureText(message, &width, &height);
    int x = (SCREEN_WIDTH - width) / 2;
    int y = (SCREEN_HEIGHT - height) / 2;

    // Draw it over a 4x4 area to make it bold
    for (int j = -1; j < 2; j++)
        for(int i = -1; i < 2; i++)
    font->DrawText(message, x + i, y + j, WHITE);

    y += height;

    font->Construct(3.0, 3.0);

    for(int i = 0; i < menuItems.size(); i++)
    {
        font->MeasureText(menuItems[i], &width, &height);
        
        x = (SCREEN_WIDTH - width) / 2;
        SDL_Rect r;
        if (i == menuIndex)
        {
            SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
            r.x = x - 16;
            r.y = y - height + 2;
            r.w = width + 32;
            r.h = height + 4;
            SDL_RenderFillRect(renderer, &r);
            font->DrawText(menuItems[i], x, y, BLACK);
        }
        else
        {
            font->DrawText(menuItems[i], x, y, WHITE);
        }
        y += (height + 8);
    }

    player.Draw();

    // Update screen
    SDL_RenderPresent(renderer);

}