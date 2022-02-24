#include <iostream>
using namespace std;

int main(){
    float dato;
    cout << "Ingresa un numero: ";
    cin >> dato;

    if(dato > 0){
        cout << "El numero es mayor que cero" << endl;
    }else{
        dato = dato + 10;
        cout << "El nuevo numero es: " << dato << endl;
    }

    return 0;
}