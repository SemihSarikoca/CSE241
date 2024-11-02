#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Shape {
public:
    Shape() = default;
    virtual double perimater() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
    
};

class Rectangle : public Shape {
public:
    Rectangle(double _x = 0., double _y = 0.) : x(_x), y(_y) {}
    double perimater() const override { return 2.*x + 2.*y; }
    double area() const override { return x*y; }
private:
    double x;
    double y;
    
};
class Square : public Shape {
public:
    Square(double _x = 0.) : x(_x) {}
    double perimater() const override { return 4.*x; }
    double area() const override { return x*x; }
private:
    double x;
};
class Triangle : public Shape {
public:
    Triangle(double _x = 0., double _y = 0., double _z = 0.) : x(_x), y(_y), z(_z) {}
    double perimater() const override {return x + y + z;}
    double area() const override {
        double u = this->perimater() / 2.;
        return sqrt(u*(u-x)*(u-y)*(u-z));
    }
private:
    double x;
    double y;
    double z;
    
};
class Circle : public Shape {
public:
    Circle(double _r = 0.) : r(_r) {}
    double perimater() const override {return 2*r*M_PI;}
    double area() const override {return r*r*M_PI;}
private:
    double r;
};

int main() {
    vector<Shape*> v;
    v.push_back(new Rectangle(2,6));
    v.push_back(new Circle(1));
    v.push_back(new Square(3));
    v.push_back(new Triangle(3,4,5));
    
    cout << "Perimaters: " << endl;
    for (auto& p : v)
        cout << p->perimater() << endl;
    
    cout << "Areas: " << endl;
    for (auto& p : v)
        cout << p->area() << endl;
    
    for (auto& p : v)
        delete p;
    
    return 0;
}
