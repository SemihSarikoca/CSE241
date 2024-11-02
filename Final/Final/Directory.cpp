
#include "Directory.hpp"
#include "SoftLink.hpp"
#include "RegularFile.hpp"

Directory::Directory(const std::string& _name, const std::shared_ptr<Directory>& _parent) : File("Directory"), name(_name), parent(_parent) {}

Directory::Directory(const Directory& other) : File("Directory"), name(other.name), parent(nullptr) {
    // Copy contents
    for (auto it = other.contents.begin(); it != other.contents.end(); ++it) {
        addContents((*it)->clone());
    }
}


size_t Directory::getTotalMemoryUsed() const {
    size_t totalMemory = name.size();
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        totalMemory += (*it)->getTotalMemoryUsed();
    }
    return totalMemory;
}


std::string Directory::getPath() const {
    if (parent == nullptr) {
        return "";
    } else {
        // If the directory is not the root, recursively get the path from the parent
        return parent->getPath() + "/" + name;
    }
}
void Directory::setParents(const std::shared_ptr<Directory>& newParent) {
    parent = newParent;
    for (auto it = contents.begin(); it != contents.end(); ++it)
        if (auto subDir = std::dynamic_pointer_cast<Directory>(*it))
            subDir->setParents(std::dynamic_pointer_cast<Directory>(shared_from_this()));
}


std::shared_ptr<File> Directory::clone() const {
    return std::make_shared<Directory>(*this);
}

void Directory::addContents(const std::shared_ptr<File>& file) {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == file->getName()) {
            std::cerr << "error: File with name: " << file->getName() << " already exists" << std::endl;
            return;
        }
    }
    contents.push_back(file);
}

void Directory::addDirectory(const std::string& dirName) {
    if (dirName == "root" || dirName == ".." || dirName == ".") {
        std::cerr << "mkdir: Can not create file with name: " << dirName << std::endl;
        return;
    }
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == dirName) {
            std::cerr << "mkdir: " << dirName << ": File exists" << std::endl;
            return;
        }
    }
    std::shared_ptr<Directory> newDir = std::make_shared<Directory>(dirName, std::dynamic_pointer_cast<Directory>(shared_from_this()));
    addContents(newDir);
}

void Directory::removeContents(const std::string& fileName) {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == fileName) {
            std::shared_ptr<File> fileToRemove = *it;

            // Check if the file is a directory and if it is empty
            if (auto subDir = std::dynamic_pointer_cast<Directory>(fileToRemove)) {
                if (!subDir->contents.empty()) {
                    std::cerr << "rm: cannot remove '" << fileName << "': Directory is not empty" << std::endl;
                    return;
                }
            } else if (auto regFile = std::dynamic_pointer_cast<RegularFile>(fileToRemove)) {
                regFile->setData({});
            } else if (auto slinFile = std::dynamic_pointer_cast<SoftLink>(fileToRemove)) {
                slinFile->setLinkedFile(nullptr);
            }

            contents.erase(it);
            return;  // Exit the function after removing the file
        }
    }
    std::cerr << "rm: cannot remove '" << fileName << "': Not found in directory" << std::endl;
}

void Directory::visualizeContents(bool recursive, size_t depth) const {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        for (size_t i = 0; i < depth; ++i) {
            std::cout << "  ";  // Adjust indentation based on depth
        }
        std::cout << (*it)->getType() << " " << (*it)->getName() << "   " << (*it)->getCreationTime() <<
            "   " << (*it)->getTotalMemoryUsed() << "Bytes" << std::endl;

        if (recursive) {
            // If it is a directory, recursively call ls
            if (auto subdir = std::dynamic_pointer_cast<const Directory>(*it)) {
                subdir->visualizeContents(true, depth + 1);
            }
        }
    }
}


void Directory::cat(const std::string& _name) const {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == _name) {
            if (std::dynamic_pointer_cast<Directory>(*it)) {
                std::cerr << "cat: " << _name << ": Is a directory" << std::endl;
                return;
            }
            (*it)->cat(_name);
            return;
        }
    }
    std::cerr << "cat: " << _name << ": No such file" << std::endl;
}


std::shared_ptr<Directory> Directory::changeDir(const std::string& dirName) {
    if (dirName == "..")
        return parent;
    else if (dirName == ".")
        return nullptr; // Do not make any change

    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == dirName) {
            if (auto subDir = std::dynamic_pointer_cast<Directory>(*it)) {
                return subDir;
            } else if (auto dirLink = std::dynamic_pointer_cast<SoftLink>(*it)) {
                // Look for directories
                auto linkedFile = dirLink->getLinkedFile();
                while (true) {
                    if (auto linkedDir = std::dynamic_pointer_cast<Directory>(linkedFile)) {
                        return linkedDir;
                    } else if (auto linkedLink = std::dynamic_pointer_cast<SoftLink>(linkedFile)) {
                        linkedFile = linkedLink->getLinkedFile();
                    } else {
                        // Handle other file types or return nullptr if it's not a directory link
                        std::cerr << "cd: " << dirName << ": No such directory" << std::endl;
                        return nullptr;
                    }
                }
            }
        }
    }

    std::cerr << "cd: " << dirName << ": No such directory" << std::endl;
    return nullptr;
}


