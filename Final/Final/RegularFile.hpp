
#ifndef RegularFile_hpp
#define RegularFile_hpp


#include "File.hpp"

class RegularFile : public File {
public:
    RegularFile(const std::string& name);
    
    size_t getTotalMemoryUsed() const override;
    void cat(const std::string& _name) const override;
    std::shared_ptr<File> clone() const override;
    
    const std::string& getName() const override { return name; }
    const std::vector<char>& getData() const { return data; }
    void setData(const std::vector<char>& newData) { data = newData; }

    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;
    
private:
    std::string name;
    std::vector<char> data;
};

#endif /* RegularFile_hpp */
