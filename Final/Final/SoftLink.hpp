
#ifndef SoftLink_hpp
#define SoftLink_hpp

#include "File.hpp"

class SoftLink : public File {
public:
    SoftLink(const std::string& _name, const std::shared_ptr<File>& _linkedFile, const std::string& _linkPath);
    SoftLink(const SoftLink& other);
    
    
    const std::string& getName() const override { return name; }
    const std::string& getLinkPath() const { return linkPath; }
    
    
    std::shared_ptr<File> getLinkedFile() { return linkedFile; }
    void setLinkedFile(const std::shared_ptr<File>& newLink);
    
    size_t getTotalMemoryUsed() const override;
    void cat(const std::string& _name) const override;
    std::shared_ptr<File> clone() const override;
    
    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;

private:
    std::string name;
    std::shared_ptr<File> linkedFile;
    std::string linkPath;
};

#endif /* SoftLink_hpp */
