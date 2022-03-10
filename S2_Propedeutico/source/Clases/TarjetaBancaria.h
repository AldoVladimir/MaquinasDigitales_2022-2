#ifndef TARJETA_H
#define TARJETA_H

#include <string>

class TarjetaBancaria{

    public:
    std::string numTarjeta;             // Número de tarjeta (16 dígitos)
    std::string nombreTarjeta;          // Nombre del titular
    std::string bancoEmisor;            // Nombre del banco emisor
    int mesVig;                         // Mes de vigencia
    int anioVig;                        // Año de vigencia
    int pinTarjeta;                     // NIP de la tarjeta

    
    // Constructor de la tarjeta bancaria
    TarjetaBancaria(std::string numTarjeta, std::string nombreTarjeta, std::string bancoEmisor,
                    int mesVig, int anioVig, int pinTarjeta);
    void ActivarTarjeta();                      // Método para activar la tarjeta
    void AnularTarjeta();                       // Método para anular la tarjeta
    void Pagar(float cantidad, int pin);        // Método para realizar un pago
};

#endif