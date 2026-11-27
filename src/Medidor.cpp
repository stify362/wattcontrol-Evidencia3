#include "Medidor.h"
#include <iostream>

// Resetea las métricas al iniciar un ciclo
void Medidor::reiniciar() {
    for (int dia = 0; dia < DIAS_SEMANA; ++dia) {
        for (int hora = 0; hora < HORAS_DIA; ++hora) {
            lecturas_[dia][hora] = 0.0;
            costos_[dia][hora] = 0.0;
        }
    }

    energiaTotalKWh_ = 0.0;
    costoTotalCOP_ = 0.0;
}

// Acumula la energía y el costo de la hora actual
void Medidor::registrarHora(double potenciaEncendidaKW, double precioCOPkWh) {
    if (potenciaEncendidaKW >= 0.0 && precioCOPkWh >= 0.0) {
        energiaTotalKWh_ += potenciaEncendidaKW; // 1 hora de consumo: kWh = kW * 1h
        costoTotalCOP_ += (potenciaEncendidaKW * precioCOPkWh);
    }
}

// Registra la lectura de consumo en la matriz de lecturas y costos, actualizando los acumuladores totales
void Medidor::registrarLectura(int dia, int hora, double potenciaKW, double precioCOPkWh) {
    if (dia < 0 || dia >= DIAS_SEMANA ||
        hora < 0 || hora >= HORAS_DIA ||
        potenciaKW < 0.0 ||
        precioCOPkWh < 0.0) {
        std::cerr << "Lectura invalida: revisa dia, hora, potencia y precio.\n";
        return;
    }

    const double energiaKWh = potenciaKW;
    const double costoCOP = energiaKWh * precioCOPkWh;

    energiaTotalKWh_ += energiaKWh - lecturas_[dia][hora];
    costoTotalCOP_ += costoCOP - costos_[dia][hora];

    lecturas_[dia][hora] = energiaKWh;
    costos_[dia][hora] = costoCOP;
}

bool Medidor::superaPotenciaContratada(double potenciaKW) const {
    return potenciaKW > config::POTENCIA_CONTRATADA_KW;
}

// Retorna la energía total acumulada
double Medidor::energiaTotalKWh() const {
    return energiaTotalKWh_;
}

// Retorna el costo financiero acumulado en COP
double Medidor::costoTotalCOP() const {
    return costoTotalCOP_;
}