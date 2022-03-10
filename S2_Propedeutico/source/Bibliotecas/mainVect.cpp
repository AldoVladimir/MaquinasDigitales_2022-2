#include <iostream>
#include "opVect.h"
using namespace std;

#define V_SIZE 3

int main(){

    int v1[V_SIZE] = {1,2,3}, v2[V_SIZE] = {3,1,2}, v3[V_SIZE] = {2,3,1};
    int vr[V_SIZE];

    cout << "vr = v1 + v2" << endl;
    sumVect(v1, v2, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v1 - v2" << endl;
    resVect(v1, v2, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v1 * v2" << endl;
    mulVect(v1, v2, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v1 / v2" << endl;
    divVect(v1, v2, vr, V_SIZE);
    printVect(vr, V_SIZE);


    return 0;
}