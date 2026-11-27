// Afluencia.h: la matriz de llegadas
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "utilidades.h"       // usa linea() para dibujar la tabla

// =============================================================
// Clase Afluencia: la MATRIZ con los vehiculos que llegan
// cada dia (fila) y cada hora (columna) en una semana de ejemplo
// =============================================================
class Afluencia {
private:
    // Matriz semanal de carros: 7 dias x 24 horas.
    // Cada fila representa un dia de la semana.
    // Cada columna representa una hora del dia.
    // Los datos son fijos y no se generan con rand().
    const int CARROS[DIAS_SEMANA][HORAS_DIA] = {
    //   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23   <- hora
        { 0, 0, 0, 0, 1, 3, 9,21,27,19,13,11,13,18,11,11,12,21,26,20, 8, 6, 2, 0},  // Lunes
        { 0, 0, 0, 0, 3, 2,11,23,30,19,14,11,14,18,12,11,14,21,27,20,10, 7, 2, 3},  // Martes
        { 0, 0, 0, 0, 0, 4,10,22,27,20,16,11,17,15,13,10,16,18,29,20, 8, 6, 5, 3},  // Miercoles
        { 0, 0, 0, 0, 0, 3, 8,23,28,20,16,14,13,17,14,11,12,18,27,18, 9, 7, 5, 3},  // Jueves
        { 0, 0, 0, 0, 1, 4,10,24,32,20,15,14,18,16,11,10,17,20,30,19,12, 8, 5, 2},  // Viernes
        { 0, 0, 0, 0, 0, 1, 4, 9,14,17,19,18,22,23,18,15,13,14,11,12, 7, 4, 3, 1},  // Sabado
        { 3, 0, 0, 0, 0, 0, 3, 3, 8,11,14,15,20,17,14,10,10, 6, 4, 3, 1, 0, 3, 0}   // Domingo
    };
    const int MOTOS[DIAS_SEMANA][HORAS_DIA] = {
    //   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23   <- hora
        { 0, 0, 0, 0, 1, 3, 7,12,17,12, 7, 8,11,12, 8, 7, 9,12,14,11, 8, 4, 3, 3},  // Lunes
        { 0, 0, 0, 0, 2, 4, 5,15,16,11, 8, 6, 7,11, 8, 8, 6,13,14,10, 5, 5, 3, 1},  // Martes
        { 0, 0, 0, 0, 1, 1, 6,12,16,14, 6, 6, 8, 8, 8, 9,10,14,14,12, 6, 2, 4, 0},  // Miercoles
        { 0, 0, 0, 0, 3, 3, 5,12,17,10, 9, 9, 8, 9, 7, 8, 7,12,17,13, 5, 4, 1, 3},  // Jueves
        { 0, 0, 0, 0, 1, 0, 7,16,20,12, 8, 6, 8,11, 7, 7, 9,13,20,13, 7, 2, 2, 0},  // Viernes
        { 0, 0, 0, 0, 0, 2, 2, 3, 7, 9,10,10,12,12,13,11, 8,10, 8, 8, 3, 6, 0, 0},  // Sabado
        { 1, 0, 0, 0, 0, 0, 1, 3, 3, 8, 8, 8, 9, 8, 8, 8, 7, 6, 5, 2, 1, 0, 2, 0}   // Domingo
    };

public:
    // Cuantos vehiculos de un tipo llegan un dia a una hora.
    // tipo 0 = carros, tipo 1 = motos (el mismo orden del arreglo de tipos)
    int llegadas(int tipo, int dia, int hora) {
        if (dia < 0 || dia >= DIAS_SEMANA || hora < 0 || hora >= HORAS_DIA) {
            return 0;
        }

        if (tipo == 0) {
            return CARROS[dia][hora];
        }
        return MOTOS[dia][hora];
    }

    // Muestra la matriz de carros: dos for anidados, filas y columnas
    void mostrar() {
        cout << "\nCarros que llegan (fila = dia, columna = hora)" << endl;
        cout << setw(10) << "Dia";                           // encabezado
        for (int h = 0; h < HORAS_DIA; h += 2) cout << setw(4) << h;   // cada 2 horas, para que quepa
        cout << endl;
        linea(10 + 4 * 12);                                  // sobrecarga: solo el largo
        for (int d = 0; d < DIAS_SEMANA; d++) {              // for externo: los dias (filas)
            cout << setw(10) << DIAS[d];
            for (int h = 0; h < HORAS_DIA; h += 2) {         // for interno: las horas (columnas)
                cout << setw(4) << CARROS[d][h];
            }
            cout << endl;
        }
    }
};
