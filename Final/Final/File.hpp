
#ifndef File_hpp
#define File_hpp

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <memory>

class File : public std::enable_shared_from_this<File> {
public:
    File(const std::string& _type = "NULL") : creationTime(std::time(0)), fileType(_type) {}
    virtual void cat(const std::string& _name) const = 0;
    virtual const std::string& getName() const = 0;
    
    virtual std::shared_ptr<File> clone() const = 0;
    virtual void serialize(std::ofstream& ofs) const = 0;
    virtual void deserialize(std::ifstream& ifs) = 0;
    
    virtual const time_t& getTime() const {return creationTime;}
    virtual const std::string& getType() const {return fileType;}
    virtual size_t getTotalMemoryUsed() const = 0;
    virtual const std::string getCreationTime() const {
        std::tm* localTime = std::localtime(&creationTime);
        std::ostringstream oss;
        oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");   // Format the time in a human-readable way
        return oss.str();
    }
protected:
    time_t creationTime;
    std::string fileType;
};

#endif /* File_hpp */
