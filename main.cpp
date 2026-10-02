#include "include/menu/MyModuleMenu.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "\n============================================================\n";
    std::cout << "        DNA SEQUENCE ANALYZER - C++17 CORE MODULE\n";
    std::cout << "       Course: CSE 2105 (DSA) & CSE 2106 (DSA Lab)\n";
    std::cout << " Assigned Module: Tree | Map | STL | Linked List | Fenwick\n";
    std::cout << "============================================================\n";

    try
    {
        MyModuleMenu menu;
        if (argc > 1 && (std::string(argv[1]) == "--test" || std::string(argv[1]) == "-t"))
        {
            std::cout << "[INFO] Running in Automated Test Mode...\n";
            bool success = menu.runAllTests();
            return success ? 0 : 1;
        }

        menu.runMainMenu();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "\n[FATAL ERROR]: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
