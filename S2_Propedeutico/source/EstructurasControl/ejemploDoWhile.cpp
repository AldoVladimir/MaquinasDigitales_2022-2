#include <iostream>
using namespace std;

int main(){

    int data;

    do{
        cout << "Ingresa un numero entre 0 y 10: ";
        cin >> data;
    }while(data >= 0 && data <= 10);

    cout << "El numero " << data << " no esta en el rango" << endl;

    return 0;
}