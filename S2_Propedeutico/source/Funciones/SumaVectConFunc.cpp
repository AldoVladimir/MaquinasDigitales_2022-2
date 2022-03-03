#include <iostream>
using namespace std;

#define V_SIZE  3
void printVect(int *v, int size);
void sumVect(int *va, int *vb, int *vs, int size);

int main(){

    int v1[V_SIZE] = {1,2,3}, v2[V_SIZE] = {3,1,2}, v3[V_SIZE] = {2,3,1};
    int vr[V_SIZE];

    cout << "vr = v1 + v2" << endl;
    sumVect(v1, v2, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v1 + v3" << endl;
    sumVect(v1, v3, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v2 + v3" << endl;
    sumVect(v2, v3, vr, V_SIZE);
    printVect(vr, V_SIZE);

    cout << "vr = v1 + v2 + v3" << endl;
    sumVect(v1, vr, vr, V_SIZE);
    printVect(vr, V_SIZE);

    return 0;
}

void printVect(int *v, int size){
    cout << "V = {";
    for(int i=0; i<size; i++){
        cout << " " << v[i] << " ";
    }
    cout << "}\n" << endl;
}

void sumVect(int *va, int *vb, int *vs, int size){
    for(int i=0; i<size; i++){
        vs[i] = va[i] + vb[i];
    }
}