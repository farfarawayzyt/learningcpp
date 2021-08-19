#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void displayVector(const vector<T> &vec){
    for (auto const &ele: vec){
        cout << ele << " ";
    }
    cout << endl;
}