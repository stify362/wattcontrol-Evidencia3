// Carro.h: hereda de Vehiculo
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "Vehiculo.h"        // HERENCIA: necesita a la clase madre

// HERENCIA: Carro ES UN Vehiculo
class Carro : public Vehiculo {
public:
    Carro() : Vehiculo("Carro", CUPOS_CARRO) {}   // llama al constructor de Vehiculo

    // De noche, el carro paga menos
    int tarifa(int hora) override {               // override: reemplaza la de Vehiculo
        bool deNoche = hora >= NOCHE_INICIO || hora <= NOCHE_FIN;
        if (deNoche) {
            return TARIFA_CARRO_NOCHE;
        }
        return TARIFA_CARRO_DIA;
    }
};