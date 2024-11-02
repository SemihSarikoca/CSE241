
#include "SoftLink.hpp"
#include "RegularFile.hpp"
#include "Directory.hpp"

SoftLink::SoftLink(const std::string& _name, const std::shared_ptr<File>& _linkedFile, const std::string& _linkPath)
    : File("SoftLink"), name(_name), linkedFile(_linkedFile), linkPath(_linkPath) {}

SoftLink::SoftLink(const SoftLink& other)
    : File("SoftLink"), name(other.name), linkedFile(other.linkedFile), linkPath(other.linkPath) {}

void SoftLink::cat(const std::string& _name) const {
    if (auto link = std::dynamic_pointer_cast<RegularFile>(linkedFile)) {
        if (link && !link->getData().empty()) {
            link->cat(_name);
        } else {
            std::cerr << "Soft link is broken. Target not found." << std::endl;
        }
    } else if (auto link = std::dynamic_pointer_cast<Directory>(linkedFile)) {
        std::cerr << "Command: cat: Not compatible with this type of link." << std::endl;
    } else if (auto link = std::dynamic_pointer_cast<SoftLink>(linkedFile)) {
        if (link) {
            link->cat(_name);
        } else {
            std::cerr << "Soft link is broken. Target not found." << std::endl;
        }
    } else {
        std::cerr << "Soft link is broken. Target not found." << std::endl;
    }
}

size_t SoftLink::getTotalMemoryUsed() const {
    return name.size(); // Only consider the soft link name size
}

std::shared_ptr<File> SoftLink::clone() const {
    return std::make_shared<SoftLink>(*this);
}

void SoftLink::setLinkedFile(const std::shared_ptr<File>& newLink) {
    linkedFile = newLink;
}

void SoftLink::serialize(std::ofstream& ofs) const {
    ofs << getType() << "\n" << getName() << "\n" << creationTime;
    if (linkedFile) {
        ofs << "\n" << linkedFile->getType() << "\n" << linkPath;
    } else {
        ofs << "\nCORRUPT\nNULL";  // Placeholder for invalid link
    }
}

void SoftLink::deserialize(std::ifstream& ifs) {
    std::string type;
    ifs >> type >> name >> creationTime;
    if (type != "SoftLink")
        throw std::runtime_error("Terminating due to the: Unexpected type at SoftLink deserialization");

    std::string linkType;
    ifs >> linkType >> linkPath;

    if (linkType == "RegularFile") {
        linkedFile = std::make_shared<RegularFile>("");
    } else if (linkType == "Directory") {
        linkedFile = std::make_shared<Directory>("", nullptr);
    } else if (linkType == "SoftLink") {
        linkedFile = std::make_shared<SoftLink>("", nullptr, "");
    } else if (linkType == "CORRUPT") {
        linkedFile = nullptr;
    } else
        throw std::runtime_error("Terminating due to the: Unknown file type during deserialization");
}
