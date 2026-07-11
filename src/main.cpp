#include"app.hpp"

#include <iostream>
#include<stdexcept>

int main()
{
    App app{};
    try {
        app.run();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}