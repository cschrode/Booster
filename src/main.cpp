#include "includes/define.h"

int main()
{
    std::cout << "Boost " << STANDARD_BOOST_VERSION << " [Easy Build and Install]";
    std::cout << std::endl << std::endl;

    InstallBoost();

    std::cout << std::endl << std::endl;
    std::cout << "Boost " << STANDARD_BOOST_VERSION << " has been installed!";
    std::cout << std::endl << std::endl;

    return 0;
}
