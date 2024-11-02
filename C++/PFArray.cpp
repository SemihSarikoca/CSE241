#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;

class PFArrayD {
public:
    explicit PFArrayD(int capacityValue = 50);
    PFArrayD(const PFArrayD& pfaObject);
    void addElement(double element);
    void output();
    bool full() const { return (capacity == used); }
    int getCapacity() const { return capacity; }
    int getNumberUsed() const { return used; }
    void emptyArray() { used = 0; }
    double& operator[](int index);
    const double& operator[](int index) const;
    PFArrayD operator ()(int ind, int size);
    PFArrayD& operator =(const PFArrayD& rightSide);
    PFArrayD& operator +=(const PFArrayD& rightSide);
    friend ostream& operator <<(ostream& out, const PFArrayD& obj);
    friend istream& operator >>(istream& in, PFArrayD& obj);
    ~PFArrayD();

private:
    double* a;
    int capacity;
    int used;
    static const int DEFSIZE = 10;
};

ostream& operator <<(ostream& out, const PFArrayD& obj){
    for(int i=0; i<obj.used; ++i){
        out<<obj[i]<<" ";
    }
    out<<endl;
    return out;
}

istream& operator>>(istream& in, PFArrayD& obj)
{
    double element;
    
    in>>element;
    obj.addElement(element);

    return in;
}

PFArrayD::PFArrayD(int elems) : capacity(elems), used(0) {
    if (elems < 0)
        capacity = DEFSIZE;

    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject) : capacity(pfaObject.capacity), used(pfaObject.used) {
    assert(used >= 0);
    assert(capacity > 0);

    a = new double[capacity];
    for (int i = 0; i < used; ++i)
        a[i] = pfaObject.a[i];
}

void PFArrayD::output() {
    for (int i = 0; i < used; i++)
        cout << a[i] << endl;
}

void PFArrayD::addElement(double element) {
    if (used < capacity)
        a[used++] = element;
    else {
        assert(used == capacity);
        capacity *= 2;
        double* ptr = new double[capacity];

        for (int i = 0; i < used; ++i)
            ptr[i] = a[i];

        ptr[used++] = element;

        delete[] a;

        a = ptr;
    }
}

double& PFArrayD::operator[](int index) {
    return a[index];
}

const double& PFArrayD::operator[](int index) const {
    return a[index];
}

PFArrayD PFArrayD::operator ()(int ind, int size) {
    // consider size is a normal value
    PFArrayD temp(size);
    if (ind >= 0 && size > 0 && ind + size <= used) {
        for (int i = 0; i < size; ++i)
            temp.addElement(a[ind + i]);
    }
    return temp;
}

PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide) {
    if (&rightSide == this)
        return *this;

    used = rightSide.used;
    capacity = rightSide.capacity;
    delete[] a;

    a = new double[capacity];
    for (int i = 0; i < used; ++i)
        a[i] = rightSide.a[i];

    return *this;
}

PFArrayD& PFArrayD::operator +=(const PFArrayD& rightSide) {
    if (&rightSide == this) {
        PFArrayD temp = *this;
        for (int i = 0; i < temp.used; ++i)
            addElement(temp[i]);
    }
    else {
        for (int i = 0; i < rightSide.used; ++i)
            addElement(rightSide[i]);
    }

    return *this;
}

PFArrayD::~PFArrayD() {
    delete[] a;
    a = nullptr;
}

int main() {
    PFArrayD a(10);
    cin>>a;
    cin>>a;
    cin>>a;
    cin>>a;
    cin>>a;
    cin>>a;
    cin>>a;
    cin>>a;
    cout<<"------"<<endl;
    PFArrayD b = a(2,3);
    cout<<a;
    cout<<"------"<<endl;
    cout<<b;
    a+=b;
    cout<<"------"<<endl;
    cout<<a;
    b=a;
    cout<<"------"<<endl;
    cout<<b;


    

    return 0;
}