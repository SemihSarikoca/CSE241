#include <iostream>
#include <vector>
using namespace std;

vector<int> maxmin(const vector<int>& v, int s = 0, int e = 0) {
    if (s == e) {
        return {v[s], v[e]};
    }

    int mid = (s + e) / 2;

    vector<int> left = maxmin(v, s, mid);
    vector<int> right = maxmin(v, mid + 1, e);

    int localMin = min(left[0], right[0]);
    int localMax = max(left[1], right[1]);

    return {localMin, localMax};
}

int main() {
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 15};
    vector<int> result = maxmin(v, 0, v.size()-1);

    cout << "Min: " << result[0] << endl;
    cout << "Max: " << result[1] << endl;

    return 0;
}
