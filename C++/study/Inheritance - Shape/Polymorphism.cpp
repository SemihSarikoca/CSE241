#include <iostream>
#include <vector>
using namespace std;


class Base {
public:
    Base() = default;
    Base(int Num) : num(Num) { cout << "Base" << endl; }
    virtual void print() {
        cout << num << endl;
    }
private:
    int num;
};

class Derived1 : public Base {
public:
    Derived1() = default;
    Derived1(int Num, int Num1) :num1(Num1), Base(Num) { cout << "Derived1" << endl; }
    virtual void print() {
        cout << "derived1 ";
        Base::print();
        cout << num1 << endl;
    }
private:
    int num1;

};

class Derived2 : public Base {
public:
    Derived2() = default;
    Derived2(int Num, int Num2) :num2(Num2), Base(Num) { cout << "Derived2" << endl; }
    virtual void print() {
        cout << "derived2 ";
        Base::print();
        cout << num2 << endl;
    }
private:
    int num2;
};



int main() {
    Derived1 d1(3,5);
    Derived2 d2(1,2);

    Base* bp = &d1;
    Base* bp2 = &d2;
    
    Derived2* dp2 = dynamic_cast<Derived2*>(bp);
    dp2->print();
    Derived1* dp = dynamic_cast<Derived1*>(bp);
    if (dp) {
        dp->print();
    }
    else {
        cout << "nullptr" << endl;
    }
    

    return 0;
}
