#include <iostream>
#ifdef _WIN32

    #include <windows.h>
    void color2(std::string color, std::string line, bool newLine = false) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int col = 7;

        if (color == "blue") col = 1;
        else if (color == "green") col = 2;
        else if (color == "cyan") col = 3;
        else if (color == "red") col = 4;
        else if (color == "magenta") col = 5;
        else if (color == "yellow") col = 6;

        SetConsoleTextAttribute(hConsole, col);
        std::cout << line;
        if (newLine) {
            std::cout << std::endl;
        }
        SetConsoleTextAttribute(hConsole, 7);
    }


#else

    void color2(std::string colour, std::string line, bool newLine = false) {
        std::string col = "\033[0m";

        if (colour == "blue") col = "\033[0;34m";
        else if (colour == "green") col = "\033[0;32m";
        else if (colour == "cyan") col = "\033[0;36m";
        else if (colour == "red") col = "\033[0;31m";
        else if (colour == "magenta") col = "\033[0;35m";
        else if (colour == "yellow") col = "\033[0;33m";

        std::cout << col << line << "\033[0m";
        if (newLine) {
            std::cout << std::endl;
        }
    }


#endif
