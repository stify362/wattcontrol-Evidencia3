// Parqueadero.h: une todo
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "Caja.h"             // COMPOSICION
#include "Vehiculo.h"         // AGREGACION
#include "Afluencia.h"        // ASOCIACION
#include "utilidades.h"       // sumar, promedio, posicionMaximo, linea

// =============================================================
// Clase Parqueadero: une todo
// =============================================================
class Parqueadero {
private:
    string nombre;                      // el nombre del parqueadero
    Caja caja;                          // COMPOSICION: la caja nace y muere con el parqueadero
    Vehiculo* tipos[TIPOS];             // AGREGACION: los tipos existen fuera (los crea el main)
    Afluencia* afluencia;               // ASOCIACION: el parqueadero solo la consulta
    float ingresos[DIAS_SEMANA][HORAS_DIA];  // MATRIZ de resultados: lo que entra cada hora
    int atendidos[DIAS_SEMANA];         // vehiculos que pudieron entrar, por dia
    int rechazados[DIAS_SEMANA];        // vehiculos que no cupieron, por dia
    bool simulado;                      // ya se simulo la semana?

public:
    Parqueadero(string n, Vehiculo* carro, Vehiculo* moto, Afluencia* a) {
        nombre = n;
        tipos[0] = carro;               // recibe los tipos ya creados
        tipos[1] = moto;
        afluencia = a;                  // y la afluencia ya creada
        simulado = false;
    }

    // Recorre la semana con dos for anidados y llena la matriz ingresos
    void simularSemana() {
        caja.cerrar();                                       // empieza con la caja en cero
        for (int d = 0; d < DIAS_SEMANA; d++) {              // cada dia (fila)
            atendidos[d] = 0;
            rechazados[d] = 0;
            for (int h = 0; h < HORAS_DIA; h++) {            // cada hora (columna)
                float ingresoHora = 0;
                for (int t = 0; t < TIPOS; t++) {            // cada tipo: carro y moto
                    int llegan = afluencia->llegadas(t, d, h);
                    int entran = llegan;
                    if (entran > tipos[t]->getCupos()) {     // no caben todos?
                        entran = tipos[t]->getCupos();       // solo entran los cupos
                    }
                    atendidos[d] += entran;
                    rechazados[d] += llegan - entran;        // los demas se van
                    // POLIMORFISMO: tarifa() es la del Carro o la de la Moto
                    ingresoHora += entran * tipos[t]->tarifa(h);
                }
                ingresos[d][h] = ingresoHora;                // guarda en la matriz
                caja.cobrar(ingresoHora);                    // y lo cobra en la caja
            }
        }
        simulado = true;
        cout << "\nSemana simulada: " << DIAS_SEMANA << " dias x " << HORAS_DIA
             << " horas = " << DIAS_SEMANA * HORAS_DIA << " horas." << endl;
    }

    // Reporte semanal: usa las funciones sumar, promedio y posicionMaximo
    void reporte() {
        if (!simulado) {                                     // sin simular no hay datos
            cout << "\nPrimero simule la semana (opcion 2)." << endl;
            return;
        }
        float porDia[DIAS_SEMANA];                           // ingreso total de cada dia
        cout << "\nREPORTE SEMANAL - " << nombre << endl;
        linea(52, '=');                                      // sobrecarga: largo y caracter
        cout << setw(10) << "Dia" << setw(12) << "Atendidos"
             << setw(12) << "Rechazados" << setw(16) << "Ingresos COP" << endl;
        linea(52);
        for (int d = 0; d < DIAS_SEMANA; d++) {
            porDia[d] = sumar(ingresos[d], HORAS_DIA);       // sobrecarga: sumar de float
            cout << setw(10) << DIAS[d] << setw(12) << atendidos[d]
                 << setw(12) << rechazados[d]
                 << setw(16) << fixed << setprecision(0) << porDia[d] << endl;
        }
        linea(52);

        // El dia con mas ingresos
        int mejorDia = posicionMaximo(porDia, DIAS_SEMANA);

        // La hora con mas ingresos de toda la semana: recorre la matriz
        int diaPico = 0;
        int horaPico = 0;
        for (int d = 0; d < DIAS_SEMANA; d++) {
            int h = posicionMaximo(ingresos[d], HORAS_DIA);  // la mejor hora de ese dia
            if (ingresos[d][h] > ingresos[diaPico][horaPico]) {
                diaPico = d;                                 // es mejor que la que llevaba
                horaPico = h;
            }
        }

        float semana = caja.getTotal();                      // lo que quedo en la caja
        int totalRechazados = sumar(rechazados, DIAS_SEMANA); // sobrecarga: sumar de int

        cout << "Dia con mas ingresos:     " << DIAS[mejorDia]
             << " ($" << porDia[mejorDia] << ")" << endl;
        cout << "Hora con mas ingresos:    " << DIAS[diaPico] << " a las " << horaPico
             << ":00 ($" << ingresos[diaPico][horaPico] << ")" << endl;
        cout << "Promedio por dia:         $" << promedio(porDia, DIAS_SEMANA) << endl;
        cout << "Ingresos de la semana:    $" << semana << endl;
        cout << "Proyeccion del mes (x" << SEMANAS_MES << "):  $" << semana * SEMANAS_MES << endl;
        cout << "Vehiculos rechazados:     " << totalRechazados
             << " (no habia cupo)" << endl;
    }
};