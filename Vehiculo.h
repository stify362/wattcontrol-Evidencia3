// Vehiculo.h: clase base abstracta
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "configuracion.h"

// =============================================================
// Clase base Vehiculo (abstracta): no se crean "vehiculos" sueltos,
// solo carros o motos
// =============================================================
class Vehiculo {
protected:                      // protected: lo ven Vehiculo y sus hijas
    string tipo;                // "Carro" o "Moto"
    int cupos;                  // cuantos recibe el parqueadero en una hora

public:
    Vehiculo(string t, int c) { // constructor: se llama al crear el objeto
        tipo = t;
        cupos = c;
    }

    virtual ~Vehiculo() {}      // destructor virtual: obligatorio en una clase base

    // POLIMORFISMO: cada hija calcula la tarifa a su manera.
    // = 0 significa "virtual pura": Vehiculo no la implementa
    virtual int tarifa(int hora) = 0;

    string getTipo() { return tipo; }    // getter del tipo
    int getCupos() { return cupos; }     // getter de los cupos
};