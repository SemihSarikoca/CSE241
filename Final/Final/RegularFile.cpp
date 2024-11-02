
#include "RegularFile.hpp"


RegularFile::RegularFile(const std::string& _name) : File("RegularFile"), name(_name), data({}) {}

void RegularFile::cat(const std::string& _name) const {
    std::cout.write(data.data(), data.size());
    std::cout << std::endl;
}


size_t RegularFile::getTotalMemoryUsed() const {
    size_t dataSize = data.size();
    size_t metadataSize = name.size();
    return dataSize + metadataSize;
}

std::shared_ptr<File> RegularFile::clone() const {
    return std::make_shared<RegularFile>(*this);
}

void RegularFile::serialize(std::ofstream& ofs) const {
    ofs << fileType << "\n" << name << "\n" << creationTime << "\n" << data.size();

    ofs.write(data.data(), data.size());
}

void RegularFile::deserialize(std::ifstream& ifs) {
    std::string type;
    ifs >> type >> name >> creationTime;
    if (type != fileType)
        throw std::runtime_error("Terminating due to the: Unexpected type at RegularFile deserialization");

    size_t dataSize;
    ifs >> dataSize;

    data.resize(dataSize);
    ifs.read(data.data(), dataSize);
}
