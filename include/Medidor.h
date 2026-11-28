#pragma once
#include "configuracion.h"

// B02: Composicion en Negocio. Cuenta consumo y costo CON gestor.
class Medidor {
private:
    double energiaTotalKWh_ = 0.0;
    double costoTotalCOP_ = 0.0;
    double lecturas_[DIAS_SEMANA][HORAS_DIA] = {}; // Matriz para almacenar lecturas de consumo por hora
    double costos_[DIAS_SEMANA][HORAS_DIA] = {}; // Matriz para almacenar costos por hora

public:
    // Método para reiniciar los acumuladores a cero
    void reiniciar();

    // Método para registrar el consumo de una hora de simulación
    void registrarHora(double potenciaEncendidaKW, double precioCOPkWh);

    // metodo para registrar una lectura de consumo en la matriz
    void registrarLectura(int dia, int hora, double potenciaKW, double precioCOPkWh);
    bool superaPotenciaContratada(double potenciaKW) const;
    // Getters para consultar las métricas acumuladas
    double energiaTotalKWh() const;
    double costoTotalCOP() const;
    };