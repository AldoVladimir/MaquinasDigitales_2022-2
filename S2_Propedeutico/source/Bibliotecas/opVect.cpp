// Implementación de las funciones

#include "opVect.h"
#include <iostream>
using namespace std;

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

void resVect(int *va, int *vb, int *vs, int size){
    for(int i=0; i<size; i++){
        vs[i] = va[i] - vb[i];
    }
}

void mulVect(int *va, int *vb, int *vs, int size){
    for(int i=0; i<size; i++){
        vs[i] = va[i] * vb[i];
    }
}

void divVect(int *va, int *vb, int *vs, int size){
    for(int i=0; i<size; i++){
        vs[i] = va[i] / vb[i];
    }
}
