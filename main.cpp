#include "mat.hpp"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int rows, cols;
    char simple1, simple2;

    cout << "enter rows and cols : ";
    cin >> rows;
    cin >> cols;
    cout << endl;

    cout << "enter simple 1 & simple 2 : ";
    cin >> simple1;
    cin >> simple2;
    cout << endl;

    cout << ariel::mat(cols, rows, simple1, simple2) << endl;
    return 0;
}
