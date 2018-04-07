/*
 * main.hpp
 *
 *  Created on: 7 апр. 2018 г.
 *      Author: groznybear
 */

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include <SDL2/SDL.h>

std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
    out << static_cast<int>(v.major) << '.';
    out << static_cast<int>(v.minor) << '.';
    out << static_cast<int>(v.patch);
    return out;
}

struct bind {
    SDL_Keycode key;
    std::string_view name;
};

void check_input(const SDL_Event& e)
{
    using namespace std;

    array<::bind, 8> keys{ { { SDLK_w, "up" },
        { SDLK_a, "left" },
        { SDLK_s, "down" },
        { SDLK_d, "right" },
        { SDLK_LCTRL, "button_one" },
        { SDLK_SPACE, "button_two" },
        { SDLK_ESCAPE, "select" },
        { SDLK_RETURN, "start" } } };

    const auto it = find_if(begin(keys), end(keys), [&](const ::bind& b) {
        return b.key == e.key.keysym.sym;
    });

    if (it != end(keys)) {
        cout << it->name << ' ';
        if (e.type == SDL_KEYDOWN) {
            cout << "is pressed\n";
        } else {
            cout << "is released\n";
        }
    }
}

int main(int argc, char* /*argv*/ [])
{
    using namespace std;
    SDL_version compiled = { 0, 0, 0 };
    SDL_version linked = { 0, 0, 0 };

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    cout << "SDL compiled version: " << compiled << endl;
    cout << "SDL linked version: " << linked << endl;

    if (SDL_COMPILEDVERSION != SDL_VERSIONNUM(linked.major, linked.minor, linked.patch)) {
        cerr << "[Warning: SDL2 compiled and linked version mismatch: "
             << compiled << " " << linked << "]" << endl;
    }

    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0) {
        const char* err_message = SDL_GetError();
        cerr << "error: failed call SDL_Init: " << err_message << endl;
        return EXIT_FAILURE;
    }

    SDL_Window* const window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 640, 480, ::SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        const char* err_message = SDL_GetError();
        cerr << "error: failed call SDL_CreateWindow: " << err_message << endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bool continue_loop = true;
    while (continue_loop) {
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
            case SDL_KEYDOWN:
                check_input(sdl_event);
                break;
            case SDL_KEYUP:
                check_input(sdl_event);
                break;
            case SDL_QUIT:
                continue_loop = false;
                break;
            default:
                break;
            }
        }
        if (argc > 1) {
            continue_loop = false;
            cout << "CI/CD build. Escape the loop." << endl;
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
