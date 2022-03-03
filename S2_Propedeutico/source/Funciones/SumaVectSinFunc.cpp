#include <iostream>
using namespace std;

int main(){

    int v1[3] = {1,2,3}, v2[3] = {3,1,2}, v3[3] = {2,3,1};
    int vr[3];

    cout << "vr = v1 + v2" << endl;
    cout << "vr = {";
    for(int i=0; i<3; i++){
        vr[i] = v1[i] + v2[i];
        cout << " " << vr[i] << " ";
    }
    cout << "} \n" << endl;

    cout << "vr = v1 + v3" << endl;
    cout << "vr = {";
    for(int i=0; i<3; i++){
        vr[i] = v1[i] + v3[i];
        cout << " " << vr[i] << " ";
    }
    cout << "} \n" << endl;

    cout << "vr = v2 + v3" << endl;
    cout << "vr = {";
    for(int i=0; i<3; i++){
        vr[i] = v2[i] + v3[i];
        cout << " " << vr[i] << " ";
    }
    cout << "} \n" << endl;

    cout << "vr = v1 + v2 + v3" << endl;
    cout << "vr = {";
    for(int i=0; i<3; i++){
        vr[i] = v1[i] + vr[i];
        cout << " " << vr[i] << " ";
    }
    cout << "} \n" << endl;

    return 0;
}