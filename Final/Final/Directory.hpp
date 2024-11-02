
#ifndef Directory_hpp
#define Directory_hpp

#include "File.hpp"

class Directory : public File {
public:
    Directory(const std::string& _name, const std::shared_ptr<Directory>& _parent = nullptr);
    Directory(const Directory& other);
    
    size_t getTotalMemoryUsed() const override;
    const std::string& getName() const override { return name; }
    void setParents(const std::shared_ptr<Directory>& newParent);
    
    void cat(const std::string& _name) const override;
    std::string getPath() const;
    std::shared_ptr<File> clone() const override;
    std::shared_ptr<Directory> changeDir(const std::string& dirName);
    
    const std::vector<std::shared_ptr<File> >& getContents() const { return contents; }
    void addContents(const std::shared_ptr<File>& file);
    void removeContents(const std::string& fileName);
    void visualizeContents(bool recursive = false, size_t depth = 0) const;
    
    void addDirectory(const std::string& dirName);
    void createLink(const std::shared_ptr<File>& sourceFile, const std::string& destinationFileName, const std::string& sourcePath);
    void copyFile(const std::string& sourceFileName, const std::string& destinationFileName);
    void copyFromMyOS(const std::shared_ptr<File>& sourceFile, const std::string& destinationFileName);

    std::shared_ptr<File> findFileByPath(const std::string& path);
    std::vector<std::string> splitPath(const std::string& path);
    std::shared_ptr<File> findFileRecursively(const std::vector<std::string>& pathTokens, size_t index);

    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;

private:
    std::string name;
    std::vector<std::shared_ptr<File> > contents;
    std::shared_ptr<Directory> parent;
};

#endif /* Directory_hpp */
