/*
 * main.cpp
 *
 *  Created on: 25 мар. 2018 г.
 *      Author: groznybear
 */
#include "mainconfig.hpp"

#ifdef HELLOLIB
#include "lib.hpp"
#endif
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "VERSION: " << use_lib_VERSION_MAJOR << "." << use_lib_VERSION_MINOR << std::endl;
    // default world to use to greeting the user, if name wasn't specified
    std::string username = "stranger";

    if (argc > 1) {
        // for now, assume that user provides his/her name
        // as the first run argument
        username = argv[1];
    }

#ifdef HELLOLIB

    std::cout << "Lib was compiled, using Lib" << std::endl;
    int exitCode = greetings(username) ? EXIT_SUCCESS : EXIT_FAILURE;
#else
    std::cout << "Lib was not compiled, using default" << std::endl;
    std::cout << "Hello, " << username << std::endl;
    int exitCode = std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
#endif

    std::cout << "Program exit with code: " << exitCode << std::endl;
    return exitCode;
}
