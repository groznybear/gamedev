#include <iostream>
int main()
{
    std::cout << "Empty" << std::endl;
    int exitCode = std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
    std::cout << "Program has exited with code: " << exitCode << std::endl;
    return exitCode;
}
