#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ofstream myFile;
    myFile.open("sample.txt", std::ios_base::out);

    if (!myFile.is_open()) {
        std::cerr << "Could not open file for writing!\n";
        std::exit(1);
    }

    myFile << "Here is some sample text.\n";
    myFile.close();
    return 0;
}