void Directory::createLink(const std::shared_ptr<File>& sourceFile, const std::string& destinationFileName, const std::string& sourcePath) {
    // Check if there is a file with the destination name already exists
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == destinationFileName) {
            std::cerr << "link: cannot create link '" << destinationFileName << "': File already exists" << std::endl;
            return;
        }
    }
    if (std::dynamic_pointer_cast<RegularFile>(sourceFile)) {
        // If source file is a regular file, create a soft link
        if (auto newSoftLink = std::make_shared<SoftLink>(destinationFileName, std::dynamic_pointer_cast<RegularFile>(sourceFile), sourcePath))
            addContents(newSoftLink);
    } else if (std::dynamic_pointer_cast<Directory>(sourceFile)) {
        // If source file is a directory, create a symbolic link
        if (auto newSoftLink = std::make_shared<SoftLink>(destinationFileName, std::dynamic_pointer_cast<Directory>(sourceFile), sourcePath))
            addContents(newSoftLink);
    } else if (auto originalSoftLink = std::dynamic_pointer_cast<SoftLink>(sourceFile)) {
        // If source file is a soft link, create a symbolic link pointing to the same target
        if (auto newSoftLink = std::make_shared<SoftLink>(destinationFileName, originalSoftLink->getLinkedFile(), sourcePath))
            addContents(newSoftLink);
    } else {
            // Handle other cases or report an error
            std::cerr << "link: unsupported file type for linking" << std::endl;
    }
}

void Directory::copyFile(const std::string& sourceFileName, const std::string& destinationFileName) {
    // Read the contents of the source file
    std::ifstream sourceFile(sourceFileName, std::ios::binary);
    if (!sourceFile.is_open()) {
        std::cerr << "cp: cannot open '" << sourceFileName << "': No such file or directory" << std::endl;
        return;
    }

    auto newRegularFile = std::make_shared<RegularFile>(destinationFileName);
    char charByte;
    std::vector<char> copiedData;
    // Get the contents of the source file to the regularfile data
    while (sourceFile.get(charByte)) {
        copiedData.push_back(charByte);
    }
    newRegularFile->setData(copiedData);
    sourceFile.close();
    addContents(newRegularFile);
}

void Directory::copyFromMyOS(const std::shared_ptr<File>& sourceFile, const std::string& destinationFileName) {
    if (auto file = std::dynamic_pointer_cast<Directory>(sourceFile)) {
        auto newDir = std::make_shared<Directory>(*file); // Create a copy of the current directory
        newDir->name = destinationFileName;
        newDir->setParents(std::dynamic_pointer_cast<Directory>(shared_from_this()));
        addContents(newDir);
    } else if (auto file = std::dynamic_pointer_cast<RegularFile>(sourceFile)) {
        auto newFile = std::make_shared<RegularFile>(destinationFileName);
        newFile->setData(file->getData());
        addContents(newFile);
    } else if (auto file = std::dynamic_pointer_cast<SoftLink>(sourceFile)) {
        auto newLink = std::make_shared<SoftLink>(destinationFileName, file->getLinkedFile(), file->getLinkPath());
        addContents(newLink);
    }
}

std::shared_ptr<File> Directory::findFileByPath(const std::string& path) {
    std::vector<std::string> pathTokens = splitPath(path);
    return findFileRecursively(pathTokens, 0);
}

std::shared_ptr<File> Directory::findFileRecursively(const std::vector<std::string>& pathTokens, size_t index) {
    if (index >= pathTokens.size()) {
        return nullptr; // End of path reached
    }

    const std::string& targetName = pathTokens[index];
    
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if ((*it)->getName() == targetName) {
            if (index == pathTokens.size() - 1) {
                return (*it); // Found the target file at the end of the path
            } else if (auto subdir = std::dynamic_pointer_cast<Directory>(*it)) {
                return subdir->findFileRecursively(pathTokens, index + 1);
            }
        }
    }
    
    return nullptr; // Target file not found
}

std::vector<std::string> Directory::splitPath(const std::string& path) {
    std::vector<std::string> result;
    std::istringstream iss(path);
    std::string token;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }

    return result;
}

void Directory::serialize(std::ofstream& ofs) const {
    ofs << fileType << "\n";
    ofs << name << "\n";
    ofs << creationTime << "\n";
    ofs << contents.size();
    
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        ofs << "\n";
        (*it)->serialize(ofs);
        
    }
}

void Directory::deserialize(std::ifstream& ifs) {
    std::string type;
    size_t itemCount;
    ifs >> type >> name >> creationTime >> itemCount;
    if (type != fileType)
        throw std::runtime_error("Terminating due to the: Unexpected type at Directory deserialization");

    for (size_t i = 0; i < itemCount; ++i) {
        std::streampos startPos = ifs.tellg(); // Okuma konumunu kaydet
        ifs >> type;
        ifs.seekg(startPos);

        std::shared_ptr<File> file;

        if (type == "Directory") {
            file = std::make_shared<Directory>("", std::dynamic_pointer_cast<Directory>(shared_from_this()));
        } else if (type == "RegularFile") {
            file = std::make_shared<RegularFile>("");
        } else if (type == "SoftLink") {
            file = std::make_shared<SoftLink>("", nullptr, "");
        } else
            throw std::runtime_error("Terminating due to the: Unknown file type during deserialization.");

        file->deserialize(ifs);
        addContents(file);
    }
}
