#include <iostream>
#include "TarjetaBancaria.h"

int main(){

    TarjetaBancaria t1("1234123412341234","Rodrigo Castillo","BanUNAM",06,28,1234);

    t1.ActivarTarjeta();
    t1.Pagar(1000, 1234);
    t1.Pagar(2453.25, 1234);
    t1.Pagar(10, 1235);
    t1.AnularTarjeta();

    return 0;
}