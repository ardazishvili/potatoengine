#pragma once

#include "key_code.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include "renderer/vertex.hpp"
#include "vector3d.hpp"

pt::key_code get_key(const SDL_Keycode& sdl_keycode)
{
    using namespace pt;

    switch (sdl_keycode)
    {
        case SDLK_UP:
        {
            return key_code::up;
        }

        case SDLK_RIGHT:
        {
            return key_code::right;
        }

        case SDLK_DOWN:
        {
            return key_code::down;
        }

        case SDLK_LEFT:
        {
            return key_code::left;
        }

        case SDLK_q:
        {
            return key_code::button_a;
        }

        case SDLK_w:
        {
            return key_code::button_b;
        }

        case SDLK_a:
        {
            return key_code::start;
        }

        case SDLK_s:
        {
            return key_code::select;
        }

        default:
        {
            return key_code::unsupported;
        }
    }
}


pt::vertex world_to_screen(const vector3d& position)
{
    return {position.x, position.y, position.z};
}
