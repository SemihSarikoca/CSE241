#include <iostream>
#include <vector>

using namespace std;

class DayofYear {
    public:
        DayofYear(int day = 1) : day(day % 366) {}
        DayofYear(const DayofYear& obj) : day(obj.day) {}
        ~DayofYear() = default;
        DayofYear& operator=(const DayofYear& obj) {
            day = obj.day;
            return *this;
        }
        bool operator==(const DayofYear& obj) const {return (day == obj.day);}
        bool operator!=(const DayofYear& obj) const {return !(*this == obj);}
        friend decltype(cout)& operator<<(decltype(cout)& out, const DayofYear& day);
        int getDay() const {return day;}
    private:
        int day;
};

class DayofYearSet {
    public:
        DayofYearSet() : data(nullptr), sizeofset(0) {++aliveSets;}
        DayofYearSet(const DayofYearSet& days);
        DayofYearSet(vector<DayofYear> days);
        ~DayofYearSet();


        void add(const DayofYear& obj);
        void remove(const DayofYear& obj);
        int size() const {return sizeofset;} //overloaded with vectors size() function

        bool operator==(const DayofYearSet& days) const;
        bool operator!=(const DayofYearSet& days) const {return !(*this == days);}

        DayofYearSet operator+(const DayofYearSet& days) const; //uninon
        DayofYearSet operator-(const DayofYearSet& days) const; //difference
        DayofYearSet operator^(const DayofYearSet& days) const; //intersection
        DayofYearSet operator!() const; //complement
        DayofYear operator[](int index) const {
            return this->data[index];
        }
        static int getAliveSets() {return aliveSets;}
        friend decltype(cout)& operator<<(decltype(cout)& out, const DayofYearSet& days);
    private:
        DayofYear * data;
        int sizeofset;
        inline static int aliveSets = 0;

        bool search(const DayofYear& obj);
};
decltype(cout)& operator<<(decltype(cout)& out, const DayofYearSet& days) {
    out << "{" << endl;
    for (int i = 0; i < days.size(); ++i) {
        out << days.data[i].getDay() << "," << endl;
    }
    out << "}" << endl;
    return out;
}
decltype(cout)& operator<<(decltype(cout)& out, const DayofYear& day) {
    out << day.getDay();
    return out;
}

int main() {
    // Create instances of DayofYear
    DayofYear day1(1);
    DayofYear day2(15);
    DayofYear day3(30);

    // Create DayofYearSet objects
    DayofYearSet set1;
    set1.add(day1);
    set1.add(day2);

    DayofYearSet set2;
    set2.add(day2);
    set2.add(day3);

    // Test the operators
    DayofYearSet unionSet = set1 + set2;
    DayofYearSet differenceSet = set1 - set2;
    DayofYearSet intersectionSet = set1 ^ set2;

    // Print the results
    cout << "Set1: " << set1 << endl;
    cout << "Set2: " << set2 << endl;
    cout << "Set1 at intex 1:" << set1 << endl;
    cout << "Union Set: " << unionSet << endl;
    cout << "Difference Set: " << differenceSet << endl;
    cout << "Intersection Set: " << intersectionSet << endl;
    cout << "Complement Set of Set2: " << !(set2) << endl;
    cout << "Alive Sets: " << DayofYearSet::getAliveSets() << endl;

    return 0;
}

DayofYearSet::DayofYearSet(const DayofYearSet& days) {
    sizeofset = days.size();
    data = new DayofYear[sizeofset];
    for (int i = 0; i < sizeofset; ++i) {
        data[i] = days.data[i];
    }
    ++aliveSets;
}
DayofYearSet::DayofYearSet(vector<DayofYear> days) {
    sizeofset = days.size();
    data = new DayofYear[sizeofset];
    int i = 0;
    for (const auto& day : days) {
        data[i] = day;
        ++i;
    }
    ++aliveSets;
}
DayofYearSet::~DayofYearSet() {
    delete[] data;
    data = nullptr;
    --aliveSets;
}

void DayofYearSet::add(const DayofYear& obj) {
    if(search(obj)) return;
    DayofYear* temp = new DayofYear[sizeofset + 1];
    for (int i = 0; i < sizeofset; ++i) {
        temp[i] = data[i];
    }
    temp[sizeofset] = obj;
    delete[] data;
    data = temp;
    ++sizeofset;
}
void DayofYearSet::remove(const DayofYear& obj) {
    if (!search(obj)) return;
    DayofYear* temp = new DayofYear[sizeofset-1];
    for (int i = 0, j = 0; i < sizeofset; ++i, ++j) {
        if (data[i] == obj) {
            --j;
            continue;
        }
        temp[j] = data[i];
    }
    delete[] data;
    data = temp;
    --sizeofset;
}
bool DayofYearSet::operator==(const DayofYearSet& days) const {
    // Check if sizes are equal
    if (sizeofset != days.size()) {
        return false;
    }

    // Bubble sort the arrays
    for (int i = 0; i < sizeofset - 1; ++i) {
        for (int j = 0; j < sizeofset - i - 1; ++j) {
            if (data[j].getDay() > data[j + 1].getDay()) {
                // Swap elements if they are out of order
                DayofYear temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    // Bubble sort the other array
    for (int i = 0; i < days.size() - 1; ++i) {
        for (int j = 0; j < days.size() - i - 1; ++j) {
            if (days.data[j].getDay() > days.data[j + 1].getDay()) {
                // Swap elements if they are out of order
                DayofYear temp = days.data[j];
                days.data[j] = days.data[j + 1];
                days.data[j + 1] = temp;
            }
        }
    }

    // Check if sorted arrays are equal
    for (int i = 0; i < sizeofset; ++i) {
        if (data[i] != days.data[i]) {
            return false;
        }
    }

    return true;
}

DayofYearSet DayofYearSet::operator+(const DayofYearSet& days) const {
    vector<DayofYear> setUnion;
    for (int i = 0; i < sizeofset; ++i) {
        setUnion.push_back(data[i]);
    }
    for (int j = 0; j < days.sizeofset; ++j) {
        if (setUnion[j].getDay() != days.data[j].getDay()) {
            setUnion.push_back(days.data[j]);
        }
    }

    return DayofYearSet(setUnion);
}
DayofYearSet DayofYearSet::operator-(const DayofYearSet& days) const {
    std::vector<DayofYear> setDifference;

    for (int i = 0; i < this->sizeofset; ++i) {
        bool found = false;
        for (int j = 0; j < days.sizeofset; ++j) {
            if (data[i] == days.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            setDifference.push_back(data[i]);
        }
    }

    return DayofYearSet(setDifference);
}
DayofYearSet DayofYearSet::operator^(const DayofYearSet& days) const {
    vector<DayofYear> setIntersection;
    for (int i = 0; i < this->sizeofset; ++i) {
        for (int j = 0; j < days.sizeofset; ++j) {
            if (data[i].getDay() == days.data[j].getDay()) {
                setIntersection.push_back(data[i]);
                break;
            }
        }
    }
    DayofYearSet temp(setIntersection);
    return temp;
}
DayofYearSet DayofYearSet::operator!() const {
    vector<DayofYear> wholeYear;
    for (int i = 1; i <= 365; ++i) {
        wholeYear.push_back(DayofYear(i));
    }
    return DayofYearSet(wholeYear) - *this;
}

bool DayofYearSet::search(const DayofYear& obj) {
    for (int i = 0; i < sizeofset; ++i) {
        if (obj == data[i]) return true;
    }
    return false;
}
