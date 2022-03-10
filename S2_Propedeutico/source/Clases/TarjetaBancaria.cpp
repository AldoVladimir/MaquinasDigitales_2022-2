#include "TarjetaBancaria.h"
#include <iostream>

TarjetaBancaria::TarjetaBancaria(std::string numTarjeta, std::string nombreTarjeta, std::string bancoEmisor,
                int mesVig, int anioVig, int pinTarjeta){
    
    this->numTarjeta = numTarjeta;
    this->nombreTarjeta = nombreTarjeta;
    this->bancoEmisor = bancoEmisor;
    this->mesVig = mesVig;
    this->anioVig = anioVig;
    this->pinTarjeta = pinTarjeta;
}

void TarjetaBancaria::ActivarTarjeta(){
    std::cout << "Tarjeta de " << nombreTarjeta << " activada." << std::endl;
}

void TarjetaBancaria::AnularTarjeta(){
    std::cout << "Tarjeta con terminacion: " << numTarjeta.substr(12, 4) << " anulada." << std::endl;
}

void TarjetaBancaria::Pagar(float cantidad, int pin){
    if(pin == pinTarjeta){
        std::cout << "Pagado: $" << cantidad << std::endl;
    }else{
        std::cout << "Pago rechazado." << std::endl;
    }
}