#include "Carga.h"
#include "utilidades.h"

Carga::Carga(const std::string& nombre, double potenciaKW)
    : nombre_(nombre), potenciaKW_(potenciaKW), encendida_(false) {
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        for (int h = 0; h < HORAS_DIA; ++h) {
            consumoSemanal_[d][h] = 0.0;
        }
    }
}

std::string Carga::nombre() const { return nombre_; }
double Carga::potenciaKW() const { return potenciaKW_; }
bool Carga::encendida() const { return encendida_; }
void Carga::fijarEncendida(bool estado) { encendida_ = estado; }

void Carga::registrarConsumo(int dia, int hora, double kwh) {
    if (dia >= 0 && dia < DIAS_SEMANA && hora >= 0 && hora < HORAS_DIA) {
        consumoSemanal_[dia][hora] = kwh;
    }
}

void Carga::registrarConsumo(int dia, int hora) {
    registrarConsumo(dia, hora, encendida_ ? potenciaKW_ : 0.0);
}

double Carga::getConsumo(int dia, int hora) const {
    if (dia < 0 || dia >= DIAS_SEMANA || hora < 0 || hora >= HORAS_DIA) {
        return 0.0;
    }
    return consumoSemanal_[dia][hora];
}

double Carga::calcularConsumoTotalSemanal() const {
    return totalSemana(consumoSemanal_);
}

double Carga::calcularPromedioSemanal() const {
    return promedio(consumoSemanal_);
}

int Carga::obtenerDiaMayorConsumo() const {
    return diaMayor(consumoSemanal_);
}

int Carga::obtenerHoraMayorConsumo() const {
    return horaMayor(consumoSemanal_);
}