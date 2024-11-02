//
//  FinalStudy.cpp
//  study
//
//  Created by Semih Sarıkoca on 22.01.2024.
//
#include <iostream>
#include <vector>
using namespace std;

template<class T>
T avg(const vector<T>& array, double total = 0., size_t it = 0) {
    if (it == array.size())
        return total/static_cast<double>(it);
    total += array[it];
    return avg(array, total, it + 1);
}

int main() {
    vector<double> semih = {2.5,1.,2.1,.8,7.1};
    vector<char> sari = {'a','u','r','c','w'};
    double xd = avg(semih);
    cout << avg(sari);
    cout << static_cast<double>(avg(sari));

}
