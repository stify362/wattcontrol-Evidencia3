// Moto.h: hereda de Vehiculo
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "Vehiculo.h"        // HERENCIA: necesita a la clase madre

// HERENCIA: Moto ES UN Vehiculo
class Moto : public Vehiculo {
public:
    Moto() : Vehiculo("Moto", CUPOS_MOTO) {}

    // La moto paga lo mismo a cualquier hora.
    // El parametro no lleva nombre porque no se usa (asi g++ no da aviso)
    int tarifa(int) override {
        return TARIFA_MOTO;
    }
};