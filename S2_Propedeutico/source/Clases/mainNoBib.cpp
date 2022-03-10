#include <iostream>
using namespace std;

class TarjetaBancaria{
    public:

    // Estos son los atributos (datos miembro) de la clase TarjetaBancaria
    // Definen, los datos que debe tener una tarjeta
    string numTarjeta;
    string nombreTarjeta;
    string BancoEmisor;
    int mesVig;
    int anioVig;
    int nipTarjeta;


    // Estos son los métodos (funciones miembro) de la clase TarjetaBancaria
    // Define las acciones que puede realizar una tarjeta

    TarjetaBancaria(string num_Tarjeta, string nombreTarjeta, string BancoEmisor,
                    int mesVig, int anioVig, int nipTarjeta){
        
        numTarjeta = num_Tarjeta;
        this->nombreTarjeta = nombreTarjeta;
        this->BancoEmisor = BancoEmisor;
        this->mesVig = mesVig;
        this->anioVig = anioVig;
        this->nipTarjeta = nipTarjeta;
    }

    void ActivarTarjeta(){
        cout << "Tarjeta de " << nombreTarjeta << " activada." << endl;
    }

    void AnularTarjeta(){
        cout << "Tarjeta con terminacion: " << numTarjeta.substr(12,4) << " anulada." << endl;
    }

    void Pagar(float cantidad, int nip){
        if(nip == nipTarjeta){
            cout << "Pagado: $" << cantidad << endl;
        }else{
            cout << "Pago rechazado." << endl;
        }
    }

};


int main(){

    int aux;
    TarjetaBancaria t1("1234123412341234", "Rodrigo Castillo", "BanCiencias", 3, 30, 1234);
    //t1.nombreTarjeta = "Rodrigo Castillo";
    //t1.numTarjeta = "1234123412341234";

    t1.ActivarTarjeta();
    t1.Pagar(1000.00, 1234);
    t1.Pagar(1859.32, 1235);
    t1.AnularTarjeta();

    return 0;
}
