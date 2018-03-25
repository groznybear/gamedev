/*
 * main.cpp
 *
 *  Created on: 25 мар. 2018 г.
 *      Author: groznybear
 */

#include <iostream>
#include <lib.hpp>

int main(int argc, char* argv[])
{
    // default world to use to greeting the user, if name wasn't specified
    std::string username = "stranger";

    if (argc > 1) {
        // for now, assume that user provides his/her name
        // as the first run argument
        username = argv[1];
    }

    return greetings(username) ? EXIT_SUCCESS : EXIT_FAILURE;
}
