#include <SDL2/SDL_version.h>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const SDL_version& v)
{
    out << static_cast<int>(v.major) << '.';
    out << static_cast<int>(v.minor) << '.';
    out << static_cast<int>(v.patch);
    return out;
}

int main()
{
    SDL_version compiled = { 0, 0, 0 };
    SDL_version linked = { 0, 0, 0 };

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    std::cout << "SDL compiled: " << compiled << std::endl;
    std::cout << "SDL linked: " << linked << std::endl;

    int exitCode = std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
    std::cout << "Program has exited with code: " << exitCode << std::endl;
    return exitCode;
}
