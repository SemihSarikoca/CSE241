#include <iostream>

class Rational {
    public:
        Rational(int num = 0, int denum = 1);
        Rational(const Rational& obj);
        ~Rational();

        Rational& operator=(const Rational& obj);
        bool operator==(const Rational& obj) const;
        bool operator!=(const Rational& obj) const;

        Rational& operator++(); //Pre inc
        Rational operator++(int); //Post inc
        Rational& operator-();

        Rational operator+(const Rational& obj) const;
        Rational operator-(const Rational& obj) const;
        Rational operator*(const Rational& obj) const;
        Rational operator/(const Rational& obj) const;

        Rational& operator+=(const Rational& obj);
        Rational& operator-=(const Rational& obj);
        Rational& operator*=(const Rational& obj);
        Rational& operator/=(const Rational& obj);

        friend std::ostream& operator<<(std::ostream& out, const Rational& obj);
        friend std::istream& operator>>(std::istream& in, Rational& obj);

        Rational simplify() const;
        int getNum() const { return _num; }
        int getDenum() const { return _denum; }
        static void printCounter() { std::cout << "Number of rational numbers:" << Rational::counter << std::endl; }
    private:
        static int counter;
        int _num;
        int _denum;
};

std::ostream& operator<<(std::ostream& out, const Rational& obj);
std::istream& operator>>(std::istream& in, Rational& obj);
int Rational::counter = 0;

int main() {
    // Create two Rational objects
    Rational r1(2, 3);
    Rational r2(4, -5);

    // Display the initial values
    std::cout << "Initial Values:" << std::endl;
    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;

    // Perform operations
    r1 += r2;
    std::cout << "After r1 += r2: " << r1 << std::endl;

    r1 -= r2;
    std::cout << "After r1 -= r2: " << r1 << std::endl;
    r1 *= r2;
    std::cout << "After r1 *= r2: " << r1 << std::endl;
    r1 /= r2;
    std::cout << "After r1 /= r2: " << r1 << std::endl;

    Rational r3;
    r3 = r1 + r2;
    std::cout << "r3 = r1 + r2: " << r3 << std::endl;

    // Prefix increment
    ++r3;
    std::cout << "After ++r3: " << r3 << std::endl;

    // Postfix increment
    Rational r4;
    r4 = r3++;
    std::cout << "After r4 = r3++: " << "r4: " << r4 << ", r3: " << r3 << std::endl;

    // Unary negation
    Rational r5;
    r5 = -r4;
    std::cout << "After r5 = -r4: " << r5 << std::endl;

    // Simplify and display
    Rational r6;
    r6 = r5.simplify();
    std::cout << "After r6 = r5.simplify(): " << r6 << std::endl;

    // Comparison
    bool isEqual = (r1 == r2);
    std::cout << "r1 == r2: " << (isEqual ? "true" : "false") << std::endl;

    Rational::printCounter();

    return 0;
}

Rational::Rational(int num, int denum) {
    _num = num;
    if (denum == 0) {
        throw std::invalid_argument("Denominator can not be zero!");
    }
    _denum = denum;
    counter++;
}
Rational::Rational(const Rational& obj) {
    _num = obj._num;
    _denum = obj._denum;
    counter++;
}
Rational::~Rational() {
    counter--;
}

Rational Rational::simplify() const {
    int a = this->getNum();
    int b = this->getDenum();
    int temp;

    int sign = (a * b >= 0) ? 1 : -1;
    a = std::abs(a);
    b = std::abs(b);
    while(b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }

    int sNum = std::abs(_num)/a * sign;
    int sDenum = std::abs(_denum)/a;

    return Rational(sNum, sDenum);
}

Rational& Rational::operator=(const Rational& obj) {
    _num = obj._num;
    _denum = obj._denum;
    return *this;
}
bool Rational::operator==(const Rational& obj) const {
    Rational temp1, temp2;
    temp1 = this->simplify();
    temp2 = obj.simplify();
    return (temp1._num == temp2._num && temp1._denum == temp2._denum);
}
bool Rational::operator!=(const Rational& obj) const {
    return !(*this == obj);
}

Rational& Rational::operator++() {
    _num += _denum;
    return *this;
}
Rational Rational::operator++(int) {
    Rational temp = *this;
    _num += _denum;
    return temp;
}
Rational& Rational::operator-() {
    _num *= -1;
    return *this;
}

Rational Rational::operator+(const Rational& obj) const {
    int tnum = _num * obj._denum + _denum * obj._num;
    int tdenum = _denum * obj._denum;
    return Rational(tnum, tdenum);
}
Rational Rational::operator-(const Rational& obj) const {
    int tnum = _num * obj._denum - _denum * obj._num;
    int tdenum = _denum * obj._denum;
    return Rational(tnum, tdenum);
}
Rational Rational::operator*(const Rational& obj) const {
    int tnum = _num * obj._num;
    int tdenum = _denum * obj._denum;
    return Rational(tnum, tdenum);
}
Rational Rational::operator/(const Rational& obj) const {
    if (obj._num == 0) {
        throw std::invalid_argument("Divison with 0 is undefined!");
    }
    int tnum = _num * obj._denum;
    int tdenum = _denum * obj._num;
    return Rational(tnum, tdenum);
}

Rational& Rational::operator+=(const Rational& obj) {
    _num = _num * obj._denum + _denum * obj._num;
    _denum = _denum * obj._denum;
    return *this;
}
Rational& Rational::operator-=(const Rational& obj) {
    _num = _num * obj._denum - _denum * obj._num;
    _denum = _denum * obj._denum;
    return *this;
}
Rational& Rational::operator*=(const Rational& obj) {
    _num = _num * obj._num;
    _denum = _denum * obj._denum;
    return *this;
}
Rational& Rational::operator/=(const Rational& obj) {
    _num = _num * obj._denum;
    _denum = _denum * obj._num;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Rational& obj) {
    out << obj._num << "/" << obj._denum;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& obj) {
    int num, denum;

    std::cout << "Enter the numerator: ";
    in >> num;
    std::cout << "Enter the denominator: ";
    in >> denum;

    if (denum == 0) {
        throw std::invalid_argument("Denominator cannot be zero!");
    }
    obj = Rational(num, denum);
    return in;
}
