//
//  TurnByte.cpp
//  study
//
//  Created by Semih Sarıkoca on 22.01.2024.
//

#include <iostream>
#include <string>
using namespace std;

string intToBinary(int value) {
    if (value == 0) {
        return "0";
    } else if (value == 1) {
        return "1";
    } else {
        // Recursive step
        return intToBinary(value / 2) + to_string(value % 2);
    }
}
int main() {
    cout << intToBinary(10*10*5*2*7*9*2*4*9*11*83*81);
}
