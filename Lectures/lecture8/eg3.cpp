#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream myInFile;
    myInFile.open("sample.txt", std::ios_base::in);

    if (!myInFile.is_open()) {
        std::cerr << "Could not open file for reading!\n";
        std::exit(1);
    }

    std::cout << "The file says:\n";
    std::string line;
    while (std::getline(myInFile, line)) {
        std::cout << line << "\n";
    }
    myInFile.close();
}