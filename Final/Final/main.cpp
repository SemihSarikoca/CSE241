
#include "Shell.hpp"

#define FileName "/Users/semihsarikoca/Desktop/disk.txt"

int main() {
    Shell myshell;
    try {
        myshell.loadFromFile(FileName);
        myshell.updateLinks();
        myshell.run();
        myshell.saveToFile(FileName);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Catched undefined exception." << std::endl;
        return -2;
    }
}
