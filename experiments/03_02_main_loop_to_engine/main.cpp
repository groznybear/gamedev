//============================================================================
// Name        : microengine.cpp
// Author      : Daniil Cherepkov
// Version     : 1.0
//============================================================================

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string_view>

#include "engine.hpp"

int main(int argc)
{
    std::unique_ptr<me::engine, void (*)(me::engine*)> engine(
        me::create_engine(), me::destroy_engine);

    std::string err = engine->initialize("");
    if (!err.empty()) {
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }

    bool continue_loop = true;
    while (continue_loop) {
        me::event event;

        while (engine->read_input(event)) {
            std::cout << event << std::endl;
            switch (event) {
            case me::event::turn_off:
                continue_loop = false;
                break;
            default:
                break;
            }
            if (argc > 1) {
                std::cout << "CI/CD build. Force escape from main loop." << std::endl;
                continue_loop = false;
            }
        }
    }

    engine->uninitialize();

    return EXIT_SUCCESS;
}
