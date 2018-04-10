#include "engine.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace me {

static std::array<std::string_view, 17> event_names = {
    { /// input events
        "left_pressed", "left_released", "right_pressed", "right_released",
        "up_pressed", "up_released", "down_pressed", "down_released",
        "select_pressed", "select_released", "start_pressed", "start_released",
        "button1_pressed", "button1_released", "button2_pressed",
        "button2_released",
        /// virtual console events
        "turn_off" }
};

struct GLVersion {
    int gl_major;
    int gl_minor;
};

std::ostream& operator<<(std::ostream& stream, const event e)
{
    std::uint32_t value = static_cast<std::uint32_t>(e);
    std::uint32_t minimal = static_cast<std::uint32_t>(event::left_pressed);
    std::uint32_t maximal = static_cast<std::uint32_t>(event::turn_off);
    if (value >= minimal && value <= maximal) {
        stream << event_names[value];
        return stream;
    } else {
        throw std::runtime_error("too big event value");
    }
}
std::ostream& operator<<(std::ostream& stream, const GLVersion v)
{
    stream << v.gl_major;
    stream << ".";
    stream << v.gl_minor;
    return stream;
}
static std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
    out << static_cast<int>(v.major) << '.';
    out << static_cast<int>(v.minor) << '.';
    out << static_cast<int>(v.patch);
    return out;
}

struct bind {
    SDL_Keycode key;
    std::string_view name;
    event event_pressed;
    event event_released;
};

const std::array<bind, 8> keys{
    { { SDLK_w, "up", event::up_pressed, event::up_released },
        { SDLK_a, "left", event::left_pressed, event::left_released },
        { SDLK_s, "down", event::down_pressed, event::down_released },
        { SDLK_d, "right", event::right_pressed, event::right_released },
        { SDLK_RSHIFT, "button1", event::button1_pressed,
            event::button1_released },
        { SDLK_SPACE, "button2", event::button2_pressed,
            event::button2_released },
        { SDLK_ESCAPE, "select", event::select_pressed, event::select_released },
        { SDLK_RETURN, "start", event::start_pressed, event::start_released } }
};

static bool check_input(const SDL_Event& e, const bind*& result)
{
    using namespace std;

    const auto it = find_if(begin(keys), end(keys), [&](const bind& b) {
        return b.key == e.key.keysym.sym;
    });

    if (it != end(keys)) {
        result = &(*it);
        return true;
    }
    return false;
}

class engine_impl final : public engine {
public:
    /// create main window
    /// on success return empty string
    std::string initialize(std::string_view config) final
    {
        using namespace std;

        stringstream serr;

        SDL_version compiled = { 0, 0, 0 };
        SDL_version linked = { 0, 0, 0 };

        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);

        if (SDL_COMPILEDVERSION != SDL_VERSIONNUM(linked.major, linked.minor, linked.patch)) {
            serr << "warning: SDL2 compiled and linked version mismatch: "
                 << compiled << " " << linked << endl;
        }

        const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
        if (init_result != 0) {
            const char* err_message = SDL_GetError();
            serr << "error: failed call SDL_Init: " << err_message << endl;
            return serr.str();
        }

        if (!config.empty()) {
            std::cout << "Configuration string was provided to indicate CI launch. Escape..." << endl;
            return "";
        }

        window = SDL_CreateWindow(
            "Microengine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 480,
            ::SDL_WINDOW_RESIZABLE | ::SDL_WINDOW_OPENGL);

        if (window == nullptr) {
            const char* err_message = SDL_GetError();
            serr << "error: failed call SDL_CreateWindow: " << err_message
                 << endl;
            SDL_Quit();
            return serr.str();
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_GLContext context = SDL_GL_CreateContext(window);
        if (context == NULL) {
        	std::string err = "Error: OpenGL not created";
            cerr << err << endl;
            return err;
        }
        GLVersion version;
        int result = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &version.gl_major);
        assert(result == 0);

        result = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &version.gl_minor);
        assert(result == 0);

        if (version.gl_major <= 2 && version.gl_minor < 1) {
            cerr << "OpenGL version is too low: " << version << endl;
            return "OpenGL version is too low";
        }

        cout << "OpenGL version: " << version << endl;

        return "";
    }
    /// main render function
    void render() final
    {
        glClearColor(0.637f, 0.3f, 0.4f, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    /// swapping buffers
    void swap() final
    {
        SDL_GL_SwapWindow(window);
    }
    /// pool event from input queue
    bool poll_event(event& e) final
    {
        using namespace std;
        // collect all events from SDL
        SDL_Event sdl_event;
        if (SDL_PollEvent(&sdl_event)) {
            const bind* binding = nullptr;

            if (sdl_event.type == SDL_QUIT) {
                e = event::turn_off;
                return true;
            } else if (sdl_event.type == SDL_KEYDOWN) {
                if (check_input(sdl_event, binding)) {
                    e = binding->event_pressed;
                    return true;
                }
            } else if (sdl_event.type == SDL_KEYUP) {
                if (check_input(sdl_event, binding)) {
                    e = binding->event_released;
                    return true;
                }
            }
        }
        return false;
    }
    void uninitialize() final {}

private:
    SDL_Window* window = nullptr;
};

static bool already_exist = false;

engine* create_engine()
{
    if (already_exist) {
        throw std::runtime_error("engine already exist");
    }
    engine* result = new engine_impl();
    already_exist = true;
    return result;
}

void destroy_engine(engine* e)
{
    if (already_exist == false) {
        throw std::runtime_error("engine not created");
    }
    if (nullptr == e) {
        throw std::runtime_error("e is nullptr");
    }
    delete e;
}

engine::~engine() {}
}
