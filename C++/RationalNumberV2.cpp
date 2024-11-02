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

        int getNum() const { return _num; }
        int getDenum() const { return _denum; }
        static void printCounter() { std::cout << "Number of rational numbers:" << Rational::counter << std::endl; }
    private:
        Rational& simplify();
        int _num;
        int _denum;
        static int counter;
};

std::ostream& operator<<(std::ostream& out, const Rational& obj);
std::istream& operator>>(std::istream& in, Rational& obj);
int Rational::counter = 0;

int main() {
    // Create two Rational objects
    Rational r1;
    Rational r2;
    std::cin >> r1 >> r2;

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

    r3 = r1 - r2;
    std::cout << "r3 = r1 - r2: " << r3 << std::endl;

    r3 = r1 / r2;
    std::cout << "r3 = r1 / r2: " << r3 << std::endl;

    r3 = r1 * r2;
    std::cout << "r3 = r1 * r2: " << r3 << std::endl;

    // Prefix increment
    ++r3;
    std::cout << "After ++r3: " << r3 << std::endl;

    // Postfix increment
    Rational r4;
    r4 = r3++;
    std::cout << "After r4 = r3++: " << "r4: " << r4 << ", r3: " << r3 << std::endl;

    // Unary negation
    Rational r5 = -r4;
    std::cout << "After r5 = -r4: " << r5 << std::endl;

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
    this->simplify();
    counter++;
}
Rational::Rational(const Rational& obj) {
    _num = obj._num;
    _denum = obj._denum;
    counter++;
}
Rational::~Rational() { counter--; }

Rational& Rational::simplify() {
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

    _num = std::abs(_num)/a * sign;
    _denum = std::abs(_denum)/a;
    return *this;
}

Rational& Rational::operator=(const Rational& obj) {
    _num = obj._num;
    _denum = obj._denum;
    return *this;
}
bool Rational::operator==(const Rational& obj) const {
    return (_num == obj._num && _denum == obj._denum);
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
    Rational temp(tnum, tdenum);
    temp.simplify();
    return temp;
}
Rational Rational::operator-(const Rational& obj) const {
    int tnum = _num * obj._denum - _denum * obj._num;
    int tdenum = _denum * obj._denum;
    Rational temp(tnum, tdenum);
    temp.simplify();
    return temp;
}
Rational Rational::operator*(const Rational& obj) const {
    int tnum = _num * obj._num;
    int tdenum = _denum * obj._denum;
    Rational temp(tnum, tdenum);
    temp.simplify();
    return temp;
}
Rational Rational::operator/(const Rational& obj) const {
    if (obj._num == 0) {
        throw std::invalid_argument("Divison with 0 is not possible!");
    }
    int tnum = _num * obj._denum;
    int tdenum = _denum * obj._num;
    Rational temp(tnum, tdenum);
    temp.simplify();
    return temp;
}

Rational& Rational::operator+=(const Rational& obj) {
    _num = _num * obj._denum + _denum * obj._num;
    _denum = _denum * obj._denum;
    this->simplify();
    return *this;
}
Rational& Rational::operator-=(const Rational& obj) {
    _num = _num * obj._denum - _denum * obj._num;
    _denum = _denum * obj._denum;
    this->simplify();
    return *this;
}
Rational& Rational::operator*=(const Rational& obj) {
    _num = _num * obj._num;
    _denum = _denum * obj._denum;
    this->simplify();
    return *this;
}
Rational& Rational::operator/=(const Rational& obj) {
    if (obj._num == 0) {
        throw std::invalid_argument("Divison with 0 is not possible!");
    }
    _num = _num * obj._denum;
    _denum = _denum * obj._num;
    this->simplify();
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