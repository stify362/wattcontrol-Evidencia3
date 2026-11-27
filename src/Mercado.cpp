#include "Mercado.h"

Mercado::Mercado() {
    cargarTarifasSemanales();
}

Mercado::Mercado(const std::string& operador, double nivelEmbalsesPct)
    : operador_(operador.empty() ? "XM - SIN Colombia" : operador) {
    actualizarNivelEmbalses(nivelEmbalsesPct);
}

void Mercado::cargarTarifasSemanales() {
    // Tarifas supuestas de referencia en COP/kWh
    const double tarifaValle = 680.0;
    const double tarifaNormal = 820.0;
    const double tarifaPico = 1150.0;

    const double factorEmbalse = hayAlertaEmbalses() ? 1.25 : 1.0;

    for (int d = 0; d < DIAS_SEMANA; ++d) {
        const double factorDia = (d >= 5) ? 0.95 : 1.0;

        for (int h = 0; h < HORAS_DIA; ++h) {
            double base = tarifaNormal;

            if (h < 6) {
                base = tarifaValle;
            } else if (esHoraPico(h)) {
                base = tarifaPico;
            }

            preciosSemana_[d][h] = base * factorDia * factorEmbalse;
        }
    }
}

bool Mercado::esHoraPico(int hora) const {
    return (hora >= 18 && hora <= 20);
}

bool Mercado::hayAlertaEmbalses() const {
    return embalsesPct_ < 40.0;
}

std::string Mercado::operador() const {
    return operador_;
}

double Mercado::nivelEmbalses() const {
    return embalsesPct_;
}

void Mercado::actualizarNivelEmbalses(double nivelPct) {
    if (nivelPct < 0.0) nivelPct = 0.0;
    if (nivelPct > 100.0) nivelPct = 100.0;

    embalsesPct_ = nivelPct;
    cargarTarifasSemanales();
}
