#include <fstream>

int main(void){
    std::ofstream testFile("test.log");
    testFile << "Hello, Ofstream!\n";
    testFile << 4 << std::endl;
    testFile << 3 << 5 << "\n";

    testFile.close();

    return 0;
}