#include <iostream>
using namespace std;


int main(){

    int arr[8] = {5,8,6,3,11,1,9,7};

    for(int i=0; i<8; i++){
        if(arr[i]%2 == 0){
            cout << "El valor " << arr[i] << " es par" << endl;
        }else{
            cout << "El valor " << arr[i] << " es impar" << endl;
        }
    }

    return 0;
}