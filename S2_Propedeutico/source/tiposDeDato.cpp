#include <iostream>
using namespace std;

int myfunc(int a){
    return 5+a;
}

int main(){

    cout << "Tamaño en bytes de <char>: " << sizeof(char) << endl;
    cout << "Tamaño en bytes de <bool>: " << sizeof(bool) << endl;
    cout << "Tamaño en bytes de <int>: " << sizeof(int) << endl;
    cout << "Tamaño en bytes de <float>: " << sizeof(float) << endl;
    cout << "Tamaño en bytes de <long>: " << sizeof(long) << endl;
    cout << "Tamaño en bytes de <double>: " << sizeof(double) << endl;

    cout << myfunc(5) << endl;
    cout << "Probando el pull" << endl;
    double var=5;
    return 1;
}

