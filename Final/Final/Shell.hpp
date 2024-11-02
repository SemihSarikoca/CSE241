
#ifndef Shell_hpp
#define Shell_hpp

#include "File.hpp"
#include "Directory.hpp"
#include "RegularFile.hpp"
#include "SoftLink.hpp"

class Shell {
public:
    Shell();
    void printPromt() const;
    std::vector<std::string> tokenizeInput(const std::string& input);
    void run();
    void processCommand(const std::vector<std::string>& tokens);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    void linkFiles(std::shared_ptr<File> file);
    void updateLinks();

private:
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> currentDir;
};

#endif /* Shell_hpp */
