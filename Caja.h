// Caja.h: la plata que entra
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "configuracion.h"

// =============================================================
// Clase Caja: guarda la plata que entra
// =============================================================
class Caja {
private:
    float total;                // lo recaudado

public:
    Caja() { total = 0; }                           // la caja empieza vacia

    void cobrar(float valor) { total += valor; }    // suma un cobro
    void cerrar() { total = 0; }                    // la deja en cero
    float getTotal() { return total; }              // cuanto hay
};