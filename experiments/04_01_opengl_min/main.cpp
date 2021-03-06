//============================================================================
// Name        : microengine_lib.cpp
// Author      : Daniil Cherepkov
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string_view>

#include "engine.hpp"

int main(int argc, char* argv[])
{
    using namespace std;

    unique_ptr<me::engine, void (*)(me::engine*)> engine(me::create_engine(), me::destroy_engine);

    string initMsg = engine->initialize(argc > 1 ? argv[1] : "");

    int exitcode = initMsg.empty() ? EXIT_SUCCESS : EXIT_FAILURE;

    if (!initMsg.empty()) {
        cout << "Engine initialization failed, reason: " << initMsg << endl;
        return exitcode;
    }

    bool ingame = true;
    while (ingame) {
        if (argc > 1) {
            cout << "Force escape from main loop." << endl;
            exitcode = cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
            ingame = false;
            break;
        }

        me::event event;
        while (engine->poll_event(event)) {
            cout << "Handling event: " << event << endl;
            switch (event) {
            case me::event::turn_off:
                ingame = false;
                break;
            default:
                break;
            }
        }

        engine->render();
        engine->swap();
    }

    engine->uninitialize();
    cout << "Exit code: " << exitcode << endl;
    return exitcode;
}
