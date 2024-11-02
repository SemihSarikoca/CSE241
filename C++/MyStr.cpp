#include <iostream>
#include <cstring>
using namespace std;

class MyStr {
    public:
        MyStr() : str(nullptr), size(0) {}
        MyStr(const char * text);
        MyStr(const MyStr& obj);
        ~MyStr();
        MyStr& operator=(const MyStr& obj);
        MyStr operator+(const MyStr& obj) const;
        MyStr& operator+=(const MyStr& obj);
        int length() const {return size;}
        const char* getStr() const {return str;}
    private:
        char* str;
        int size;    
};

int main() {
    // Create MyStr objects
    MyStr str1("Hello, ");
    MyStr str2("World!");

    // Use the copy constructor
    MyStr str3 = str1;

    // Use the assignment operator
    MyStr str4;
    str4 = str2;

    // Use the concatenation operator
    MyStr str5 = str1 + str2;

    // Use the += operator
    for(int i = 0; i<str2.length(); ++i) {
        str1 += str2;
    }


    // Display the results
    std::cout << "str1: " << str1.getStr() << std::endl;
    std::cout << "str2: " << str2.getStr() << std::endl;
    std::cout << "str3: " << str3.getStr() << std::endl;
    std::cout << "str4: " << str4.getStr() << std::endl;
    std::cout << "str5: " << str5.getStr() << std::endl;

    return 0;
}

MyStr::MyStr(const char* text) : str(nullptr), size(strlen(text)) {
    str = new char[size + 1];
    strcpy(str, text);
}

MyStr::MyStr(const MyStr& obj) : str(nullptr), size(obj.length()) {
    str = new char[size + 1];
    strcpy(str, obj.str);
}

MyStr::~MyStr() {
    delete[] str;
}

MyStr& MyStr::operator=(const MyStr& obj) {
    if (this == &obj) return *this;
    if (size != 0) delete[] str;
    
    size = obj.length();
    
    str = new char[size+1];
    strcpy(str,obj.str);
    return *this;
}

MyStr& MyStr::operator+=(const MyStr& obj) {
    *this = *this + obj;
    return *this;
}

MyStr MyStr::operator+(const MyStr& obj) const {
    MyStr temp;
    if (obj.size == 0) {
        return *this;
    }
    else if (size == 0) {
        temp = obj;
        return temp;
    }
    else {
        temp.size = size + obj.size;
        temp.str = new char[temp.size + 1];
        strcpy(temp.str, str);
        strcat(temp.str, obj.str);
        return temp;
    }
}
