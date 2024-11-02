
#include "Shell.hpp"
#define TOTAL_MEMORY (10 * 1024 * 1024)


Shell::Shell() : root(std::make_shared<Directory>("root")), currentDir(root) {}


void Shell::printPromt() const {
    std::cout << currentDir->getName() << "> ";
}

std::vector<std::string> Shell::tokenizeInput(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;

    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void Shell::run() {
    std::string userInput;

    while (true) {
        if (TOTAL_MEMORY < root->getTotalMemoryUsed()) {
            throw std::runtime_error("Total memory used exceeds the memory capacity.\nTerminating shell...");
        }
        // Get user input as a line
        printPromt();
        std::getline(std::cin, userInput);

        // Tokenize the input
        std::vector<std::string> tokens = tokenizeInput(userInput);
        processCommand(tokens);
        if (tokens[0] == "exit")
            break;
    }
}

void Shell::processCommand(const std::vector<std::string>& tokens) {
    std::string command = tokens[0];

    if (command == "ls") {
        if (tokens.size() == 1)
            currentDir->visualizeContents(false);
        else if (tokens.size() == 2 && tokens[1] == "-R")
            currentDir->visualizeContents(true);
    } else if (command == "cd") {
        if (tokens.size() == 1)
            currentDir = root;
        else if (tokens.size() == 2) {
            std::shared_ptr<Directory> newDir = std::dynamic_pointer_cast<Directory>(currentDir->changeDir(tokens[1]));
            if (newDir) currentDir = newDir;
        }
    } else if (command == "cat" && tokens.size() == 2) {
        currentDir->cat(tokens[1]);
    } else if (command == "mkdir" && tokens.size() == 2) {
        currentDir->addDirectory(tokens[1]);
    } else if (command == "rm" && tokens.size() == 2) {
        currentDir->removeContents(tokens[1]);
    } else if (command == "cp" && tokens.size() == 3) {
        // Find the source file in the current directory
        std::shared_ptr<File> sourceFile = nullptr;

        // Check if the user entered a full path
        if (tokens[1].front() == '~') {
            // Full path provided, start searching from the root
            currentDir->copyFile(tokens[1].substr(1), tokens[2]);
            return;
        } else if (tokens[1].front() == '/') {
            sourceFile = root->findFileByPath(tokens[1]);
        } else {
            // No path provided, search only in the current directory
            for (const auto& file : currentDir->getContents()) {
                if (file->getName() == tokens[1]) {
                    sourceFile = file;
                    break;
                }
            }
        }

        if (sourceFile) {
            currentDir->copyFromMyOS(sourceFile, tokens[2]);
        } else {
            std::cerr << "Error: Source file or directory not found." << std::endl;
        }

    } else if (command == "link" && tokens.size() == 3) {
        // Find the source file in the current directory
        std::shared_ptr<File> sourceFile = nullptr;
        std::string sourcePath;
        // Check if the user entered a full path
        if (tokens[1].front() == '/') {
            // Full path provided, start searching from the root
            sourceFile = root->findFileByPath(tokens[1]);
            sourcePath = tokens[1];
        } else {
            // No path provided, search only in the current directory
            for (const auto& file : currentDir->getContents()) {
                if (file->getName() == tokens[1]) {
                    sourceFile = file;
                    break;
                }
            }
            sourcePath = currentDir->getPath() + "/" + tokens[1];
        }
        // If the source file is found, create a soft link
        if (sourceFile) {
            currentDir->createLink(sourceFile, tokens[2], sourcePath);
        } else {
            std::cout << "link: cannot create link '" << tokens[2] << "': Source file not found" << std::endl;
        }
    } else if (command == "exit" && tokens.size() == 1) {
        return;
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

void Shell::saveToFile(const std::string& filename) {
    std::ofstream diskFile(filename, std::ios::binary | std::ios::out);
    if (diskFile) {
        root->serialize(diskFile);
        diskFile.close();
    } else {
        std::cerr << "Error: Unable to write file '" << filename << "' to disk." << std::endl;
    }
}

void Shell::loadFromFile(const std::string& filename) {
    std::ifstream diskFile(filename, std::ios::binary | std::ios::in);
    if (diskFile) {
        if (diskFile.peek() == std::ifstream::traits_type::eof())
            return;
        root->deserialize(diskFile);
        diskFile.close();
    } else {
        std::cerr << "Error: Unable to read file '" << filename << "' from disk." << std::endl;
    }
}

void Shell::linkFiles(std::shared_ptr<File> file) {
    if (auto dir = std::dynamic_pointer_cast<Directory>(file)) {
        for (const auto& content : dir->getContents()) {
            linkFiles(content);
        }
    } else if (auto link = std::dynamic_pointer_cast<SoftLink>(file)) {
        std::shared_ptr<File> linkFileObj = root->findFileByPath(link->getLinkPath());

        if (linkFileObj != nullptr) {
            link->setLinkedFile(linkFileObj);
        } else {
            link->setLinkedFile(nullptr);
        }
    }
}

void Shell::updateLinks() {
    linkFiles(root);
}
