#ifndef CARGA_H
#define CARGA_H

#include "configuracion.h"
#include <string>

class Carga {
protected:
    std::string nombre_;
    double potenciaKW_;
    bool encendida_;
    double consumoSemanal_[DIAS_SEMANA][HORAS_DIA]; // kWh registrados por dia y hora

public:bool esAplazable() const { return tipo() == "Aplazable"; }

void reiniciar() {
    encendida_ = false;
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        for (int h = 0; h < HORAS_DIA; ++h) {
            consumoSemanal_[d][h] = 0.0;
        }
    }
}

void registrarHora() {
    // Mantiene compatibilidad con el conteo horario por dia
    encendida_ = true;
}
    Carga(const std::string& nombre, double potenciaKW);
    virtual ~Carga() = default;

    // Interfaz base (Evidencia 2)
    std::string nombre() const;
    double potenciaKW() const;
    bool encendida() const;
    void fijarEncendida(bool estado);

    virtual bool debeEncender(int hora, double precioCOPkWh, double embalsesPct) const = 0;
    virtual std::string tipo() const = 0;

    // Extension semanal [7][24] (Evidencia 3)
    void registrarConsumo(int dia, int hora, double kwh);
    void registrarConsumo(int dia, int hora); // Sobrecarga: registra potenciaKW_ si esta encendida
    double getConsumo(int dia, int hora) const;
    double calcularConsumoTotalSemanal() const;
    double calcularPromedioSemanal() const;
    int obtenerDiaMayorConsumo() const;
    int obtenerHoraMayorConsumo() const;
};

#endif